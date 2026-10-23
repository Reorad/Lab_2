#include "Profiler.h"
#include "constant.h"
#include <iostream>


Profiler prf("Heap building comparisons");

template <typename T>
void swap_numb(T &t1, T &t2) {
    T aux = t1;
    t1 = t2;
    t2 = aux;
}



enum HEAP_TYPE{Min_HEAP, Max_HEAP};

HEAP_TYPE type_global = Min_HEAP;


bool sink_comp(int a, int b, Operation *op){
    op->count();
    
    if(type_global == Min_HEAP){
        return a > b; 
    }
    else
        return a < b;
}

//Heap building methods 

// Sink -> Bottom up

void sink(int *arr, int i , int n, Operation *ass, Operation *comp ){
   
    while(2*i <= n){
        int mini = 2*i; // arr[mini] > arr[mini+1]
        if(2*i+1 <= n && sink_comp(arr[mini], arr[mini+1], comp) ){
            mini++;
        } // arr[i] > arr[mini]
        if(sink_comp(arr[i], arr[mini], comp) ){ // MIN heap <=> arr[i] will receive min (arr[i] < arr[mini] so we comp) 
            swap_numb(arr[i], arr[mini]);   
            (*ass).count(3); // wanna be -> 
            i = mini;
        }
        else{
            break;
        }
    }
}

// for int i = n/2 ; i>1; i--

void build_heap_bottom_up(int *arr, int n, Operation *ass, Operation *comp ){
    for(int i = n/2; i>=1; i--){
        sink(arr,i,n, ass, comp);
    }
}


// Swim -> top up

bool swim_comp(int a, int b, Operation *op){
    op->count();
     if(type_global == Min_HEAP){
        return a < b; 
    }
    else
        return a > b;
}

void swim(int *arr, int i, int n, Operation *ass, Operation *comp ){   

    // arr[i] < arr[i/2]
    while(i>1 && swim_comp(arr[i], arr[i/2], comp) ){
        swap_numb(arr[i],arr[i/2]);
        ass->count(3);
        i/=2;
    }

}
// for int i = n; i>2; i--

void build_heap_top_up(int *arr, int n, Operation *ass, Operation *comp ){
    for(int i = 2; i<=n ; i++){
        swim(arr,i,n, ass, comp);
    }
}

// Heap sorting rn

void Heap_Sort(int *arr, int n){

    Operation ass = prf.createOperation(Heap_Sort_assign,n);
    Operation comp = prf.createOperation(Heap_Sort_comp,n);

    build_heap_bottom_up(arr,n, &ass, &comp);

    int heap_size = n;

    while(heap_size>1){

        swap_numb(arr[1], arr[heap_size]);  
        ass.count(3);
        heap_size--;
        sink(arr,1,heap_size,&ass,&comp);
    }
}

// Run casses 

//Comparative analysis of the two build heap methods in the average case 


// Demo 

int get_left_child(int root){
    return 2*root;
}

int get_right_child(int root){
    return 2*root+1;
}

// Heap min or max i m not gonna change the name btw
bool is_heap(int *arr, int n, HEAP_TYPE t){

    if(t == Min_HEAP){
        for(int i = 1; i<=n ; i++)  {
            int left_child_indx = get_left_child(i);
            int right_child_indx = get_right_child(i);
            if( (left_child_indx <= n && arr[i] > arr[left_child_indx])
                 || ( (right_child_indx <= n) && arr[i] > arr[right_child_indx]) )
                return false;        
        }
        return true;
    }
    else{
        for(int i = 1; i<= n; i++){
            int left_child_indx = get_left_child(i);
            int right_child_indx = get_right_child(i);
            if( (left_child_indx <= n && arr[i] < arr[left_child_indx] )
                || ( (right_child_indx <= n) && arr[i] < arr[right_child_indx]) )
                return false;    
        }
    }
    return true;
}

