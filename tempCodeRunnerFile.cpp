
    if (isBinary(data)) {
        strcpy(binaryData, data);  // Already binary, use as-is
    } else {
        stringToBinary(data, binaryData);  // Convert ASCII to binary
    }