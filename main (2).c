#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// ---------------------------------------------------------
// Função Bubble Sort com contagem de passos
// ---------------------------------------------------------
long long bubbleSort(int v[], int n) {
    long long passos = 0;  // Contador de operações-chave

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - 1 - i; j++) {
            passos++; // Comparação

            if (v[j] > v[j + 1]) {
                int temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
                passos += 3; // Troca conta como 3 operações
            }
        }
    }
    return passos;
}

// ---------------------------------------------------------
// Gera vetor aleatório
// ---------------------------------------------------------
void gerarAleatorio(int v[], int n) {
    for (int i = 0; i < n; i++)
        v[i] = rand() % 10000;
}

// ---------------------------------------------------------
// Copia vetor
// ---------------------------------------------------------
void copiar(int dest[], int orig[], int n) {
    for (int i = 0; i < n; i++)
        dest[i] = orig[i];
}

// ---------------------------------------------------------
// Função principal
// ---------------------------------------------------------
int main() {
    srand(time(NULL));

    char rgm[16];
    printf("Digite seu RGM (8 digitos): ");
    scanf("%8s", rgm);

    int vrgm[8];

    // Converter para vetor de inteiros
    for (int i = 0; i < 8; i++)
        vrgm[i] = rgm[i] - '0';

    // -----------------------------------------------------
    // ORDENAR RGM COM BUBBLE SORT
    // -----------------------------------------------------
    int copiaRgm[8];
    copiar(copiaRgm, vrgm, 8);

    clock_t t0 = clock();
    long long passosRgm = bubbleSort(copiaRgm, 8);
    double tempoRgm = (clock() - t0) * 1000.0 / CLOCKS_PER_SEC;

    printf("\n===== SAÍDA CSV =====\n");
    printf("metodo,N,caso,passos,tempo_ms\n");
    printf("bubble,8,rgm,%lld,%.3f\n", passosRgm, tempoRgm);

    // -----------------------------------------------------
    // BENCHMARK COM 3 TAMANHOS
    // -----------------------------------------------------
    int tamanhos[3] = {100, 1000, 10000};

    for (int t = 0; t < 3; t++) {
        int N = tamanhos[t];

        int *v = malloc(N * sizeof(int));
        int *copia = malloc(N * sizeof(int));

        // Gerar vetor aleatório
        gerarAleatorio(v, N);
        copiar(copia, v, N);

        // Bubble Sort
        t0 = clock();
        long long passos = bubbleSort(copia, N);
        double tempo = (clock() - t0) * 1000.0 / CLOCKS_PER_SEC;

        printf("bubble,%d,aleatorio,%lld,%.3f\n", N, passos, tempo);

        free(v);
        free(copia);
    }

    return 0;
}