void print_array(int *arr, int n){

    for(int i = 1; i<=n; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void print_heap_type(int *arr, int n, HEAP_TYPE t){
    char *heap_type_name =(char*)malloc(10*sizeof(char)); // (min -3 heap -4 = 7 + 1 = 8 , 2 for leaway)
    if(t==Min_HEAP){
        strcpy(heap_type_name,"MIN HEAP");
    }
    else{
        strcpy(heap_type_name,"MAX HEAP");
    }
    if(is_heap(arr,n,t)){
       printf("Its a %s \n", heap_type_name);
    }
    else{
        printf("Its not a heap \n");
    }
    print_array(arr,n);
    free(heap_type_name);
}

// Comparing iterative vs recursive sorts

void Iterative_SelectionSort(int *arr, int n, Operation *ass, Operation *comp){

    for(int i=0; i<n-1;i++){
        int mini = i;
        for(int j=i+1; j<n;j++){
            comp->count();
            if(arr[mini] > arr[j]){
                mini = j;
                
            }
        }
        if(i!=mini){
            ass->count(3);
            swap_numb(arr[i] , arr[mini]);
        }
    }


}

void Recursive_Selection_Sort_var2(int *arr, int n, int i, Operation *ass, Operation *comp){

    if(i >= n-1)
        return;
    
    int mini = i;
    for(int j = i+1; j <n; j++){
        comp->count();
        if(arr[mini] > arr[j])
            mini = j;
    }

    if(mini != i){
        ass->count(3);
        swap_numb(arr[i], arr[mini]);
    }
    Recursive_Selection_Sort_var2(arr,n,i+1,ass,comp);
}

//To be honest I could as well just make two global Operation comp and assigments to reduce this insane overhead

int find_mini(int *arr, int n , int j, int mini, Operation *comp){

    if(j==n){
        return mini;
    }

    comp->count();
    if(arr[j] < arr[mini]){
        mini = j;
    }
    return find_mini(arr, n, j+1, mini, comp);
}

void Recursive_SelectionSort(int *arr, int n, int i , Operation *ass, Operation *comp){

    if(i >= n-1)
        return;

    // two recursive functions mini finishes then frees the stack
    int mini = find_mini(arr,n,i+1,i,comp);

    if(mini != i){
        swap_numb(arr[i], arr[mini]);
        ass->count(3);
    }

    Recursive_SelectionSort(arr, n, i+1, ass, comp );

}

void print_entire_array(int *arr, int n){
    if(IsSorted(arr,n)){
        printf("Is sorted \n");
    }
    else{
        printf("Is not sorted \n");
    }
    for(int i = 0; i<n ; i++){
        printf("%d ", arr[i]);
    }
    printf("\n");
}

void Average_case(){

    for(int n = Step_start; n<= Step_final; n+= Step_size){

        for(int j = test; j< nr_test; j+= test_step){
            
            //Swim top up
            FillRandomArray(array_numb, n+1, min_arr, max_arr, false, UNSORTED ); // n = 9999, n = 10000 ok since array numb[10001]
            // looks good for a[0] which not touched to be -1
            array_numb[0] = -1;
            CopyArray(array_numb_aux, array_numb, n+1);
            Operation ass_swim = prf.createOperation(Swim_assign, n);
            Operation comp_swim = prf.createOperation(Swim_comp, n);
            build_heap_top_up(array_numb_aux,n,&ass_swim, &comp_swim);
            // problen arr 100 bullshit value
            //Sink bottom up
            CopyArray(array_numb_aux, array_numb, n+1);
            Operation ass_sink = prf.createOperation(Sink_assign, n);
            Operation comp_sink = prf.createOperation(Sink_comp, n);
            build_heap_bottom_up(array_numb_aux,n,&ass_sink, &comp_sink);
            
        
        }
    }

    prf.addSeries(Swim_tot, Swim_assign, Swim_comp);
    prf.addSeries(Sink_tot, Sink_assign, Sink_comp);

    prf.divideValues(Swim_tot, nr_test);
    prf.divideValues(Swim_assign, nr_test);
    prf.divideValues(Swim_comp, nr_test);

    prf.divideValues(Sink_tot, nr_test);
    prf.divideValues(Sink_assign, nr_test);
    prf.divideValues(Sink_comp, nr_test);

    

    prf.createGroup(Average_Assigments, Swim_assign, Sink_assign);
    prf.createGroup(Average_Comparisons, Swim_comp, Sink_comp);
    prf.createGroup(Average_full, Swim_tot, Sink_tot);

}

void Iter_VS_rec(){
    Operation dummy = prf.createOperation("dummy", 0);
    for(int n = timer_t_start; n<= timer_t_max; n+=timer_t_step){

        for(int z = 0; z<5 ; z++){

            FillRandomArray(array_numb, n, min_arr, max_arr, false, UNSORTED);
            
            prf.startTimer(SS_REC2_Timer,n);
            for(int j = 0; j< time_rep; ++j){
                CopyArray(array_numb_aux, array_numb, n);
                Recursive_Selection_Sort_var2(array_numb_aux,n,0, &dummy, &dummy);
            }
            prf.stopTimer(SS_REC2_Timer,n);

            prf.startTimer(SS_IT_Timer, n);
            for(int j = 0; j< time_rep; ++j){
                CopyArray(array_numb_aux, array_numb, n);
                Iterative_SelectionSort(array_numb_aux,n, &dummy, &dummy);
            }
            prf.stopTimer(SS_IT_Timer,n);

            prf.startTimer(SS_REC_Timer, n);
            for(int j = 0; j< time_rep; ++j){
                CopyArray(array_numb_aux, array_numb, n);
                Recursive_SelectionSort(array_numb_aux,n,0, &dummy, &dummy);
            }
            prf.stopTimer(SS_REC_Timer,n);

        }
    }

     for(int n = ss_serie; n<= ss_max_serie; n+=ss_serie_step){
        for(int j = ss_test; j< ss_test_attempt; j+= ss_test_step ){
            
            // Iterative vs Recursive Selection Sort
            FillRandomArray(array_numb,n,min_arr,max_arr,false, UNSORTED);
            Operation ass_iterative = prf.createOperation(SS_IT_assign,n);
            Operation comp_iterative = prf.createOperation(SS_IT_comp, n);
            CopyArray(array_numb_aux, array_numb,n);
            Iterative_SelectionSort(array_numb_aux,n,&ass_iterative, &comp_iterative);
            

            CopyArray(array_numb_aux, array_numb,n);
            Operation ass_recursive = prf.createOperation(SS_REC_assign,n);
            Operation comp_recursive = prf.createOperation(SS_REC_comp, n);
            Recursive_SelectionSort(array_numb_aux,n,0,&ass_recursive, &comp_recursive);

            CopyArray(array_numb_aux, array_numb,n);
            Operation ass_recursive_var2 = prf.createOperation(SS_REC2_assign,n);
            Operation comp_recursive_var2 = prf.createOperation(SS_REC2_comp, n);
            Recursive_Selection_Sort_var2(array_numb_aux,n,0,&ass_recursive_var2, &comp_recursive_var2);
        }
    }

    prf.addSeries(SS_IT_total, SS_IT_assign, SS_IT_comp);
    prf.addSeries(SS_REC_total, SS_REC_assign, SS_REC_comp);
    prf.addSeries(SS_REC2_total, SS_REC2_assign, SS_REC2_comp);

    prf.divideValues(SS_IT_total, ss_test_attempt);
    prf.divideValues(SS_IT_assign, ss_test_attempt);
    prf.divideValues(SS_IT_comp, ss_test_attempt);

    prf.divideValues(SS_REC_total, ss_test_attempt);
    prf.divideValues(SS_REC_assign, ss_test_attempt);
    prf.divideValues(SS_REC_comp, ss_test_attempt);

    prf.divideValues(SS_REC2_total, ss_test_attempt);
    prf.divideValues(SS_REC2_assign, ss_test_attempt);
    prf.divideValues(SS_REC2_comp, ss_test_attempt);


    prf.createGroup("Timer Iter vs Rec", SS_IT_Timer, SS_REC_Timer, SS_REC2_Timer);

    prf.createGroup("Total Iter vs Rec", SS_IT_total, SS_REC_total, SS_REC2_total);

    prf.createGroup("Assing Iter vs Rec ", SS_IT_assign, SS_REC_assign, SS_REC2_assign);

    prf.createGroup("Comp Iter vs Rec ", SS_IT_comp, SS_REC_comp, SS_REC2_comp);
   

}


//
void Worst_case(){

    for(int n = Step_start; n<= Step_final; n+= Step_size){
            // Min Heap 
            if(type_global == Min_HEAP){
                FillRandomArray(array_numb + 1, n, min_arr, max_arr, false, DESCENDING ); // n = 9999, n = 10000 ok since array numb[10001]

            }
            else{
                FillRandomArray(array_numb + 1, n, min_arr, max_arr, false, ASCENDING );
            }
            array_numb[0] = -1;
            CopyArray(array_numb_aux, array_numb, n+1);
            Operation ass_swim = prf.createOperation(Swim_assign, n);
            Operation comp_swim = prf.createOperation(Swim_comp, n);
            build_heap_top_up(array_numb_aux,n,&ass_swim, &comp_swim);
            // problen arr 100 bullshit value
            //Sink bottom up
            CopyArray(array_numb_aux, array_numb, n+1);
            Operation ass_sink = prf.createOperation(Sink_assign, n);
            Operation comp_sink = prf.createOperation(Sink_comp, n);
            build_heap_bottom_up(array_numb_aux,n,&ass_sink, &comp_sink);

            
        
    }

    prf.addSeries(Swim_tot, Swim_assign, Swim_comp);
    prf.addSeries(Sink_tot, Sink_assign, Sink_comp);
            
    prf.createGroup(Worst_assigments, Swim_assign, Sink_assign);
    prf.createGroup(Worst_Comparisons, Swim_comp, Sink_comp);
    prf.createGroup(Worst_full, Swim_tot, Sink_tot);

}

void Demo(){
    
    int n = 10;

    int arr[11]={-1,11,23,10,2,3,4,5,1,34,22};
    int arr_aux[11];
    
    printf("Demo \n ");

    type_global = Min_HEAP;
    print_heap_type(arr,n, type_global); // should check but tbh I hope I didnt write a heap
    //Dont rly care about them + pdf.reset will erase values
    Operation op1 = prf.createOperation("Demo case", n);
    Operation op2 = prf.createOperation("Demo case", n);

    //Min heap on arr1 top up, bottom 
    CopyArray(arr_aux, arr, n+1);
    build_heap_bottom_up(arr_aux,n, &op1 , &op2);
    print_heap_type(arr_aux, n, type_global);
    
    // top up 
    CopyArray(arr_aux,arr,n+1);
    build_heap_top_up(arr_aux,n,&op1, &op2);
    print_heap_type(arr_aux, n, type_global);

    // If corect both should output Min Heap (not same heap just a min heap)

    type_global = Max_HEAP;
    int arr_sec[11]={-1,121,1,40,3,2,1,22,33,34,22};
    print_heap_type(arr_sec,n,type_global);

    CopyArray(arr_aux , arr_sec, n+1);
    build_heap_bottom_up(arr_aux, n, &op1, &op2);
    print_heap_type(arr_aux,n,type_global);

    CopyArray(arr_aux , arr_sec, n+1);
    build_heap_top_up(arr_aux, n, &op1, &op2);
    print_heap_type(arr_aux,n,type_global);
    
    // both should output Max_Heap (not same heap just a max heap)

    // FOR heap sort i m gonna pass a MAX heap since that would output an ascending order array

    type_global = Max_HEAP;
    CopyArray(arr_aux, arr_sec, n+1);
    Heap_Sort(arr_aux, n);
    printf("Heap Sort on a Max heap since I want an ascending order array \n");

    int sorted_arr[10];
    CopyArray(sorted_arr, arr_aux+1, n);
    printf("Original array : ");
    print_array(arr_sec,n);

    if(IsSorted(sorted_arr,n)){
        printf("Sorted array : ");
        print_array(arr_aux, n);
    }
    else{
        printf("Not sorted \n");
    }


    printf("Iterative vs Recursive Selection Sort \n");
    int arr_old_sorts[10]={3,4,5,2,33,11,22,344,5,123};
    
    CopyArray(array_numb_aux, arr_old_sorts, n);
    print_entire_array(array_numb_aux, n);
    Iterative_SelectionSort(array_numb_aux, n, &op1, &op2);
    print_entire_array(array_numb_aux,n);

    CopyArray(array_numb_aux, arr_old_sorts,n);
    Recursive_SelectionSort(array_numb_aux,n, 0, &op1, &op2 );
    print_entire_array(array_numb_aux,n);

}



int main(){


    if(Demo_state){

        Demo();

    }
    else{
        Average_case();
        prf.reset("Worst case");
        Worst_case();
        prf.reset("Iterative vs Recursive");
        Iter_VS_rec();
        prf.showReport();
    }
    

    printf("Done \n");

}