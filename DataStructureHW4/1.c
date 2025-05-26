#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<string.h>
#define N 5
#define element char*
#define swap(x,y,t) ((t)=(x),(x)=(y),(y)=(t))
char* randarr[N];
element sortarr[N];
element SWAPTMP;
double Time_Data[5];
long long Compare_Data[5];
long long Swap_Data[5];
char* Name_Data[5] = { "Buuble Sort","Insert Sort","Quick Sort" ,"Merge Sort","Heap Sort" };
char* Stable_Data[5] = { "YES","YES","NO","NO","NO" };

void mk_n_rand(void);
void mk_c_rand(void);
void setting_arr(element x[], element y[]);
void Bubble_Sort(element arr[]);
void Bubble_Sort_Func(element arr[]);
void Insert_Sort(element arr[]);
void Insert_Sort_Func(element arr[]);
void Quick_Sort(element arr[]);
void Quick_Sort_Func(element arr[]);

int main(void) {
	srand((unsigned)time(NULL));
	mk_c_rand();
	printf("Number of Instances: %d\n", N);
	setting_arr(sortarr, randarr);
	Bubble_Sort(sortarr);
	setting_arr(sortarr, randarr);
	Insert_Sort(sortarr);
	setting_arr(sortarr, randarr);
	Quick_Sort(sortarr);


	printf("====Sorting Result Summary ===\n");
	printf("Algorithm    | Tims(s)  | Compare            | Swap               | Stable\n");
	printf("--------------------------------------------------------------------------\n");
	for (int i = 0; i < 5; i++) {
		printf("%-13s", Name_Data[i]);
		printf("|%-10lf", Time_Data[i]);
		printf("|%-20lld", Compare_Data[i]);
		printf("|%-20lld", Swap_Data[i]);
		printf("|%s\n", Stable_Data[i]);
	}
}


void Quick_Sort_Func(element arr[]) {
	return;
}
void Quick_Sort(element arr[]) {
	FILE* fp = fopen("quick_sort.out", "w");
	printf("=> Starting - Quick Sort\n");
	clock_t start, finish;
	double duraion;
	start = clock();

	Insert_Sort_Func(arr);
	for (int i = 0; i < N; i++) {
		fprintf(fp, "%s ", arr[i]);
	}

	finish = clock();
	duraion = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("=> Finished\n");
	Time_Data[1] = duraion;
	fclose(fp);
	printf("=> Created - quick_sort.out\n");
}
void Insert_Sort_Func(element arr[]) {
	for (int i = 1; i < N; i++) {
		element key = arr[i];
		int j = i-1;
		for (; j >= 0;j--) {
			Compare_Data[1]++;
			if (strcmp(arr[j], key) == 1) {
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
		fprintf(fp, "%s ", arr[i]);
	}

	finish = clock();
	duraion = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("=> Finished\n");
	Time_Data[1] = duraion;
	fclose(fp);
	printf("=> Created - insert_sort.out\n");
}
void Bubble_Sort_Func(element arr[]) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N - i - 1; j++) {
			Compare_Data[0]++;
			if (strcmp(arr[j],arr[j+1])==1) {
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
		fprintf(fp, "%s ", arr[i]);
		//printf("%d ", arr[i]);
	}

	finish = clock();
	duraion = (double)(finish - start) / CLOCKS_PER_SEC;
	printf("=> Finished\n");
	Time_Data[0] = duraion;
	fclose(fp);
	printf("=> Created - bubble_sort.out\n");
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
		randarr[i] = malloc(sizeof(char) * (l + 1));

		int j = 0;
		char tmp[100];
		for (; j < l; j++) {
			tmp[j] = rand() % ('z' - 'a'+1) + 'a';
		}
		tmp[j] = '\0';
		strcpy(randarr[i],tmp);
	}
	return;
}
void setting_arr(element x[], element y[]) {
	for (int i = 0; i < N; i++) x[i] = y[i];
}