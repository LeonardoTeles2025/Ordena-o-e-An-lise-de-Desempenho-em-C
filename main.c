#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

typedef long long ll;

static ll steps; 

#define COUNT_CMP()  (steps++)
#define COUNT_SWAP() (steps++)


void copy_array(int *dst, int *src, int n) {
    for (int i = 0; i < n; ++i) dst[i] = src[i];
}

int *make_random_array(int n) {
    int *a = malloc(sizeof(int) * n);
    if (!a) { perror("malloc"); exit(1); }
    for (int i = 0; i < n; ++i) a[i] = rand() % 1000000;
    return a;
}


void insertion_sort(int *a, int n) {
    for (int i = 1; i < n; ++i) {
        int key = a[i];
        COUNT_SWAP();
        int j = i - 1;
        while (1) {
            if (j < 0) break;
            COUNT_CMP(); 
            if (a[j] > key) {
                a[j + 1] = a[j];
                COUNT_SWAP();
                j--;
            } else break;
        }
        a[j + 1] = key;
        COUNT_SWAP();
    }
}


void quick_swap(int *a, int i, int j) {
    if (i == j) return;
    int t = a[i]; a[i] = a[j]; a[j] = t;
    COUNT_SWAP();
}

int partition_qs(int *a, int low, int high) {
    int pivot = a[high];
    COUNT_SWAP(); 
    int i = low - 1;
    for (int j = low; j <= high - 1; ++j) {
        COUNT_CMP(); 
        if (a[j] < pivot) {
            i++;
            quick_swap(a, i, j);
        }
    }
    quick_swap(a, i + 1, high);
    return i + 1;
}

void quick_sort_rec(int *a, int low, int high) {
    if (low < high) {
        COUNT_CMP(); 
        int pi = partition_qs(a, low, high);
        quick_sort_rec(a, low, pi - 1);
        quick_sort_rec(a, pi + 1, high);
    } else {
       
        COUNT_CMP();
    }
}

void quick_sort(int *a, int n) {
    quick_sort_rec(a, 0, n - 1);
}


void merge(int *a, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int *L = malloc(sizeof(int) * n1);
    int *R = malloc(sizeof(int) * n2);
    if (!L || !R) { perror("malloc"); exit(1); }

    for (int i = 0; i < n1; ++i) { L[i] = a[l + i]; COUNT_SWAP(); }
    for (int j = 0; j < n2; ++j) { R[j] = a[m + 1 + j]; COUNT_SWAP(); }

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        COUNT_CMP(); 
        if (L[i] <= R[j]) {
            a[k++] = L[i++];
            COUNT_SWAP();
        } else {
            a[k++] = R[j++];
            COUNT_SWAP();
        }
    }
    while (i < n1) {
        a[k++] = L[i++];
        COUNT_SWAP();
    }
    while (j < n2) {
        a[k++] = R[j++];
        COUNT_SWAP();
    }
    free(L); free(R);
}

void merge_sort_rec(int *a, int l, int r) {
    if (l < r) {
        COUNT_CMP();
        int m = l + (r - l) / 2;
        merge_sort_rec(a, l, m);
        merge_sort_rec(a, m + 1, r);
        merge(a, l, m, r);
    } else {
        COUNT_CMP(); 
    }
}

void merge_sort(int *a, int n) {
    merge_sort_rec(a, 0, n - 1);
}


double measure_sort(void (*sortf)(int *, int), int *data, int n, ll *out_steps) {
   
    int *work = malloc(sizeof(int) * n);
    if (!work) { perror("malloc"); exit(1); }
    copy_array(work, data, n);

    steps = 0;
    clock_t t0 = clock();
    sortf(work, n);
    clock_t t1 = clock();

    *out_steps = steps;
    double ms = 1000.0 * (double)(t1 - t0) / (double)CLOCKS_PER_SEC;
    free(work);
    return ms;
}

void print_csv_header() {
    printf("metodo,N,caso,passos,tempo_ms\n");
}

void run_benchmark_for_method(const char *name, void (*sortf)(int *, int),
                              int *input, int n, const char *caso) {
    const int runs = 5;
    ll sum_steps = 0;
    double sum_time = 0.0;
    for (int r = 0; r < runs; ++r) {
        ll s = 0;
        double ms = measure_sort(sortf, input, n, &s);
        sum_steps += s;
        sum_time += ms;
    }
    double avg_steps = (double)sum_steps / runs;
    double avg_time = sum_time / runs;
    
    printf("%s,%d,%s,%.0f,%.3f\n", name, n, caso, avg_steps, avg_time);
}


int main(int argc, char **argv) {
    srand((unsigned int) time(NULL));
    print_csv_header();

    
    char rgm_s[64];
    printf("Digite seu RGM (somente dígitos): ");
    if (scanf("%63s", rgm_s) != 1) {
        fprintf(stderr, "Erro na leitura do RGM\n");
        return 1;
    }
    
    int len = 0;
    for (int i = 0; rgm_s[i] != '\0'; ++i) if (isdigit((unsigned char)rgm_s[i])) rgm_s[len++] = rgm_s[i];
    rgm_s[len] = '\0';

    if (len == 0) {
        fprintf(stderr, "RGM vazio depois de filtrar não-dígitos\n");
        return 1;
    }

    int *rgm_arr = malloc(sizeof(int) * len);
    for (int i = 0; i < len; ++i) rgm_arr[i] = rgm_s[i] - '0';


    run_benchmark_for_method("insertion", insertion_sort, rgm_arr, len, "rgm");
    run_benchmark_for_method("quick", quick_sort, rgm_arr, len, "rgm");
    run_benchmark_for_method("merge", merge_sort, rgm_arr, len, "rgm");

    
    int sizes[] = {100, 1000, 10000};
    int nsizes = sizeof(sizes)/sizeof(sizes[0]);
    for (int si = 0; si < nsizes; ++si) {
        int n = sizes[si];
        int *base = make_random_array(n);
        
        run_benchmark_for_method("insertion", insertion_sort, base, n, "aleatorio");
        run_benchmark_for_method("quick", quick_sort, base, n, "aleatorio");
        run_benchmark_for_method("merge", merge_sort, base, n, "aleatorio");
        free(base);
    }

    free(rgm_arr);
    return 0;
}