#ifndef _CONSTANT_H
#define _CONSTANT_H

#include <stdio.h>
#include "Profiler.h"

#define NMAX 10001
#define arr_min 23
#define arr_max 49167



const bool demo_state = false;
const int Step_Initial = 100;
const int Step_Size = 100;
const int Step_Final = 10000;

const int Test_start = 1;
const int Test_attemtps = 10;
const int Test_step = 1;


//Names for Sortings
const char *Heap_Sort_assign = "HeapSort Assigns";
const char *Heap_Sort_comp = "HeapSort Comps";
const char *Heap_Sort_total = "HeapSort Total";

const char *Quick_Sort_assign = "QuickSort Assigns";
const char *Quick_Sort_comp = "QuickSort Comps";
const char *Quick_Sort_total = "QuickSort Total";

// QUICKSORTING comparing

const char *Quick_Sort_Average_Assign = "QuickSort Average assings";
const char *Quick_Sort_Average_Comp = "QuickSort Average comps";
const char *Quick_Sort_Average_Total = "QuickSort Average Total";

const char *Quick_Sort_Worst_Assign = "QuickSort Worst assings";
const char *Quick_Sort_Worst_Comp = "QuickSort Worst comps";
const char *Quick_Sort_Worst_Total = "QuickSort Worst Total";

const char *Quick_Sort_Best_Assign = "QuickSort Best assings";
const char *Quick_Sort_Best_Comp = "QuickSort Best comps";
const char *Quick_Sort_Best_Total = "QuickSort Best Total";

// Running constants 

const int T_running_tine = 500;

template <typename T>
void swap_func(T& num1, T& num2) {
    T aux = num1;
    num1 = num2;
    num2 = aux;
}

void print_array(int *arr, int start_pos, int final_pos){
    
    for(int i = start_pos; i< final_pos ;i++){
        printf("%d ", arr[i]);
    }
    printf("\n");

}





#endif