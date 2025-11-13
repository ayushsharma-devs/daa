#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    FILE *fa, *fd, *fr;
    int i, n = 400; // choose between 300-500 elements
    int val;

    fa = fopen("inAsce.dat", "w");
    fd = fopen("inDesc.dat", "w");
    fr = fopen("inRand.dat", "w");

    if (fa == NULL || fd == NULL || fr == NULL) {
        printf("Error creating files.\n");
        return 0;
    }

    // Ascending
    for (i = 1; i <= n; i++) {
        fprintf(fa, "%d ", i * 10); // e.g. 10, 20, ..., 4000
    }

    // Descending
    for (i = n; i >= 1; i--) {
        fprintf(fd, "%d ", i * 10);
    }

    // Random
    srand(time(0));
    for (i = 0; i < n; i++) {
        val = rand() % 5000 + 1; // between 1 and 500
        fprintf(fr, "%d ", val);
    }
    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    
    #define SIZE 300  // can change to 500 if needed
    
    void generateAscending(const char *filename) {
        FILE *fp = fopen(filename, "w");
        if (!fp) {
            perror("Error creating ascending file");
            return;
        }
    
        for (int i = 1; i <= SIZE; i++) {
            fprintf(fp, "%d ", i * 10);  // 10, 20, 30, ...
        }
    
        fclose(fp);
        printf("Generated %s\n", filename);
    }
    
    void generateDescending(const char *filename) {
        FILE *fp = fopen(filename, "w");
        if (!fp) {
            perror("Error creating descending file");
            return;
        }
    
        for (int i = SIZE; i >= 1; i--) {
            fprintf(fp, "%d ", i * 10);  // 3000, 2990, ...
        }
    
        fclose(fp);
        printf("Generated %s\n", filename);
    }
    
    void generateRandom(const char *filename) {
        FILE *fp = fopen(filename, "w");
        if (!fp) {
            perror("Error creating random file");
            return;
        }
    
        srand(time(NULL));
        for (int i = 0; i < SIZE; i++) {
            int num = rand() % 5000 + 1;
            fprintf(fp, "%d ", num);
        }
    
        fclose(fp);
        printf("Generated %s\n", filename);
    }
    
    int main() {
        generateAscending("inAsce.dat");
        generateDescending("inDesc.dat");
        generateRandom("inRand.dat");
    
        printf("All input files generated.\n");
        return 0;
    }
    
    fclose(fa);
    fclose(fd);
    fclose(fr);

    printf("Files generated successfully with %d entries each.\n", n);
    return 0;
}