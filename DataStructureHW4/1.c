#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define N 50000
#define swap(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
typedef struct {
	char* str;
	int ind;
}element;
element randarr[N];
element SWAPTMP;

double Time_Data[5];
long long Compare_Data[5];
long long Swap_Data[5];
char* Name_Data[5] = { "Bubble Sort","Insert Sort","Quick Sort" ,"Merge Sort","Heap Sort" };
int Stable_Data[5];

void mk_n_rand(void);
void mk_c_rand(void);
int check_stable(element arr[]);
void setting_arr(element x[], element y[]);
void Setting_Merge_Sort_Func(element arr[], element tmp[], int l, int r);
void Bubble_Sort(element arr[]);
void Bubble_Sort_Func(element arr[]);
void Insert_Sort(element arr[]);
void Insert_Sort_Func(element arr[]);
void Quick_Sort(element arr[]);
void Quick_Sort_Func(element arr[], int l, int r);
void Merge_Sort(element arr[]);
void Merge_Sort_Func(element arr[], element tmp[], int l, int r);
void Heap_Sort(element arr[]);
void Heap_Sort_Func(element arr[]);

int main(void) {
	srand((unsigned)time(NULL));
	mk_c_rand();
	printf("Number of Instances: %d\n", N);
	setting_arr(randarr, randarr);
	Bubble_Sort(randarr);
	setting_arr(randarr, randarr);
	Insert_Sort(randarr);
	setting_arr(randarr, randarr);
	Quick_Sort(randarr);
	setting_arr(randarr, randarr);
	Merge_Sort(randarr);
	setting_arr(randarr, randarr);
	Heap_Sort(randarr);


	printf("====Sorting Result Summary ===\n");
	printf("Algorithm    | Tims(s)  | Compare            | Swap               | Stable\n");
	printf("--------------------------------------------------------------------------\n");
	for (int i = 0; i < 5; i++) {
		printf("%-13s", Name_Data[i]);
		printf("|%-10lf", Time_Data[i]);
		printf("|%-20lld", Compare_Data[i]);
		printf("|%-20lld", Swap_Data[i]);
		if (Stable_Data[i])printf("|YES\n");
		else printf("|NO\n");
		//printf("|%s\n", Stable_Data[i]);
	}

	for (int i = 0; i < N; i++)free(randarr[i].str);
}

