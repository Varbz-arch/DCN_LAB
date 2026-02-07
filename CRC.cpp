#include <stdio.h>
#include <string.h>

// XOR operation (binary subtraction)
void xorOperation(char *temp, char *key, int keyLen) {
    for (int i = 0; i < keyLen; i++) {
        temp[i] = (temp[i] == key[i]) ? '0' : '1';
    }
}

void calculateCRC(char originalData[], char key[], char remainder[]) {
    char temp[200];
    strcpy(temp, originalData);

    int dataLen = strlen(originalData);
    int keyLen = strlen(key);
    for (int i = 0; i < keyLen - 1; i++) {
        strcat(temp, "0");
    }

    int tempLen = strlen(temp);

    // Binary division
    for (int i = 0; i <= tempLen - keyLen; i++) {
        if (temp[i] == '1') {
            xorOperation(&temp[i], key, keyLen);
        }
    }

    // Extract remainder
    int r = 0;
    for (int i = tempLen - (keyLen - 1); i < tempLen; i++) {
        remainder[r++] = temp[i];
    }
    remainder[r] = '\0';
}

// // Error detection: checks received data
// void detectError(char receivedData[], char key[]) {
//     char temp[200];
//     strcpy(temp, receivedData);

//     int dataLen = strlen(receivedData);
//     int keyLen = strlen(key);

//     for (int i = 0; i <= dataLen - keyLen; i++) {
//         if (temp[i] == '1') {
//             xorOperation(&temp[i], key, keyLen);
//         }
//     }

//     // Check if remainder is all zeros
//     int error = 0;
//     for (int i = dataLen - (keyLen - 1); i < dataLen; i++) {
//         if (temp[i] != '0') {
//             error = 1;
//             break;
//         }
//     }

//     if (error)
//         printf("Error detected in received data!\n");
//     else
//         printf("No error detected. Data is correct.\n");
// }

int main() {
    char data[100], key[20], remainder[20];
    char transmitted[200], received[200];

    printf("Enter data bits: ");
    scanf("%s", data);

    printf("Enter generator key: ");
    scanf("%s", key);

    // Calculate CRC remainder
    calculateCRC(data, key, remainder);

    // Form transmitted data
    strcpy(transmitted, data);
    strcat(transmitted, remainder);

    printf("CRC Remainder: %s\n", remainder);
    printf("Transmitted Data: %s\n", transmitted);

    // // Optionally, simulate received data
    // printf("\nEnter received data bits (can simulate error by changing one bit): ");
    // scanf("%s", received);

    // detectError(received, key);

    return 0;
}
