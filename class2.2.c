#include <stdio.h>
#include <stdlib.h>

// Recursive GCD function
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        return 1;
    }

    FILE *fin = fopen(argv[1], "r");
    FILE *fout = fopen(argv[2], "w");

    if (!fin || !fout) {
        printf("Error opening file(s).\n");
        return 1;
    }

    int a, b;
    while (fscanf(fin, "%d %d", &a, &b) == 2) {
        int result = gcd(a, b);
        fprintf(fout, "The GCD of %d and %d is %d\n", a, b, result);
        printf("The GCD of %d and %d is %d\n", a, b, result);
    }

    fclose(fin);
    fclose(fout);
    return 0;
}
