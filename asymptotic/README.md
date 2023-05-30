# Analise Assintótica

## Introdução
A análise assintótica é uma técnica utilizada para avaliar o desempenho temporal de um algoritmo em relação ao tamanho dos dados de entrada. Ela tem por objetivo determinar quanto tempo o algoritmo leva para processar dados de entrada específicos. Além disso, a análise assintótica também fornece informações sobre a complexidade, consumo de memória e eficiência do algoritmo.

Nesse contexto, são utilizadas duas notações principais:

**Notação Big O (O):**

* A notação Big O estabelece um limite superior para o tempo de execução do algoritmo, considerando o pior caso possível.
* Ela descreve a taxa de crescimento do tempo de execução à medida que o tamanho dos dados de entrada aumenta.
* Por exemplo, se um algoritmo possui uma complexidade de O(n), isso indica que o tempo de execução aumenta linearmente com o tamanho dos dados de entrada.

**Notação Ômega (Ω):**

* A notação Ômega estabelece um limite inferior para o tempo de execução do algoritmo, considerando o melhor caso possível.
* Ela fornece uma estimativa mínima do tempo de execução, independentemente das variações nos dados de entrada.
* Por exemplo, se um algoritmo possui uma complexidade de Ω(n^2), isso indica que o tempo de execução cresce, no mínimo, de forma quadrática com o tamanho dos dados de entrada.

Essas notações são essenciais para entender o desempenho dos algoritmos e tomar decisões informadas na escolha do algoritmo mais adequado para resolver um determinado problema. Elas permitem comparar o comportamento relativo dos algoritmos e prever como seu desempenho será afetado pelo aumento do tamanho dos dados de entrada.

### Complexidade O(n):
Exemplo de complexidade linear, onde o tempo de execução é proporcional ao tamanho da entrada.

```c
// Exemplo 1:
#include <stdio.h>

void linearSearch(int arr[], int n, int key) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == key) {
            printf("Element found at index %d\n", i);
            return;
        }
    }
    printf("Element not found\n");
}

int main() {
    int arr[] = {5, 2, 7, 10, 4};
    int key = 7;
    int size = sizeof(arr) / sizeof(arr[0]);

    linearSearch(arr, size, key);

    return 0;
}

// Exemplo 2:
#include <stdio.h>

void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void linearTimeExample(int arr[], int n) {
    printf("Array elements: ");
    printArray(arr, n);
}

int main() {
    int arr[] = {2, 5, 1, 4, 3};
    int size = sizeof(arr) / sizeof(arr[0]);

    linearTimeExample(arr, size);

    return 0;
}

```
### Complexidade O(n²):

Exemplo de complexidade quadrática, onde o tempo de execução é proporcional ao quadrado do tamanho da entrada.

```c
// Exemplo 1:

#include <stdio.h>

void printMatrix(int mat[][3], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

void quadraticTimeExample(int mat[][3], int n) {
    printf("Matrix elements:\n");
    printMatrix(mat, n);
}

int main() {
    int mat[][3] = {{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}};
    int size = sizeof(mat) / sizeof(mat[0]);

    quadraticTimeExample(mat, size);

    return 0;
}

// Exemplo 2:
#include <stdio.h>

void bubbleSort(int arr[], int n) {
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

int main() {
    int arr[] = {5, 2, 7, 10, 4};
    int size = sizeof(arr) / sizeof(arr[0]);

    bubbleSort(arr, size);

    printf("Sorted array: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");

    return 0;
}

```

### Complexidade O(log n):
Exemplo de complexidade logarítmica, onde o tempo de execução é proporcional ao logaritmo do tamanho da entrada.

```c
// Exemplo 1:
#include <stdio.h>

int binarySearch(int arr[], int left, int right, int key) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) {
            return mid;
        } else if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int main() {
    int arr[] = {2, 4, 5, 7, 10};
    int key = 5;
    int size = sizeof(arr) / sizeof(arr[0]);

    int index = binarySearch(arr, 0, size - 1, key);

    if (index != -1) {
        printf("Element found at index %d\n", index);
    } else {
        printf("Element not found\n");
    }

    return 0;
}

// Exemplo 2:
#include <stdio.h>

int binarySearch(int arr[], int left, int right, int key) {
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (arr[mid] == key) {
            return mid;
        } else if (arr[mid] < key) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int binarySearchExample(int arr[], int n, int key) {
    return binarySearch(arr, 0, n - 1, key);
}
````


