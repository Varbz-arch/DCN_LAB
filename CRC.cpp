// #include <stdio.h>
// #include <string.h>

// // XOR operation (binary subtraction)
// void xorOperation(char *temp, char *key, int keyLen) {
//     for (int i = 0; i < keyLen; i++) {
//         temp[i] = (temp[i] == key[i]) ? '0' : '1';
//     }
// }

// void calculateCRC(char originalData[], char key[], char remainder[]) {
//     char temp[200];
//     strcpy(temp, originalData);

//     int dataLen = strlen(originalData);
//     int keyLen = strlen(key);
//     for (int i = 0; i < keyLen - 1; i++) {
//         strcat(temp, "0");
//     }

//     int tempLen = strlen(temp);

//     // Binary division
//     for (int i = 0; i <= tempLen - keyLen; i++) {
//         if (temp[i] == '1') {
//             xorOperation(&temp[i], key, keyLen);
//         }
//     }

//     // Extract remainder
//     int r = 0;
//     for (int i = tempLen - (keyLen - 1); i < tempLen; i++) {
//         remainder[r++] = temp[i];
//     }
//     remainder[r] = '\0';
// }

// // // Error detection: checks received data
// // void detectError(char receivedData[], char key[]) {
// //     char temp[200];
// //     strcpy(temp, receivedData);

// //     int dataLen = strlen(receivedData);
// //     int keyLen = strlen(key);

// //     for (int i = 0; i <= dataLen - keyLen; i++) {
// //         if (temp[i] == '1') {
// //             xorOperation(&temp[i], key, keyLen);
// //         }
// //     }

// //     // Check if remainder is all zeros
// //     int error = 0;
// //     for (int i = dataLen - (keyLen - 1); i < dataLen; i++) {
// //         if (temp[i] != '0') {
// //             error = 1;
// //             break;
// //         }
// //     }

// //     if (error)
// //         printf("Error detected in received data!\n");
// //     else
// //         printf("No error detected. Data is correct.\n");
// // }

// int main() {
//     char data[100], key[20], remainder[20];
//     char transmitted[200], received[200];

//     printf("Enter data bits: ");
//     scanf("%s", data);

//     printf("Enter generator key: ");
//     scanf("%s", key);

//     // Calculate CRC remainder
//     calculateCRC(data, key, remainder);

//     // Form transmitted data
//     strcpy(transmitted, data);
//     strcat(transmitted, remainder);

//     printf("CRC Remainder: %s\n", remainder);
//     printf("Transmitted Data: %s\n", transmitted);

//     // // Optionally, simulate received data
//     // printf("\nEnter received data bits (can simulate error by changing one bit): ");
//     // scanf("%s", received);

//     // detectError(received, key);

//     return 0;
// }



#include <stdio.h>
#include <string.h>
#include <ctype.h>
// XOR operation
void xorOperation(char *temp, char *key, int keyLen) {
    for (int i = 0; i < keyLen; i++) {
        temp[i] = (temp[i] == key[i]) ? '0' : '1';
    }
}

// Convert string to binary (ASCII)
void stringToBinary(char input[], char binary[]) {
    binary[0] = '\0';
    for (int i = 0; input[i] != '\0'; i++) {
        for (int j = 7; j >= 0; j--) {
            char bit = ((input[i] >> j) & 1) + '0';
            strncat(binary, &bit, 1);
        }
    }
}
void polynomialToBinary(char poly[], char binary[]) {
    int degree[20];
    int count = 0;
    int maxDeg = 0;

    // Extract degrees
    for (int i = 0; poly[i] != '\0'; i++) {
        if (poly[i] == 'x') {
            if (poly[i+1] == '^') {
                int d = poly[i+2] - '0';
                degree[count++] = d;
                if (d > maxDeg) maxDeg = d;
            } else {
                degree[count++] = 1;
                if (1 > maxDeg) maxDeg = 1;
            }
        } else if (poly[i] == '1') {
            degree[count++] = 0;
        }
    }

    // Initialize binary key
    for (int i = 0; i <= maxDeg; i++)
        binary[i] = '0';
    binary[maxDeg + 1] = '\0';

    // Set bits
    for (int i = 0; i < count; i++) {
        binary[maxDeg - degree[i]] = '1';
    }
}

// CRC calculation
void calculateCRC(char data[], char key[], char remainder[]) {
    char temp[600];
    strcpy(temp, data);

    int keyLen = strlen(key);

    for (int i = 0; i < keyLen - 1; i++)
        strcat(temp, "0");

    int tempLen = strlen(temp);

    for (int i = 0; i <= tempLen - keyLen; i++) {
        if (temp[i] == '1')
            xorOperation(&temp[i], key, keyLen);
    }

    int r = 0;
    for (int i = tempLen - (keyLen - 1); i < tempLen; i++)
        remainder[r++] = temp[i];

    remainder[r] = '\0';
}

// Receiver CRC check
void detectError(char received[], char key[]) {
    char temp[600];
    char remainder[50];
    strcpy(temp, received);

    int dataLen = strlen(received);
    int keyLen = strlen(key);

    // Division
    for (int i = 0; i <= dataLen - keyLen; i++) {
        if (temp[i] == '1') {
            xorOperation(&temp[i], key, keyLen);
        }
    }

    // Extract remainder
    int r = 0;
    int error = 0;
    for (int i = dataLen - (keyLen - 1); i < dataLen; i++) {
        remainder[r++] = temp[i];
        if (temp[i] != '0')
            error = 1;
    }
    remainder[r] = '\0';

    // Print remainder
    printf("Receiver Remainder: %s\n", remainder);

    // Error decision
    if (error)
        printf("Error detected \n");
    else
        printf("No error detected\n");
}


int main() {
    char data[100];
    char key[20];
    char poly[50];
    char binaryData[500];
    char remainder[50];
    char transmitted[600];
    char received[600];
    int pos;

    printf("Enter data (string): ");
    scanf("%s", data);

    printf("Enter generator polynomial (e.g., x^3+1): ");
    scanf("%s", poly);

    polynomialToBinary(poly, key);
    printf("Binary generator key: %s\n", key);

    // Convert data to binary
    stringToBinary(data, binaryData);

    printf("\nBinary data: %s\n", binaryData);
    printf("Binary key:  %s\n", key);

    // Sender side
    calculateCRC(binaryData, key, remainder);
    strcpy(transmitted, binaryData);
    strcat(transmitted, remainder);

    printf("\nCRC Remainder: %s\n", remainder);
    printf("Transmitted Data: %s\n", transmitted);

    // Receiver check (no error)
    printf("\n--- Receiver Check ---\n");
    detectError(transmitted, key);

    // Copy transmitted data to received buffer
    strcpy(received, transmitted);

    // Manual 1-bit error
    printf("\nEnter bit position to flip (0-based): ");
    scanf("%d", &pos);

    if (pos < 0 || pos >= strlen(received)) {
        printf("Invalid bit position! Program terminated.\n");
        return 0;   
    }

    // Flip the bit
    received[pos] = (received[pos] == '0') ? '1' : '0';

    printf("Received Data (after 1-bit change): %s\n", received);
    printf("--- Receiver Check (After 1-bit Error) ---\n");
    detectError(received, key);

    return 0;
}