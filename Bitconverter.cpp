// #include <stdio.h>
// #include <string.h>

// // Function to convert one character into 8-bit binary
// void printBinary(char character) {
//     int asciiValue = character;

//     // Loop from bit 7 to bit 0 (8 bits)
//     for (int bit = 7; bit >= 0; bit--) {
//         int binaryDigit = (asciiValue >> bit) & 1;
//         printf("%d", binaryDigit);
//     }
// }

// int main() {

//     char headerText[100];
//     char packetText[100];

//     // Take header input
//     printf("Enter header text: ");
//     scanf("%s", headerText);

//     // Take packet input
//     printf("Enter packet text: ");
//     scanf("%s", packetText);

//     printf("\nBinary Header: ");
//     for (int i = 0; headerText[i] != '\0'; i++) {
//         printBinary(headerText[i]);
//         printf(" ");
//     }

//     printf("\nBinary Packet: ");
//     for (int i = 0; packetText[i] != '\0'; i++) {
//         printBinary(packetText[i]);
//         printf(" ");
//     }

//     printf("\n\nCombined Binary Data: ");
//     for (int i = 0; headerText[i] != '\0'; i++) {
//         printBinary(headerText[i]);
//     }
//     for (int i = 0; packetText[i] != '\0'; i++) {
//         printBinary(packetText[i]);
//     }

//     printf("\n");

//     return 0;
// }


// #include <stdio.h>
// #include <stdlib.h>  // required for malloc and free

// int main() {
//     int h, d;

//     // Read number of header bits
//     printf("Enter number of header bits: ");
//     scanf("%d", &h);

//     // Allocate header array at runtime
//     int *header = (int*) malloc(h * sizeof(int));
//     if(header == NULL) {
//         printf("Memory allocation failed!\n");
//         return 1;
//     }

//     printf("Enter header bits (0 or 1):\n");
//     for (int i = 0; i < h; i++) {
//         scanf("%d", &header[i]);
//         if(header[i] != 0 && header[i] != 1) {
//             printf("Invalid input! Only 0 or 1 allowed.\n");
//             free(header); // free memory before exiting
//             return 0;
//         }
//     }

//     // Read number of data bits
//     printf("Enter number of data bits: ");
//     scanf("%d", &d);

//     // Allocate data array at runtime
//     int *data = (int*) malloc(d * sizeof(int));
//     if(data == NULL) {
//         printf("Memory allocation failed!\n");
//         free(header);
//         return 1;
//     }

//     printf("Enter data bits (0 or 1):\n");
//     for (int i = 0; i < d; i++) {
//         scanf("%d", &data[i]);
//         if(data[i] != 0 && data[i] != 1) {
//             printf("Invalid input! Only 0 or 1 allowed.\n");
//             free(header);
//             free(data);
//             return 0;
//         }
//     }

//     // Display packet
//     printf("\n---- FINAL PACKET ----\n");
//     printf("Header: ");
//     for (int i = 0; i < h; i++)
//         printf("%d", header[i]);

//     printf("\nData  : ");
//     for (int i = 0; i < d; i++)
//         printf("%d", data[i]);

//     printf("\nPacket: ");
//     for (int i = 0; i < h; i++)
//         printf("%d", header[i]);
//     for (int i = 0; i < d; i++)
//         printf("%d", data[i]);

//     // Free dynamically allocated memory
//     free(header);
//     free(data);

//     return 0;
// }


// #include <stdio.h>
// #include <string.h>
// void charToBinary(char ch, int bits[]) {
//     int ascii = ch;

//     for (int i = 7; i >= 0; i--) {
//         bits[i] = ascii % 2;
//         ascii = ascii / 2;
//     }
// }
// int stringToBinary(char str[], int result[]) {
//     int index = 0;

//     for (int i = 0; str[i] != '\0'; i++) {
//         int bits[8];
//         charToBinary(str[i], bits);

//         for (int j = 0; j < 8; j++) {
//             result[index++] = bits[j];
//         }
//     }
//     return index;  // number of bits
// }

// int main() {
//     char header[50], data[50];
//     int headerBits[400], dataBits[400], frame[800];

//     printf("Enter Header: ");
//     scanf("%s", header);

//     printf("Enter Data: ");
//     scanf("%s", data);

//     int hCount = stringToBinary(header, headerBits);
//     int dCount = stringToBinary(data, dataBits);

//     int k = 0;
//     for (int i = 0; i < hCount; i++)
//         frame[k++] = headerBits[i];
//     for (int i = 0; i < dCount; i++)
//         frame[k++] = dataBits[i];

//     printf("\nFrame bits: ");
//     for (int i = 0; i < k; i++)
//         printf("%d", frame[i]);

//     printf("\nTotal number of bits: %d\n", k);

//     return 0;
// }


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int* stringToBinary(char str[], int *bitCount) {
    int len = strlen(str);
    *bitCount = len * 8;   

    int *bits = (int*) malloc((*bitCount) * sizeof(int));
    if (bits == NULL) {
        printf("Memory allocation failed!\n");
        return NULL;
    }

    int k = 0;

    for (int i = 0; i < len; i++) {
        int ascii = str[i];
        for (int j = 7; j >= 0; j--) {
            bits[k + j] = ascii % 2;
            ascii = ascii / 2;
        }
        k += 8;
    }

    return bits;
}

int main() {
    char headerStr[50], dataStr[50];
    int hBitsCount, dBitsCount;

    printf("Enter Header string: ");
    scanf("%s", headerStr);

    printf("Enter Data string: ");
    scanf("%s", dataStr);
    int *header = stringToBinary(headerStr, &hBitsCount);
    int *data   = stringToBinary(dataStr, &dBitsCount);

    if (header == NULL || data == NULL)
        return 1;
    int totalBits = hBitsCount + dBitsCount;
    int *packet = (int*) malloc(totalBits * sizeof(int));

    if (packet == NULL) {
        printf("Memory allocation failed!\n");
        free(header);
        free(data);
        return 1;
    }
    int k = 0;
    for (int i = 0; i < hBitsCount; i++)
        packet[k++] = header[i];

    for (int i = 0; i < dBitsCount; i++)
        packet[k++] = data[i];

    printf("Header (binary): ");
    for (int i = 0; i < hBitsCount; i++)
        printf("%d", header[i]);

    printf("\nData   (binary): ");
    for (int i = 0; i < dBitsCount; i++)
        printf("%d", data[i]);

    printf("\nPacket (binary): ");
    for (int i = 0; i < totalBits; i++)
        printf("%d", packet[i]);

    printf("\nTotal number of bits: %d\n", totalBits);

    free(header);
    free(data);
    free(packet);

    return 0;
}
