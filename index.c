#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define MAX_BOYUT 7

int matrixA[MAX_BOYUT][MAX_BOYUT];  // A matirisi - MAX BOYUT 7
int matrixB[MAX_BOYUT][MAX_BOYUT];  // B matirisi - MAX BOYUT 7
int matrixS[MAX_BOYUT][MAX_BOYUT];  // Sonuç matirisi - MAX BOYUT 7

int gercekBoyutA;    // 7 den küçük bir boyut gelirse belleği daha verimli kullanmak için ve B matrisi ile A matris boyutlarının eşit olduğunu kontrol etmek için
int gercekBoyutB;    // 7 den küçük bir boyut gelirse belleği daha verimli kullanmak için ve A matirisi ile B matris boyutlarının eşit olduğunu kontrol etmek için 

int tempSum; // Çarpım sonuçlarının toplamı için kullanılacak.

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;


struct Info{  // Çarpım yapacağım satır ve sütun bilgilerini tutmak için
    int row;
    int col;
};

void *matrixMultiplication(void* params) // matris çarpımı yapan fonksiyon. Parametre olarak satır ve sutun bilgisi alıyor.
{
    struct Info* p = (struct Info *) params;
    int row = p->row;
    int col = p->col;

   
    int temp = 0;
    for(int i = 0; i < gercekBoyutA; i++){
       // printf("A: %d\n", matrixA[row][i]);
       // printf("B: %d\n", matrixB[i][col]);
        temp+=matrixA[row][i] * matrixB[i][col];
        printf("A[%d][%d] * B[%d][%d] = %d * %d = %d\n", row, i, i, col, matrixA[row][i], matrixB[i][col], matrixA[row][i] * matrixB[i][col]);
        
    }
    printf("Hücre Sonucu: %d\n\n", temp);

    pthread_mutex_lock(&mutex);
    tempSum += temp;
    matrixS[row][col] = tempSum;
    pthread_mutex_unlock(&mutex);
    tempSum = 0;
    pthread_exit(NULL);
   
}


int readMatrixA(char file[100]){    // A matirisi okuma fonksiyonu
    FILE *fileA = fopen(file, "r");
    if (fileA == NULL) {
        printf("Matrsi A Dosyası Okuma Hatası\n");
        return -1;
    }
    printf("Matris A dosyası okundu\n");

    char line[50];
    int i = 0, j = 0;

    while (fgets(line, 50, fileA)) {
       //printf("Satır: %s", line);

        char *cell = strtok(line, " ");   // " " boşluk karakteri ile split ediyorum.
        while (cell != NULL) {
            // printf("\nhücre: %s\n", cell);
            matrixA[i][j] = atoi(cell);
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
    
    gercekBoyutA = i;
    return 0;
}


int readMatrixB(char file[100]) {    // B matrisi okuma fonksiyonu
    FILE *fileB = fopen(file, "r");

    if (fileB == NULL) {
        printf("Matrsi B Dosyası Okuma Hatası\n");
        return -1;
    }

     printf("Matris B dosyası okundu\n");

    char line[50];
    int i = 0, j = 0;

    while (fgets(line, 50, fileB)) {
       // printf("Satır: %s", line);

        char *cell = strtok(line, " ");  
        while (cell != NULL) {
            // printf("\nhücre: %s\n", cell);
            matrixB[i][j] = atoi(cell);

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
    
    gercekBoyutB = i;
    return 0;
}


int writeToMatricesScreen(){    // Okunan A ve B matrislerini ekrana yazdırma fonksiyonu
    int i, j;
    printf("\nMATRİS A\n");
    for (i = 0; i < gercekBoyutA ; i++){
        for (j = 0; j < gercekBoyutA; j++){
            printf("%d ", matrixA[i][j]);
        }
        printf("\n");
    }

    printf("\nMATRİS B\n");
    for (i = 0; i < gercekBoyutB ; i++){
        for (j = 0; j < gercekBoyutB; j++){
            printf("%d ", matrixB[i][j]);
        }
        printf("\n");
    }
    printf("\n");


    if(gercekBoyutA!=gercekBoyutB){
        printf("A ve B matris boyutları eşit değildir. ÇARPIM YAPILAMAZ");
        return -1;
    }
    return 0;
}



int createThread(pthread_t threads[MAX_BOYUT][MAX_BOYUT], struct Info params[MAX_BOYUT][MAX_BOYUT]) {   // Thread oluşturduğum fonksiyon
    for(int i = 0; i < gercekBoyutA; i++){  
        for(int j = 0; j < gercekBoyutB; j++){
            // Çarpım işlemi yapacağım satır  ve sütundaki değerleri diziye atıyorum.
            params[i][j].row = i;
            params[i][j].col = j;
            pthread_create(&threads[i][j], NULL, matrixMultiplication, (void *)&params[i][j]);   // // Her bir matris hücresi için bir thread oluşturdum ve matrixMultiplication fonksiyonunu çağırarak çarpım işlemini gerçekleştirdim.
            pthread_join(threads[i][j], NULL); // Çarpım işleminin doğru çalışması için oluşturduğum threadlerin tamamlanması bekliyorum. Yoksa sonuç yanlış çıkıyor.
        }  
    }
    return 0;
}

/*int waitThread(pthread_t threads[MAX_BOYUT][MAX_BOYUT], struct Info params[MAX_BOYUT][MAX_BOYUT]) {  // Bu fonksiyonu çalıştırırsam istediğim çıktıyı vermiyor.
    for(int i = 0; i < gercekBoyutA; i++){
        for(int j = 0; j < gercekBoyutB; j++){
            pthread_join(threads[i][j], NULL);
        }
    }
    //printf("TempSum: %d\n", tempSum);
    return 0;
}*/


int writeResultScreen(){     // Matris sonucunu ekrana bastırıyorum.
    printf("\nÇARPIM SONUCU \n Sonuç Matrisi\n");
    for(int i = 0; i < gercekBoyutA; i++){
        for(int j = 0; j < gercekBoyutB ; j++){
            printf("%3d " , matrixS[i][j]);
        }
        printf("\n");
    }
    return 0;
}



int main() {
    
    pthread_t threads[MAX_BOYUT][MAX_BOYUT];  // Veri tipi pthread_t olan bir dizi tanımlıyorum. Bu dizide threadlerimi tutacağım.
    struct Info params[MAX_BOYUT][MAX_BOYUT];  // Veri tipi Info olan params adında bir dizi tanımlıyorum. Bu dizi satır ve sütun bilgisi tutacak.

    readMatrixA("inputA.txt");  // A matrisini oku
    readMatrixB("inputB.txt");  // B matrisini oku
    
    writeToMatricesScreen();  // A ve B matrislerini ekrana yaz.
    
    createThread(threads,params);  // Thread oluşturduğum fonksiyon
    //waitThread(threads,params);
    writeResultScreen();   // Sonuç Matrisini ekrana yazdırıyorum.
    
    return 0;
}
