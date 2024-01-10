#include <stdio.h>
#include <stdlib.h>
#include <string.h>  // Include string.h for strtok

#define MAX_BOYUT 7

int matrixA[MAX_BOYUT][MAX_BOYUT];
int matrixB[MAX_BOYUT][MAX_BOYUT];
int matrixS[MAX_BOYUT][MAX_BOYUT];

int dosyaOku() {
    FILE *fileA = fopen("inputA.txt", "r");
    FILE *fileB = fopen("inputB.txt", "r");

    if (fileA == NULL || fileB == NULL) {
        printf("Dosyalar Yok\n");
        return -1;
    }

    printf("dosyalar okundu\n");

    char line[50];
    int i = 0, j = 0;

    while (fgets(line, 50, fileA)) {
       printf("Satır: %s", line);

        char *cell = strtok(line, " ");  // Use cell for string token
        while (cell != NULL) {
            printf("\nhücre: %s\n", cell);
            matrixA[j][i] = atoi(cell);

            cell = strtok(NULL, " ");
            j++;
        }

        i++;
        j = 0;  // Reset column index for the next row
    }
    return 0;
}



int main() {
    dosyaOku();
    return 0;
}
