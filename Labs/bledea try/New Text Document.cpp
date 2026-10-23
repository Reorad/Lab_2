/// Fundamental Algorithms Laboratory 3 assignment
/// Heapsort VS Quicksort
/// Name: Bledea Alexandru Cătălin
/// Gruop: 30424

/// !!! OBS: The 1MB stack is to small for the recursive calls of quicksort. I used an 8MB stack

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "Profiler.h"

Profiler profiler("main_profiler");

/// Constants:

const int TRYES_PER_TEST = 20;
const int STEP_SIZE = 100;
const int MIN_N = 100;
const int MAX_N = 100000;

/// Helper functions:

inline void swapInt(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}

void arrCopy(int arr[], int cpy[], int n, int indexedFrom = 0)
{
	for (int i = indexedFrom; i < n + indexedFrom; i++)
		cpy[i] = arr[i];
}

void arrPrint(int arr[], int n, int indexedFrom = 0, bool newline = true)
{
	for (int i = indexedFrom; i < n + indexedFrom; i++)
		printf("%d ", arr[i]);

	if (newline)
		printf("\n");
}

void arrReverse(int arr[], int n)
{
	int i = 0, j = n - 1;
	while (i < j)
	{
		swapInt(arr + i, arr + j);
		i++;
		j--;
	}
}

/// Assignment functions:


/// The functions for heapsort were already covered in the last homework
void sink(int arr[], int n, int i, Operation* as = NULL, Operation* co = NULL)
{
	while (2 * i <= n)
	{
		int mini = 2 * i;
		if (mini + 1 <= n)
		{
			if (co != NULL) co->count();
			if (arr[mini + 1] < arr[mini])
				mini++;
		}

		if (co != NULL) co->count();
		if (arr[mini] < arr[i])
		{
			if (as != NULL) as->count(3);
			swapInt(arr + mini, arr + i);
			i = mini;
		}
		else
			break;
	}
}

void bottomup_buid_heap(int arr[], int n, Operation* as = NULL, Operation* co = NULL)
{
	for (int i = n / 2; i >= 1; i--)
		sink(arr, n, i, as, co);
}

void heapsort(int arr[], int n, Operation* as = NULL, Operation* co = NULL)
{
	bottomup_buid_heap(arr - 1, n, as, co); /// arrays to be sorted are indexed at 0 so I will do this "-1 trick" as a shortcut since the heap is indexed from 1

	for (int i = n - 1; i >= 1; i--)
	{
		if (as != NULL) as->count(3);
		swapInt(arr, arr + i);

		sink(arr - 1, i, 1, as, co);
	}

	/// the result is an array ordered in descending order so we will reverse the array

	if (as != NULL) as->count(n * 3 / 2);
	arrReverse(arr, n);
}



/// We choose a partition element M in the subarray (in this case the last) divide the subarray into two (hopefully equal) parts:
/// the first contains elements smaller or equal to M in any order and the second contains elements greater than M in any order
/// while M is placed in between the two partitions and it's index position is returned by the function
int partition(int arr[], int l, int r, Operation *as = NULL, Operation* co = NULL)
{
	int i = l - 1;
	for (int j = l; j <= r - 1; j++)
	{
		if(co != NULL) co->count();
		if (arr[r] > arr[j])
		{
			i++;

			if (as != NULL) as->count(3);
			swapInt(arr + i, arr + j);
		}
	}

	if (as != NULL) as->count(3);
	swapInt(arr + r, arr + i + 1);

	return i + 1;
}

void quicksort(int arr[], int l, int r, Operation* as = NULL, Operation* co = NULL)
{
	if (l >= r) /// case of array of 1 element (already sorted)
		return;

	int p_idx = partition(arr, l, r, as, co);
	quicksort(arr, l, p_idx - 1, as, co);
	quicksort(arr, p_idx + 1, r, as, co);
}

