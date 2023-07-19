#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_LEN 100

void performCRCDivision(char *message, char *key, char *crc)
{
    int messageLen = strlen(message);
    int keyLen = strlen(key);

    // Make a copy of the message to store the modified message
    char modifiedMessage[100];
    strcpy(modifiedMessage, message);

    // Perform CRC division
    for (int i = 0; i <= messageLen - keyLen; i++)
    {
        if (modifiedMessage[i] == '1')
        {
            for (int j = 0; j < keyLen; j++)
            {
                modifiedMessage[i + j] = (modifiedMessage[i + j] == key[j]) ? '0' : '1';
            }
        }
    }

    // Extract the CRC remainder from the modified message
    strncpy(crc, modifiedMessage + messageLen - keyLen + 1, keyLen - 1);
    crc[keyLen - 1] = '\0';
}

// Function to detect errors
int detectErrors(char *receivedCode, char *key)
{
    char crc[MAX_LEN];
    performCRCDivision(receivedCode, key, crc);

    // Check if any error is detected
    for (int i = 0; i < strlen(crc); i++)
    {
        if (crc[i] == '1')
        {
            return 1; // Error detected
        }
    }

    return 0; // No error detected
}

int findErrorPosition(char *transmittedCode, char *receivedCode)
{
    int len = strlen(transmittedCode);

    for (int i = 0; i < len; i++)
    {
        if (transmittedCode[i] != receivedCode[i])
        {
            return i + 1; // Error position (1-based index)
        }
    }

    return -1; // No error found
}
int main()
{
    char message[MAX_LEN];
    char key[MAX_LEN];
    char crc[MAX_LEN];
    char transmittedCode[MAX_LEN];
    char receivedCode[MAX_LEN];

    printf("Enter the sender's code: ");
    scanf("%s", message);

    printf("Enter the key: ");
    scanf("%s", key);

    // Perform CRC division
    performCRCDivision(message, key, crc);

    printf("\nSender Side:\n");
    printf("CRC: %s\n", crc);

    // Append CRC to the original message
    strcpy(transmittedCode, message);
    strcat(transmittedCode, crc);

    printf("Transmitted Code: %s\n", transmittedCode);

    printf("\nReceiver Side:\n");
    printf("Enter the received code: ");
    scanf("%s", receivedCode);
    printf("Recieved code: %s\n", receivedCode);

    int errorDetected = detectErrors(receivedCode, key);
    
    if (errorDetected)
    {
        int errorIndex= findErrorPosition(transmittedCode, receivedCode);
        printf("Error detected.\n");
        printf("Error at position: %d\n", errorIndex);
    }
    else
    {
        printf("No error detected.\n");
    }

    return 0;
}
