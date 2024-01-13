# Multi-Threaded Matrix Multiplication in C

Bu program, C programlama dili kullanılarak iki matrisin çarpımını (Matrix Multiplication) gerçekleştiren bir örnektir. Çarpım işlemleri, multi-threading kullanılarak gerçekleştirilmekte ve sonuçlar global bir 2 boyutlu diziye yazılmaktadır.


## Matris Çarpımı

İki matrisin çarpımı, A (M satır ve K sütun) ve B (K satır ve N sütun) matrislerinin C çarpımı şeklinde ifade edilir (C = A x B). Çarpım matrisinin her elemanı, bir satırın bir sütunuyla çarpılması ve bu çarpma sonuçlarının toplanmasıyla elde edilir.

Çarpım işlemleri şu adımları içerir:

    Çarpım sonuçlarını toplamak için her bir satır ve sütun için bir thread oluşturulur.
    Her thread, ilgili satır ve sütunu çarpar ve sonuçları "tempSum" adlı ortak değişkende toplar.
    Sonuç, global 2 boyutlu bir diziye yazılır, bu işlem sırasında uygun senkronizasyon mekanizmaları kullanılır.

Bu program, çarpım işlemlerini multi-threading kullanarak eşzamanlı olarak gerçekleştirir ve sonuç matrisini global bir dizi üzerinde tutar.


## İçerik

- Program, A ve B matrislerini "inputA.txt" ve "inputB.txt" dosyalarından okur.
- Kullanıcı tarafından sağlanan matrislerin boyutu en fazla 7x7 olabilir.
- Çarpım işlemleri için her bir satır ve sütun çarpımı için bir thread oluşturulur.
- Her bir thread, çarpım sonuçlarını toplamak için "tempSum" adlı ortak bir değişken kullanır.
- Multi-threading işlemleri için uygun senkronizasyon mekanizmaları (lock, mutex, semaphore vb.) kullanılır.
- Sonuç matrisi, global 2 boyutlu bir dizide tutulur ve ekrana bastırılır.

## Kullanım

Programı derlemek ve çalıştırmak için aşağıdaki komutları kullanın:

```bash
gcc -o my_program index.c -pthread
./my_program





## Multi-Threaded Matrix Multiplication in C

This program is an example of matrix multiplication using the C programming language. Matrix multiplication operations are performed using multi-threading, and the results are written to a global 2-dimensional array.

## Matrix Multiplication

The multiplication of two matrices, A (M rows and K columns) and B (K rows and N columns), is expressed as C = A x B. Each element of the multiplication matrix is obtained by multiplying a row by a column, and then summing up these multiplication results.

The multiplication process includes the following steps:

    - Create a thread for each row and column to sum up the multiplication results.
    - Each thread multiplies the respective row and column and sums up the results in a shared variable called "tempSum."
    - The result is written to a global 2-dimensional array, using appropriate synchronization mechanisms during this process.

This program performs multiplication operations concurrently using multi-threading and keeps the result matrix in a global array.

## Content

- The program reads matrices A and B from the "inputA.txt" and "inputB.txt" files.
- The size of matrices provided by the user can be at most 7x7.
- A thread is created for each row and column multiplication operation.
- Each thread uses a shared variable named "tempSum" to sum up the multiplication results.
- Suitable synchronization mechanisms (lock, mutex, semaphore, etc.) are used for multi-threading operations.
- The result matrix is stored in a global 2-dimensional array and printed to the screen.

## Usage

Instructions for running the program:

```bash
gcc -o my_program index.c -pthread
./my_program