/// this function takes an already ascending sorted array and modifies where the median of each
/// subarray is so that quicksort only swaps once or twice per call of the partition function
void buildBestArrayForQuicksort(int arr[], int l, int r)
{
	if (l >= r)
		return;

	int m = (l + r) / 2;

	buildBestArrayForQuicksort(arr, l, m - 1);
	buildBestArrayForQuicksort(arr, m + 1, r);

	/// after those two calls the array looks like:
	/// L, L, ... L, M, B, B, .... B
	/// where L are elements lower than the median M and B are elements bigger than the median
	/// so we just swap M and the last B and now the array mimicks the way partition works in the best case
	
	swapInt(arr + m, arr + r);
}

void insertion_sort(int arr[], int n, Operation *as, Operation *co)
{
	for (int i = 1; i < n; i++)
	{
		int j = i - 1;

		if(as != NULL) as->count();
		int buff = arr[i];

		if(co != NULL) co->count();
		while (j >= 0 && arr[j] > buff)
		{
			if(co != NULL) co->count(); /// we count the coparisons once before the while and then for every loop

			if(as != NULL) as->count();
			arr[j + 1] = arr[j];

			j--;
		}

		if (j < i - 1)
		{
			if(as != NULL) as->count();
			arr[j + 1] = buff;
		}
	}
}

void quicksort_hybrid(int arr[], int l, int r, int T = 10, Operation* as = NULL, Operation* co = NULL)
{
	if (l >= r) return;

	if (r - l + 1 <= T)
	{
		insertion_sort(arr + l, r - l + 1, as, co);
		return; 
	}

	int p_idx = partition(arr, l, r, as, co);
	quicksort_hybrid(arr, l, p_idx - 1, T, as, co);
	quicksort_hybrid(arr, p_idx + 1, r, T, as, co);
}


/// Demo and benchmark functions:

void demo_quicksort_hybridization()
{
	printf("quicksort hhybridization demo:\n");

	int n = 8;
	int arr[8] = { 10, 2, 6, 7, 5, 5, 9, 8};

	printf("Initial array: "); arrPrint(arr, n);

	quicksort_hybrid(arr, 0, n - 1, 2);

	printf("Array after quicksort: "); arrPrint(arr, n);
}

void demo_quicksort()
{
	printf("quicksort demo:\n");

	int n = 8;
	int arr[8] = { 9, 2, 1, 7, 8, 6, 2, 5 };

	printf("Initial array: "); arrPrint(arr, n);

	quicksort(arr, 0, n - 1);

	printf("Array after quicksort: "); arrPrint(arr, n);
}

void benchmark_quicksort_average()
{
	int *arr;

	arr = (int*)malloc((MAX_N + 1) * sizeof(int));
	if (arr == NULL) return;

	for (int n = MIN_N; n <= MAX_N; n += STEP_SIZE)
	{
		if (n != MIN_N)
			printf("\33[2K\r");

		printf("quicksort average progress: %d out of %d", n, MAX_N);
		
		Operation as = profiler.createOperation("quicksort_average_assignments", n);
		Operation co = profiler.createOperation("quicksort_average_comparisons", n);

		for (int i = 0; i < TRYES_PER_TEST; i++)
		{
			FillRandomArray(arr, n);

			quicksort(arr, 0, n - 1, &as, &co);
		}
	}

	free(arr);

	profiler.divideValues("quicksort_average_assignments", TRYES_PER_TEST);
	profiler.divideValues("quicksort_average_comparisons", TRYES_PER_TEST);

	profiler.addSeries("quicksort_average_operations", "quicksort_average_assignments", "quicksort_average_comparisons");
}

