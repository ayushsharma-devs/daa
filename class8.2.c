#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// A utility function to find the maximum of two integers
int max(int a, int b) {
    return (a > b) ? a : b;
}

/**
 * @brief Finds and prints the Longest Common Subsequence of two strings.
 * @param X The first string.
 * @param Y The second string.
 */
void findLCS(char *X, char *Y) {
    int m = strlen(X);
    int n = strlen(Y);

    // Create a DP table to store lengths of LCSs.
    // dp[i][j] will contain the length of LCS of X[0..i-1] and Y[0..j-1]
    int dp[m + 1][n + 1];

    // --- Step 1: Fill the DP table in a bottom-up manner ---
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if (i == 0 || j == 0) {
                // Base case: If one of the strings is empty, LCS is 0
                dp[i][j] = 0;
            } else if (X[i - 1] == Y[j - 1]) {
                // If the last characters match, add 1 to the LCS of the preceding strings
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                // If they don't match, take the max of the two possibilities
                dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // The length of the LCS is in the bottom-right cell
    int lcs_length = dp[m][n];
    
    // --- Step 2: Reconstruct the LCS string by backtracking ---
    
    // Allocate memory for the LCS string (+1 for the null terminator)
    char lcs_string[lcs_length + 1];
    lcs_string[lcs_length] = '\0'; // Set the null terminator

    // Start from the bottom-right corner of the DP table
    int i = m, j = n;
    int index = lcs_length;

    while (i > 0 && j > 0) {
        // If current characters in X and Y are the same, then this character is part of LCS
        if (X[i - 1] == Y[j - 1]) {
            lcs_string[index - 1] = X[i - 1]; // Put the character in the result
            i--;
            j--;
            index--;
        }
        // If not same, then find the larger of two and go in the direction of the larger value
        else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    // --- Step 3: Print the results ---
    printf("LCS: %s\n", lcs_string);
    printf("LCS Length: %d\n", lcs_length);
}

int main() {
    char str1[100], str2[100];

    printf("Enter the first string into an array: ");
    scanf("%s", str1);

    printf("Enter the second string into an array: ");
    scanf("%s", str2);

    findLCS(str1, str2);

    return 0;
}