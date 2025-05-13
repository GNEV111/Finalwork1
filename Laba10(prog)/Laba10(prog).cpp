#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

#define SIZE_M 10
#define SIZE_A 5
#define SIZE_B 6
#define SIZE_C (SIZE_A + SIZE_B)

void inputArray(int* arr, int size, const char* filename) {
    FILE* file;
    fopen_s(&file, filename, "a");
    if (!file) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < size; i++) {
        int value = rand() % 100;
        fprintf(file, "%d ", value);
    }
    fprintf(file, "\n");
    fclose(file);
}

float calculateAverage(const char* filename, int* arr, int size) {
    FILE* file;
    fopen_s(&file, filename, "r");
    if (!file) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }
    float sum = 0;
    for (int i = 0; i < size; i++) {
        fscanf_s(file, "%d", &arr[i]);
        sum += arr[i];
    }
    fclose(file);
    return sum / size;
}

void combineArrays(const char* filename, int* A, int* B, int* C) {
    FILE* file;
    fopen_s(&file, filename, "r");
    if (!file) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    
    fseek(file, 0, SEEK_SET);  
    char buffer[256];
    fgets(buffer, sizeof(buffer), file);  

    
    for (int i = 0; i < SIZE_A; i++) {
        fscanf_s(file, "%d", &A[i]);
        C[i] = A[i];  
    }

    
    for (int i = 0; i < SIZE_B; i++) {
        fscanf_s(file, "%d", &B[i]);
        C[SIZE_A + i] = B[i];  
    }

    fclose(file);
}

void bubbleSort(int* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}

void writeResultsToFile(const char* filename, float average, int* C) {
    FILE* file = fopen(filename, "a");
    if (file != NULL) {
        fprintf(file, "Среднее арифметическое массива M: %.2f\n", average);
        fprintf(file, "Отсортированный массив C:\n");
        for (int i = 0; i < SIZE_C; i++) {
            fprintf(file, "%d ", C[i]);
        }
        fprintf(file, "\n");
        fclose(file);
    }
    else {
        printf("Ошибка открытия файла для записи.\n");
    }
}

int main() {
    setlocale(LC_ALL, "");
    srand(time(NULL));

    int M[SIZE_M], A[SIZE_A], B[SIZE_B], C[SIZE_C];
    float average = 0.0;
    char dataFile[100], resultFile[100];

    printf("Введите имя файла для данных массивов M: ");
    scanf("%s", dataFile);
    printf("Введите имя файла для вывода результата: ");
    scanf("%s", resultFile);

    FILE* file1;
    fopen_s(&file1, dataFile, "w");
    fclose(file1);

    FILE* file2;
    fopen_s(&file2, resultFile, "w");
    fclose(file2);

    inputArray(M, SIZE_M, dataFile);
    average = calculateAverage(dataFile, M, SIZE_M);
    inputArray(A, SIZE_A, dataFile);
    inputArray(B, SIZE_B, dataFile);

    combineArrays(dataFile, A, B, C);

    bubbleSort(C, SIZE_C);

    writeResultsToFile(resultFile, average, C);

    return 0;
}