void benchmark_quicksort_worst()
{
	/// Since out partition function uses the last element as a pivot and because the most amount of swaps happen if the pivot
	/// is greater then every element in the partition interval, the worst case happens if the array is already sorted.
	
	int* arr;

	arr = (int*)malloc((MAX_N + 1) * sizeof(int));
	if (arr == NULL) return;

	for (int n = MIN_N; n <= MAX_N; n += STEP_SIZE)
	{
		if (n != MIN_N)
			printf("\33[2K\r");

		printf("quicksort worst progress: %d out of %d", n, MAX_N);

		Operation as = profiler.createOperation("quicksort_worst_assignments", n);
		Operation co = profiler.createOperation("quicksort_worst_comparisons", n);

		for (int i = 0; i < TRYES_PER_TEST; i++)
		{
			FillRandomArray(arr, n, 1, n, true, 1);

			quicksort(arr, 0, n - 1, &as, &co);
		}
	}

	free(arr);

	profiler.divideValues("quicksort_worst_assignments", TRYES_PER_TEST);
	profiler.divideValues("quicksort_worst_comparisons", TRYES_PER_TEST);

	profiler.addSeries("quicksort_worst_operations", "quicksort_worst_assignments", "quicksort_worst_comparisons");
}

void benchmark_quicksort_best()
{
	/// For the best case we should only swap once or twice per call of the partition function. This happens if each partitioning
	/// chooses the partition element (the one compared to the rest) as the median of that subarray, meaning that there are an
	/// equal amount of elements smaller and bigger than it, so when it is placed in the correct place in the subarray it would be
	/// placed in the middle.
	/// This is somewhat troublesome since we always choose the partition element as the last element in that subarray. To build the
	/// best array we will have to make a recursive function which mimicks the path quicksort would take but swaps the median of each
	/// subarray with the last element of that subarray.
	
	int* arr;

	arr = (int*)malloc((MAX_N + 1) * sizeof(int));
	if (arr == NULL) return;

	for (int n = MIN_N; n <= MAX_N; n += STEP_SIZE)
	{
		if (n != MIN_N)
			printf("\33[2K\r");

		printf("quicksort best progress: %d out of %d", n, MAX_N);

		Operation as = profiler.createOperation("quicksort_best_assignments", n);
		Operation co = profiler.createOperation("quicksort_best_comparisons", n);

		for (int i = 0; i < TRYES_PER_TEST; i++)
		{
			FillRandomArray(arr, n, 1, n, true, 1);
			buildBestArrayForQuicksort(arr, 0, n - 1);

			quicksort(arr, 0, n - 1, &as, &co);
		}
	}

	free(arr);

	profiler.divideValues("quicksort_best_assignments", TRYES_PER_TEST);
	profiler.divideValues("quicksort_best_comparisons", TRYES_PER_TEST);

	profiler.addSeries("quicksort_best_operations", "quicksort_best_assignments", "quicksort_best_comparisons");
}

void benchmark_quicksort_ops()
{
	benchmark_quicksort_average();
	benchmark_quicksort_worst();
	benchmark_quicksort_best();

	profiler.createGroup("quicksort_operations", "quicksort_best_operations", "quicksort_average_operations", "quicksort_worst_operations");
	profiler.createGroup("quicksort_operations_best_vs_average", "quicksort_best_operations", "quicksort_average_operations");

	profiler.showReport();
}