void Heap_Sort(element arr[]){
	FILE* fp = fopen("heap_sort.out", "w");
	printf("=> Starting - Heap Sort\n");
	clock_t start, finish;
	double duraion;
	start = clock();

	Heap_Sort_Func(arr);
	for (int i = 0; i < N; i++) {
		fprintf(fp, "%s ", arr[i].str);
	}

	finish = clock();
	duraion = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("=> Finished\n");
	Time_Data[4] = duraion;
	fclose(fp);
	printf("=> Created - heap_sort.out\n");
	Stable_Data[4] = check_stable(arr);
}
void Heap_Sort_Func(element arr[]) {
	element heap[N + 1];
	int ind = 1;
	for (int i = 0; i < N; i++) {
		heap[ind] = arr[i];
		for (int j = ind; j / 2 > 0; j /= 2) {
			Compare_Data[4]++;
			if (strcmp(heap[j].str, heap[j / 2].str) < 0){
				swap(heap[j], heap[j / 2], SWAPTMP);
				Swap_Data[4]++;
			}
			else break;
		}
		ind++;
	}
	for (int i = 0; i < N; i++) {
		arr[i] = heap[1];
		swap(heap[1], heap[ind - 1], SWAPTMP);
		Compare_Data[4]++;
		Swap_Data[4]++;
		ind--;

		int j = 1;
		while (j * 2 < ind) {
			int child = j * 2;
			if (child + 1 < ind && strcmp(heap[child + 1].str, heap[child].str) < 0) {
				Compare_Data[4]++;
				child++;
			}

			if (strcmp(heap[j].str, heap[child].str) > 0) {
				swap(heap[j], heap[child], SWAPTMP);
				Compare_Data[4]++;
				Swap_Data[4]++;
				j = child;
			}
			else break;
		}
	}
}
void Merge_Sort_Func(element arr[], element tmp[], int l, int r) {
	if (l >= r)return;


	int ind = 0;
	int lower = l;
	int mid = (l + r) / 2;
	int upper = mid + 1;

	Merge_Sort_Func(arr, tmp, l, mid);
	Merge_Sort_Func(arr, tmp, mid + 1, r);


	while (lower <= mid && upper <= r) {
		if (strcmp(arr[lower].str, arr[upper].str) <= 0) {
			Compare_Data[3]++;
			Swap_Data[3]++;
			tmp[ind] = arr[lower];
			lower++;
		}
		else {
			Compare_Data[3]++;
			Swap_Data[3]++;
			tmp[ind] = arr[upper];
			upper++;
		}
		ind++;
	}
	for (; lower <= mid; lower++) {
		Compare_Data[3]++;
		Swap_Data[3]++;
		tmp[ind] = arr[lower];
		ind++;
	}
	for (; upper <= r; upper++) {
		Compare_Data[3]++;
		Swap_Data[3]++;
		tmp[ind] = arr[upper];
		ind++;
	}
	for (ind = 0; l + ind <= r; ind++) {
		arr[l + ind] = tmp[ind];
	}

}
void Merge_Sort(element arr[]){
	FILE* fp = fopen("merge_sort.out", "w");
	printf("=> Starting - Merge Sort\n");
	clock_t start, finish;
	double duraion;
	start = clock();
	element tmp[N];
	Merge_Sort_Func(arr, tmp, 0, N - 1);
	for (int i = 0; i < N; i++) {
		fprintf(fp, "%s ", arr[i].str);
	}

	finish = clock();
	duraion = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("=> Finished\n");
	Time_Data[3] = duraion;
	fclose(fp);
	printf("=> Created - merge_sort.out\n");
	Stable_Data[3] = check_stable(arr);
}
void Quick_Sort_Func(element arr[], int l, int r) {
	if (l >= r)return;
	int lower, upper;
	lower = l;
	upper = r + 1;
	while (lower < upper) {
		lower++;
		while ((lower <= r) && (strcmp(arr[lower].str, arr[l].str) < 0)) {
			Compare_Data[2]++;
			lower++;
		}
		upper--;
		while ((upper >= l + 1) && (strcmp(arr[upper].str, arr[l].str) >= 0)) {
			Compare_Data[2]++;
			upper--;
		}
		if (lower < upper) {
			Swap_Data[2]++;
			swap(arr[lower], arr[upper], SWAPTMP);
		}
	}
	swap(arr[upper], arr[l], SWAPTMP);
	Swap_Data[2]++;
	Quick_Sort_Func(arr, l, upper - 1);
	Quick_Sort_Func(arr, upper + 1, r);
	return;
}
void Quick_Sort(element arr[]) {
	FILE* fp = fopen("quick_sort.out", "w");
	printf("=> Starting - Quick Sort\n");
	clock_t start, finish;
	double duraion;
	start = clock();

	Quick_Sort_Func(arr, 0, N-1);
	for (int i = 0; i < N; i++) {
		fprintf(fp, "%s ", arr[i].str);
	}

	finish = clock();
	duraion = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("=> Finished\n");
	Time_Data[2] = duraion;
	fclose(fp);
	printf("=> Created - quick_sort.out\n");
	Stable_Data[2] = check_stable(arr);
}
void Insert_Sort_Func(element arr[]) {
	for (int i = 1; i < N; i++) {
		element key = arr[i];
		int j = i-1;
		for (; j >= 0;j--) {
			Compare_Data[1]++;
			if (strcmp(arr[j].str, key.str) >0) {
				arr[j + 1] = arr[j];
				Swap_Data[1]++;
			}
			else break;
		}
		arr[j + 1] = key;
		Swap_Data[1]++;
	}
}
void Insert_Sort(element arr[]){
	FILE* fp = fopen("insert_sort.out", "w");
	printf("=> Starting - Insert Sort\n");
	clock_t start, finish;
	double duraion;
	start = clock();

	Insert_Sort_Func(arr);
	for (int i = 0; i < N; i++) {
		fprintf(fp, "%s ", arr[i].str);
	}

	finish = clock();
	duraion = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("=> Finished\n");
	Time_Data[1] = duraion;
	fclose(fp);
	printf("=> Created - insert_sort.out\n");
	Stable_Data[1] = check_stable(arr);
}
void Bubble_Sort_Func(element arr[]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - i - 1; j++) {
			Compare_Data[0]++;
			if (strcmp(arr[j].str,arr[j+1].str)>0) {
				swap(arr[j], arr[j + 1], SWAPTMP);
				Swap_Data[0]++;
			}
		}
	}
}
void Bubble_Sort(element arr[]) {
	FILE* fp = fopen("bubble_sort.out", "w");
	printf("=> Starting - Bubble Sort\n");
	clock_t start, finish;
	double duraion;
	start = clock();

	Bubble_Sort_Func(arr);
	for (int i = 0; i < N; i++) {
		fprintf(fp, "%s ", arr[i].str);
		//printf("%d ", arr[i]);
	}

	finish = clock();
	duraion = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("=> Finished\n");
	Time_Data[0] = duraion;
	fclose(fp);
	printf("=> Created - bubble_sort.out\n");
	Stable_Data[0] = check_stable(arr);
}
void mk_n_rand(void) {
	for (int i = 0; i < N; i++) {
		//randarr[i] = rand() % 1'000'000 + 1;
	}
	return;
}
void mk_c_rand(void) {
	for (int i = 0; i < N; i++) {
		int l = rand() % 20 + 1;
		randarr[i].str = malloc(sizeof(char) * (l + 1));

		int j = 0;
		char tmp[100];
		for (; j < l; j++) {
			tmp[j] = rand() % ('z' - 'a'+1) + 'a';
		}
		tmp[j] = '\0';
		strcpy(randarr[i].str,tmp);
		randarr[i].ind = i;
	}
	return;
}
int check_stable(element arr[])
{
	for (int i = 0; i < N-1; i++) {
		if (strcmp(arr[i].str, arr[i + 1].str) == 0) {
			if (arr[i].ind > arr[i + 1].ind)return 0;
		}
	}
	return 1;
}
void setting_arr(element x[], element y[]) {
	//for (int i = 0; i < N; i++) x[i] = y[i];
	element tmp[N];
	Setting_Merge_Sort_Func(x, tmp, 0, N - 1);
}
void Setting_Merge_Sort_Func(element arr[], element tmp[], int l, int r) {
	if (l >= r)return;


	int ind = 0;
	int lower = l;
	int mid = (l + r) / 2;
	int upper = mid + 1;

	Setting_Merge_Sort_Func(arr, tmp, l, mid);
	Setting_Merge_Sort_Func(arr, tmp, mid + 1, r);


	while (lower <= mid && upper <= r) {
		if (arr[lower].ind< arr[upper].ind) {
			tmp[ind] = arr[lower];
			lower++;
		}
		else {
			tmp[ind] = arr[upper];
			upper++;
		}
		ind++;
	}
	for (; lower <= mid; lower++) {
		tmp[ind] = arr[lower];
		ind++;
	}
	for (; upper <= r; upper++) {
		tmp[ind] = arr[upper];
		ind++;
	}
	for (ind = 0; l + ind <= r; ind++) {
		arr[l + ind] = tmp[ind];
	}
}