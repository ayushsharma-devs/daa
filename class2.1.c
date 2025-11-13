#include <stdio.h>
#include <stdlib.h>

// Recursive function to convert a decimal number to binary string
void decimalToBinary(int num, char *binary, int pos) {
    if (pos < 0) return;  // Base case: no more bits to fill
    binary[pos] = (num % 2) + '0'; // Store '0' or '1'
    decimalToBinary(num / 2, binary, pos - 1); // Recursive call
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Usage: %s <n> <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    char *inputFile = argv[2];
    char *outputFile = argv[3];

    FILE *inFile = fopen(inputFile, "r");
    if (!inFile) {
        perror("Error opening input file");
        return 1;
    }

    FILE *outFile = fopen(outputFile, "w");
    if (!outFile) {
        perror("Error opening output file");
        fclose(inFile);
        return 1;
    }

    int num, count = 0;
    while (count < n && fscanf(inFile, "%d", &num) == 1) {
        char binary[17]; // 16 bits + null terminator
        binary[16] = '\0';
        decimalToBinary(num, binary, 15);
        fprintf(outFile, "The binary equivalent of %d is %s\n", num, binary);
        count++;
    }

    fclose(inFile);
    fclose(outFile);

    // Display output file contents
    outFile = fopen(outputFile, "r");
    if (!outFile) {
        perror("Error reopening output file");
        return 1;
    }

    char ch;
    while ((ch = fgetc(outFile)) != EOF) {
        putchar(ch);
    }

    fclose(outFile);
    return 0;
}