void benchmark_quicksort_vs_heapsort()
{
	int *arr, *arrCpy;

	arr = (int*)malloc((MAX_N + 1) * sizeof(int));
	if (arr == NULL) return;

	arrCpy = (int*)malloc((MAX_N + 1) * sizeof(int));
	if (arrCpy == NULL) return;

	for (int n = MIN_N; n <= MAX_N; n += STEP_SIZE)
	{
		if (n != MIN_N)
			printf("\33[2K\r");

		printf("quicksort vs heapsort progress: %d out of %d", n, MAX_N);

		/// This is the second time we calculate those operations but this time we also use the same array as heapsort
		Operation as1 = profiler.createOperation("quicksort_avg_assignments", n);
		Operation co1 = profiler.createOperation("quicksort_avg_comparisons", n);

		Operation as2 = profiler.createOperation("heapsort_avg_assignments", n);
		Operation co2 = profiler.createOperation("heapsort_avg_comparisons", n);

		for (int i = 0; i < TRYES_PER_TEST; i++)
		{
			FillRandomArray(arr, n);

			arrCopy(arr, arrCpy, n);
			quicksort(arrCpy, 0, n - 1, &as1, &co1);

			arrCopy(arr, arrCpy, n);
			heapsort(arrCpy, n, &as2, &co2);
		}
	}

	free(arr);
	free(arrCpy);

	profiler.divideValues("quicksort_avg_assignments", TRYES_PER_TEST);
	profiler.divideValues("quicksort_avg_comparisons", TRYES_PER_TEST);

	profiler.divideValues("heapsort_avg_assignments", TRYES_PER_TEST);
	profiler.divideValues("heapsort_avg_comparisons", TRYES_PER_TEST);
	
	profiler.addSeries("quicksort_avg_operations", "quicksort_avg_assignments", "quicksort_avg_comparisons");
	profiler.addSeries("heapsort_avg_operations", "heapsort_avg_assignments", "heapsort_avg_comparisons");

	profiler.createGroup("heapsort_vs_quicksort_operations", "quicksort_avg_operations", "heapsort_avg_operations");

	profiler.showReport();
}

void benchmark_quicksort_hybridization_T_variable()
{
	int N = 10000;
	int T_MIN = 1;
	int T_MAX = 100;
	int TRYES = 5;

	int **arr, **arrCpy;

	arr = (int**)malloc(TRYES * sizeof(int*));
	if (arr == NULL) return;

	arrCpy = (int**)malloc(TRYES * sizeof(int*));
	if (arrCpy == NULL) return;

	for (int i = 0; i < TRYES; i++)
	{
		arr[i] = (int*)malloc(MAX_N * sizeof(int));
		if (arr[i] == NULL) return;

		arrCpy[i] = (int*)malloc(MAX_N * sizeof(int));
		if (arrCpy[i] == NULL) return;
	}

	for (int t = 10; t <= 50; t++)
	{
		if (t != 1)
			printf("\33[2K\r");

		printf("quicksort hybridization T variable progress: %d out of %d", t, T_MAX);

		Operation as = profiler.createOperation("quicksort_hyb_t_var_assignments", t);
		Operation co = profiler.createOperation("quicksort_hyb_t_var_comparisons", t);

        // a e ok
		for (int i = 0; i < 5; i++)
			FillRandomArray(arr[i], N, 0, 100000);

		/// For operations

		for (int i = 0; i < TRYES; i++)
			arrCopy(arr[i], arrCpy[i], N);

		for (int i = 0; i < TRYES; i++)
			quicksort_hybrid(arrCpy[i], 0, N - 1, t, &as, &co);

		/// For time

		for (int i = 0; i < TRYES; i++)
			arrCopy(arr[i], arrCpy[i], N);


            
		profiler.startTimer("quicksort_hyb_t_var_time", t) ;
		for (int i = 0; i < TRYES; i++)
			quicksort_hybrid(arrCpy[i], 0, N - 1, t);

		profiler.stopTimer("quicksort_hyb_t_var_time", t);
	}

	for (int i = 0; i < TRYES_PER_TEST; i++)
	{
		free(arr[i]);
		free(arrCpy[i]);
	}

	free(arr);
	free(arrCpy);

	profiler.divideValues("quicksort_hyb_t_var_assignments", TRYES);
	profiler.divideValues("quicksort_hyb_t_var_comparisons", TRYES);
	profiler.addSeries("quicksort_hyb_t_var_operations", "quicksort_hyb_t_var_assignments", "quicksort_hyb_t_var_comparisons");

	profiler.showReport();
}

int main()
{
	/// quicksort_demo();
	//demo_quicksort_hybridization();
	/// benchmark_quicksort_ops();
	/// benchmark_quicksort_vs_heapsort();
	benchmark_quicksort_hybridization_T_variable();

	return 0;
}