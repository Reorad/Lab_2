#include "Profiler.h"
#include "constant.h"

Profiler ob("Avg cases");
int arr[10000];
int arr_aux[10000];

template <typename T>
void swap_func(T& num1, T& num2) {
    T aux = num1;
    num1 = num2;
    num2 = aux;
}

void generate_array(int *arr, int n, int min_val, int max_val, bool identical_items, SortMethod a ){
    FillRandomArray(arr, n, min_val, max_val, identical_items, a);
}

void SelectionSort(int *arr, int n){

    Operation assign_val = ob.createOperation(SS_Sort_asign, n);
    Operation compare_val = ob.createOperation(SS_Sort_comp, n);

    for(int i = 0; i<n; i++){
        int min = i;
        for(int j=i+1; j<n;j++){
            if(arr[min] > arr[j]){
                min = j;
            }

            compare_val.count();
        }
        if(min != i){
            swap_func(arr[i], arr[min]);
            assign_val.count(3);
        }

    }

}

void InsertionSort(int *arr, int n){

    Operation assign_val = ob.createOperation(IS_Sort_asign, n);
    Operation compare_val = ob.createOperation(IS_Sort_comp, n);

    for(int i = 1; i<n; i++){

        int j = i-1;
        int buf = arr[i];
        assign_val.count();

        bool stop_flag = false;

        while(j >= 0 && !stop_flag ){
            compare_val.count();
            if(arr[j] > buf){
                arr[j+1] = arr[j];
                j--;
                assign_val.count();
            }
            else
                stop_flag = true;
        }
        arr[j+1] = buf;
        assign_val.count();
    }
}

void BublaSort(int *arr, int n){

    Operation assign_val = ob.createOperation(BB_Sort_asign, n);
    Operation compare_val = ob.createOperation(BB_Sort_comp, n);

    bool did_sort = false;
    int m = n;
    do{
        did_sort = false;
        for(int i = 0; i< m - 1 ; i++){
            compare_val.count();
            if(arr[i] > arr[i+1]){
                swap_func(arr[i], arr[i+1]);
                assign_val.count(3);
                did_sort = true;
            }
        }
        m--;
    }while(did_sort);
}

void Avg_cases(){

    for(int n = step_start ; n<= final_step ; n+= step_size ){

        for(int i = 0 ; i< attempts_test; i++){
            generate_array(arr, n, 10, 23413,false, UNSORTED);
            CopyArray(arr_aux, arr, n);
            SelectionSort(arr_aux, n);

            CopyArray(arr_aux, arr, n);
            InsertionSort(arr_aux, n);

            CopyArray(arr_aux, arr, n);
            BublaSort(arr_aux, n);
        }
   }
}

void Worst_cases(){

    for(int n = step_start ; n<= final_step ; n+= step_size ){

        for(int i = 0 ; i< attempts_test; i++){
            generate_array(arr, n , 10, 23413, true, ASCENDING);
            int minim_years_till_gta6 = arr[0];
            for(int i = 0 ; i<n;i++){
                arr[i] = arr[i+1];
            }
            arr[n-1] = minim_years_till_gta6;

            CopyArray(arr_aux, arr, n);
            SelectionSort(arr_aux, n);

            generate_array(arr, n, 10, 23413, true, DESCENDING);
            CopyArray(arr_aux, arr, n);
            InsertionSort(arr_aux, n);

            CopyArray(arr_aux, arr, n);
            BublaSort(arr_aux, n);
        }
   }

}

void Best_cases(){

    for(int n = step_start ; n<= final_step ; n+= step_size ){

        for(int i = 0 ; i< attempts_test; i++){
            generate_array(arr, n, 10, 23413, true, ASCENDING);
            CopyArray(arr_aux, arr, n);
            SelectionSort(arr_aux, n);

            CopyArray(arr_aux, arr, n);
            InsertionSort(arr_aux, n);

            CopyArray(arr_aux, arr, n);
            BublaSort(arr_aux, n);
        }
   }

}

void merge_cases(const char *grup_sort_cmp , const char *grup_assing_cmp , const char *grup_comp_cmp){

    ob.addSeries(SS_Sort, SS_Sort_asign, SS_Sort_comp);
    ob.addSeries(IS_Sort, IS_Sort_asign, IS_Sort_comp);
    ob.addSeries(BB_Sort, BB_Sort_asign, BB_Sort_comp);

    ob.divideValues(SS_Sort, attempts_test);
    ob.divideValues(SS_Sort_asign, attempts_test);
    ob.divideValues(SS_Sort_comp, attempts_test);

    ob.divideValues(IS_Sort, attempts_test);
    ob.divideValues(IS_Sort_asign, attempts_test);
    ob.divideValues(IS_Sort_comp, attempts_test);

    ob.divideValues(BB_Sort, attempts_test);
    ob.divideValues(BB_Sort_asign, attempts_test);
    ob.divideValues(BB_Sort_comp, attempts_test);

    ob.createGroup(grup_sort_cmp, SS_Sort, IS_Sort, BB_Sort);
    ob.createGroup(grup_comp_cmp, SS_Sort_comp, IS_Sort_comp, BB_Sort_comp);
    ob.createGroup(grup_assing_cmp,SS_Sort_asign, IS_Sort_asign, BB_Sort_asign);

}

void print_that(const char *title, int n, int *array){

    printf("%s : \n", title);

    for(int i = 0 ; i<n ; i++){
        printf("%d ", array[i]);
    }
    printf("\n");
}

void demo(){

    int a[10]={7,6,2,1,5,4,3,2,9,111};
    int n = 10;
    int b[10];
    int gta6[10]={9, 9, 7, 6, 6, 4, 3, 3, 2, 1};

    print_that("Original 1", n, gta6);

    CopyArray(b,a,n);
    SelectionSort(b,n);
    print_that("Selection Sort", n, b);

    CopyArray(b,a,n);
    InsertionSort(b,n);
    print_that("Insertion Sort",n,b);

    CopyArray(b,a,n);
    BublaSort(b,n);
    print_that("Buble Sort",n,b);

    print_that("Original 2", n, gta6);

    CopyArray(b,gta6,n);
    SelectionSort(b,n);
    print_that("Selection Sort", n, b);

    CopyArray(b,gta6,n);
    InsertionSort(b,n);
    print_that("Insertion Sort",n,b);

    CopyArray(b,gta6,n);
    BublaSort(b,n);
    print_that("Buble Sort",n,b);

}

int main(){

    if(demo_state){
        demo();
    }
    else
    {
        Avg_cases();
        merge_cases("Compare alg avg", "Compare asign avg", "Compare comp avg");
        ob.createGroup("Bubble vs Selection sort", SS_Sort, BB_Sort);
        ob.createGroup("Compare_comp_avg Buble and Insertion", IS_Sort_comp, BB_Sort_comp);

        ob.reset("Best cases");
        Best_cases();
        merge_cases("Compare alg best", "Compare asign best", "Compare comp best");
        ob.createGroup("Insertion vs Bubble best", IS_Sort, BB_Sort);
        ob.createGroup("Insertion vs Bubble comp best", IS_Sort_comp, BB_Sort_comp);

        ob.reset("Worst cases");
        Worst_cases();
        merge_cases("Compare alg worst", "Compare asign worst", "Compare comp worst");

    }

    ob.showReport();

    printf("done \n");

}
