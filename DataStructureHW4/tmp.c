//#include <stdio.h>
//#include <stdlib.h>
//#include <string.h>
//#include <time.h>
//
//#define N 50000
//#define MAX_LEN 20
//
//typedef struct {
//    char str[MAX_LEN + 1];
//    int original_index;
//} StringItem;
//
//typedef struct {
//    unsigned long compares;
//    unsigned long swaps;
//    double time;
//    int is_stable;
//} SortStats;
//
//void generate_data(StringItem* arr) {
//    for (int i = 0; i < N; i++) {
//        int len = rand() % MAX_LEN + 1;
//        for (int j = 0; j < len; j++) {
//            arr[i].str[j] = 'a' + rand() % 26;
//        }
//        arr[i].str[len] = '\0';
//        arr[i].original_index = i;
//    }
//}
//
//int compare_items(StringItem a, StringItem b, unsigned long* count) {
//    (*count)++;
//    return strcmp(a.str, b.str);
//}
//
//void swap_items(StringItem* a, StringItem* b, unsigned long* count) {
//    (*count)++;
//    StringItem temp = *a;
//    *a = *b;
//    *b = temp;
//}
//
//void bubble_sort(StringItem* data, SortStats* stats) {
//    StringItem* arr = malloc(sizeof(StringItem) * N);
//    memcpy(arr, data, sizeof(StringItem) * N);
//
//    clock_t start = clock();
//    for (int i = 0; i < N - 1; i++) {
//        for (int j = 0; j < N - i - 1; j++) {
//            if (compare_items(arr[j], arr[j + 1], &stats->compares) > 0) {
//                swap_items(&arr[j], &arr[j + 1], &stats->swaps);
//            }
//        }
//    }
//    clock_t end = clock();
//    stats->time = (double)(end - start) / CLOCKS_PER_SEC;
//    stats->is_stable = 1;
//    FILE* fp = fopen("bubble_sort.out", "w");
//    for (int i = 0; i < N; i++) fprintf(fp, "%s\n", arr[i].str);
//    fclose(fp);
//    free(arr);
//}
//
//void insertion_sort(StringItem* data, SortStats* stats) {
//    StringItem* arr = malloc(sizeof(StringItem) * N);
//    memcpy(arr, data, sizeof(StringItem) * N);
//
//    clock_t start = clock();
//    for (int i = 1; i < N; i++) {
//        StringItem key = arr[i];
//        int j = i - 1;
//        while (j >= 0 && compare_items(arr[j], key, &stats->compares) > 0) {
//            arr[j + 1] = arr[j];
//            stats->swaps++;
//            j--;
//        }
//        arr[j + 1] = key;
//    }
//    clock_t end = clock();
//    stats->time = (double)(end - start) / CLOCKS_PER_SEC;
//    stats->is_stable = 1;
//    FILE* fp = fopen("insert_sort.out", "w");
//    for (int i = 0; i < N; i++) fprintf(fp, "%s\n", arr[i].str);
//    fclose(fp);
//    free(arr);
//}
//
//int is_stable_sort(StringItem* original, StringItem* sorted) {
//    for (int i = 1; i < N; i++) {
//        if (strcmp(sorted[i - 1].str, sorted[i].str) == 0 &&
//            sorted[i - 1].original_index > sorted[i].original_index) {
//            return 0;
//        }
//    }
//    return 1;
//}
//
//void quick_sort_rec(StringItem* arr, int left, int right, SortStats* stats) {
//    if (left < right) {
//        StringItem pivot = arr[right];
//        int i = left - 1;
//        for (int j = left; j < right; j++) {
//            if (compare_items(arr[j], pivot, &stats->compares) <= 0) {
//                i++;
//                swap_items(&arr[i], &arr[j], &stats->swaps);
//            }
//        }
//        swap_items(&arr[i + 1], &arr[right], &stats->swaps);
//        int p = i + 1;
//        quick_sort_rec(arr, left, p - 1, stats);
//        quick_sort_rec(arr, p + 1, right, stats);
//    }
//}
//
//void quick_sort(StringItem* data, SortStats* stats) {
//    StringItem* arr = malloc(sizeof(StringItem) * N);
//    memcpy(arr, data, sizeof(StringItem) * N);
//
//    clock_t start = clock();
//    quick_sort_rec(arr, 0, N - 1, stats);
//    clock_t end = clock();
//    stats->time = (double)(end - start) / CLOCKS_PER_SEC;
//    stats->is_stable = is_stable_sort(data, arr);
//    FILE* fp = fopen("quick_sort.out", "w");
//    for (int i = 0; i < N; i++) fprintf(fp, "%s\n", arr[i].str);
//    fclose(fp);
//    free(arr);
//}
//
//void merge(StringItem* arr, int left, int mid, int right, SortStats* stats) {
//    int n1 = mid - left + 1;
//    int n2 = right - mid;
//
//    StringItem* L = (StringItem*)malloc(n1 * sizeof(StringItem));
//    StringItem* R = (StringItem*)malloc(n2 * sizeof(StringItem));
//
//    memcpy(L, &arr[left], n1 * sizeof(StringItem));
//    memcpy(R, &arr[mid + 1], n2 * sizeof(StringItem));
//
//    int i = 0, j = 0, k = left;
//    while (i < n1 && j < n2) {
//        if (compare_items(L[i], R[j], &stats->compares) <= 0) {
//            arr[k++] = L[i++];
//        }
//        else {
//            arr[k++] = R[j++];
//            stats->swaps++;
//        }
//    }
//    while (i < n1) arr[k++] = L[i++];
//    while (j < n2) arr[k++] = R[j++];
//
//    free(L);
//    free(R);
//}
//
//void merge_sort_rec(StringItem* arr, int left, int right, SortStats* stats) {
//    if (left < right) {
//        int mid = (left + right) / 2;
//        merge_sort_rec(arr, left, mid, stats);
//        merge_sort_rec(arr, mid + 1, right, stats);
//        merge(arr, left, mid, right, stats);
//    }
//}
//
//void merge_sort(StringItem* data, SortStats* stats) {
//    StringItem* arr = malloc(sizeof(StringItem) * N);
//    memcpy(arr, data, sizeof(StringItem) * N);
//    clock_t start = clock();
//    merge_sort_rec(arr, 0, N - 1, stats);
//    clock_t end = clock();
//    stats->time = (double)(end - start) / CLOCKS_PER_SEC;
//    stats->is_stable = is_stable_sort(data, arr);
//    FILE* fp = fopen("merge_sort.out", "w");
//    for (int i = 0; i < N; i++) fprintf(fp, "%s\n", arr[i].str);
//    fclose(fp);
//    free(arr);
//}
//
//void heapify(StringItem* arr, int n, int i, SortStats* stats) {
//    int largest = i;
//    int l = 2 * i + 1;
//    int r = 2 * i + 2;
//
//    if (l < n && compare_items(arr[l], arr[largest], &stats->compares) > 0)
//        largest = l;
//
//    if (r < n && compare_items(arr[r], arr[largest], &stats->compares) > 0)
//        largest = r;
//
//    if (largest != i) {
//        swap_items(&arr[i], &arr[largest], &stats->swaps);
//        heapify(arr, n, largest, stats);
//    }
//}
//
//void heap_sort(StringItem* data, SortStats* stats) {
//    StringItem* arr = malloc(sizeof(StringItem) * N);
//    memcpy(arr, data, sizeof(StringItem) * N);
//    clock_t start = clock();
//    for (int i = N / 2 - 1; i >= 0; i--) heapify(arr, N, i, stats);
//    for (int i = N - 1; i >= 0; i--) {
//        swap_items(&arr[0], &arr[i], &stats->swaps);
//        heapify(arr, i, 0, stats);
//    }
//    clock_t end = clock();
//    stats->time = (double)(end - start) / CLOCKS_PER_SEC;
//    stats->is_stable = is_stable_sort(data, arr);
//    FILE* fp = fopen("heap_sort.out", "w");
//    for (int i = 0; i < N; i++) fprintf(fp, "%s\n", arr[i].str);
//    fclose(fp);
//    free(arr);
//}
//
//void print_report(SortStats s, const char* name) {
//    printf("%-14s | %7.3f | %8lu | %6lu | %s\n",
//        name, s.time, s.compares, s.swaps, s.is_stable ? "YES" : "NO");
//}
//
//int main() {
//    srand((unsigned)time(NULL));
//    StringItem* data = malloc(sizeof(StringItem) * N);
//    generate_data(data);
//
//    SortStats stats;
//
//    printf("Algorithm      | Time(s) | Compare | Swap | Stable\n");
//    printf("---------------------------------------------------------------\n");
//    stats = (SortStats){ 0 }; bubble_sort(data, &stats); print_report(stats, "Bubble Sort");
//    stats = (SortStats){ 0 }; insertion_sort(data, &stats); print_report(stats, "Insert Sort");
//    stats = (SortStats){ 0 }; quick_sort(data, &stats); print_report(stats, "Quick Sort");
//    stats = (SortStats){ 0 }; merge_sort(data, &stats); print_report(stats, "Merge Sort");
//    stats = (SortStats){ 0 }; heap_sort(data, &stats); print_report(stats, "Heap Sort");
//
//    free(data);
//    return 0;
//}