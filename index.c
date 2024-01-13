#include <stdio.h>
#include <stdlib.h>
#include <string.h> 

#define MAX_BOYUT 7

int matrixA[MAX_BOYUT][MAX_BOYUT];
int matrixB[MAX_BOYUT][MAX_BOYUT];
int matrixS[MAX_BOYUT][MAX_BOYUT];

int gercekBoyut;

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

        char *cell = strtok(line, " ");  
        while (cell != NULL) {
            printf("\nhücre: %s\n", cell);
            matrixA[j][i] = atoi(cell);

            cell = strtok(NULL, " ");
            j++;
        }

        
        i++;
        if(i>MAX_BOYUT){
            printf("Matris boyutu 7 den büyük olamaz.");
            return -1;
        }
        j = 0; 
    }
    
    gercekBoyut = i;
    return 0;
}


void matrisiEkranaYaz(){
    int i, j;
    for (i = 0; i < gercekBoyut ; i++){
        for (j = 0; j < gercekBoyut; j++){
            printf("%d ", matrixA[i][j]);
        }
        printf("\n");
    }

}


int main() {
    dosyaOku();
    matrisiEkranaYaz();
    return 0;
}
