#include <stdio.h>
#include "constant.h"
#include "Profiler.h"

Profiler prf("QuickSort");

Operation *HP_Ass = nullptr;
Operation *HP_Comp = nullptr;
Operation *QS_Ass = nullptr;
Operation *QS_Comp = nullptr;

const int MAX_THRESHOLD = 50;
const int MIN_THRESHOLD = 5;
const int STEP_TH = 1;

Operation *QS_Th_Ass; // 10 to 10 ....
Operation *QS_Th_Comp;

void deinitialize_global_operations(){
    HP_Ass = nullptr;
    HP_Comp = nullptr;
    QS_Ass = nullptr;
    QS_Comp = nullptr;
}

//QuickSorting 
int Partition(int *arr, int l , int r ){


    int i = l-1;
    for(int j = l ; j<r ; j++){
        QS_Comp -> count();
        if(arr[j] < arr[r]){
            i++;
            QS_Ass -> count(3);
            swap_func(arr[j], arr[i]);
        }
    }

    QS_Ass -> count(3);
    swap_func(arr[i+1], arr[r]); 

    return i+1;
}

void QuickSort(int *arr, int l, int r){

    if(l>=r){
        return;
    }

    int pos = Partition(arr, l,r);
    QuickSort(arr,l,pos-1);
    QuickSort(arr,pos+1,r);

}


void BisCase(int *arr, int l, int r){

    if(l >= r)
        return;

    int mid = (l+r)/2;

    BisCase(arr, l, mid-1);
    BisCase(arr, mid+1, r);

    swap_func(arr[mid], arr[r]);      
}

//HeapSorting

bool sink_comp(int a, int b){
    HP_Comp->count();
    return a < b;
}

void sink(int *arr, int i , int n){
   
    while(2*i <= n){
        int maxi = 2*i; // arr[mini] > arr[mini+1]
        if(2*i+1 <= n && sink_comp(arr[maxi], arr[maxi+1]) ){
            maxi++;
        } // arr[i] < arr[mini]
        if(sink_comp(arr[i], arr[maxi]) ){ // MIN heap <=> arr[i] will receive min (arr[i] < arr[mini] so we comp) 
            swap_func(arr[i], arr[maxi]);   
            HP_Ass->count(3);
            i = maxi;
        }
        else{
            break;
        }
    }
}

// for int i = n/2 ; i>1; i--

void build_heap_bottom_up(int *arr, int n ){
    for(int i = n/2; i>=1; i--){
        sink(arr,i,n );
    }
}

void Heap_Sort(int *arr, int n){

    

    build_heap_bottom_up(arr,n );

    int heap_size = n;

    while(heap_size>1){

        swap_func(arr[1], arr[heap_size]);  
        HP_Ass->count(3);
        heap_size--;
        sink(arr,1,heap_size);
    }
}

void Average_Cases_QS_vs_HS(){

    for(int n = Step_Initial; n <= Step_Final; n+= Step_Size){
        
        printf("Comparing HeapSort with QuickSort avg case n : %d \n", n);

        int *arr_initial = (int*)malloc((n+1)*sizeof(int));
        int *arr_copy = (int*)malloc((n+1)*sizeof(int));

        arr_initial[0] = -1;
        arr_copy[0] = -1;

        for(int i = Test_start; i<=Test_attemtps; i+= Test_start){

            FillRandomArray(arr_initial+1,n,arr_min,arr_max, false, UNSORTED);
            
            CopyArray(arr_copy+1, arr_initial + 1, n);
            Operation ass_HS = prf.createOperation(Heap_Sort_assign,n);
            Operation comp_HS = prf.createOperation(Heap_Sort_comp,n);
            HP_Ass = &ass_HS;
            HP_Comp = &comp_HS;
            Heap_Sort(arr_copy, n);


            CopyArray(arr_copy+1, arr_initial + 1, n);
            Operation ass_QS = prf.createOperation(Quick_Sort_assign,n);
            Operation comp_QS = prf.createOperation(Quick_Sort_comp,n);
            QS_Ass = &ass_QS;
            QS_Comp = &comp_QS;
            QuickSort(arr_copy,1,n);
            

            deinitialize_global_operations();
        }

        

        //prf.createGroup()


        free(arr_initial);
        free(arr_copy);
    }

    prf.divideValues(Heap_Sort_assign, Test_attemtps);
    prf.divideValues(Heap_Sort_comp, Test_attemtps);
    prf.divideValues(Quick_Sort_comp, Test_attemtps);
    prf.divideValues(Quick_Sort_assign, Test_attemtps);

    prf.addSeries(Quick_Sort_total, Quick_Sort_assign, Quick_Sort_comp );
    prf.addSeries(Heap_Sort_total, Heap_Sort_assign, Heap_Sort_comp );
    
    prf.createGroup("Heap vs Quick - Assign ", Quick_Sort_assign, Heap_Sort_assign );
    prf.createGroup("Heap vs Quick - Comp ", Quick_Sort_comp, Heap_Sort_comp );
    prf.createGroup("Heap vs Quick - Total ", Quick_Sort_total, Heap_Sort_total );

}

void QuickSort_Comparisons(){


    for(int n = Step_Initial; n <= Step_Final; n+= Step_Size){
        
        printf("Comparing QuickSorts n : %d \n", n);

        int *arr_initial = (int*)malloc((n+1)*sizeof(int));
        int *arr_copy = (int*)malloc((n+1)*sizeof(int));


        arr_initial[0] = -1;
        arr_copy[0] = -1;
        // arr_initial_worst[0] =-1;
        // arr_initial_best[0] = -1;

        for(int i = Test_start; i<=Test_attemtps; i+= Test_start){
            
            //Average
            FillRandomArray(arr_initial+1,n,arr_min,arr_max, false, UNSORTED);
            CopyArray(arr_copy+1, arr_initial + 1, n);
            Operation ass_Avg_QS = prf.createOperation(Quick_Sort_Average_Assign,n);
            Operation comp_Avg_QS = prf.createOperation(Quick_Sort_Average_Comp,n);
            QS_Ass = &ass_Avg_QS;
            QS_Comp = &comp_Avg_QS;
            QuickSort(arr_copy,1,n);
    
            deinitialize_global_operations();
        }

         //Worst
        FillRandomArray(arr_initial+1, n, arr_min, arr_max, true, ASCENDING);
        CopyArray(arr_copy+1, arr_initial + 1, n);
        Operation ass_Worst_QS = prf.createOperation(Quick_Sort_Worst_Assign,n);
        Operation comp_Worst_QS = prf.createOperation(Quick_Sort_Worst_Comp,n);
        QS_Ass = &ass_Worst_QS;
        QS_Comp = &comp_Worst_QS;
        QuickSort(arr_copy,1,n);

            //Best 
        FillRandomArray(arr_initial+1, n, arr_min, arr_max, true, ASCENDING);
        
        CopyArray(arr_copy+1, arr_initial + 1, n);
        BisCase(arr_copy,1,n);
        Operation ass_BEST_QS = prf.createOperation(Quick_Sort_Best_Assign,n);
        Operation comp_BEST_QS = prf.createOperation(Quick_Sort_Best_Comp,n);
        QS_Ass = &ass_BEST_QS;
        QS_Comp = &comp_BEST_QS;
        QuickSort(arr_copy,1,n);

        deinitialize_global_operations();



        //prf.createGroup()


        free(arr_initial);
        free(arr_copy);
    }


    prf.divideValues(Quick_Sort_Average_Assign, Test_attemtps);
    prf.divideValues(Quick_Sort_Average_Comp, Test_attemtps);
    prf.addSeries(Quick_Sort_Average_Total, Quick_Sort_Average_Assign, Quick_Sort_Average_Comp);
    prf.addSeries(Quick_Sort_Best_Total, Quick_Sort_Best_Assign, Quick_Sort_Best_Comp);
    prf.addSeries(Quick_Sort_Worst_Total, Quick_Sort_Worst_Assign, Quick_Sort_Worst_Comp); 

    prf.createGroup("Total QuickSorts", Quick_Sort_Average_Total, Quick_Sort_Best_Total, Quick_Sort_Worst_Total);
    prf.createGroup("Assigments QuickSorts", Quick_Sort_Average_Assign, Quick_Sort_Best_Assign, Quick_Sort_Worst_Assign);
    prf.createGroup("Comparisons QuickSorts", Quick_Sort_Average_Comp, Quick_Sort_Best_Comp, Quick_Sort_Worst_Comp);
    
    prf.createGroup("Total Quick AVG BEST", Quick_Sort_Average_Total, Quick_Sort_Best_Total);


}


// Insertion Sort + QuickSort with Hybridization 

void Insertion_Sort(int *arr, int l, int r){

    for(int i = l+1; i<= r; i++){
        
        int j = i-1;
        int buf = arr[i];
        QS_Th_Ass -> count();
        bool stop_flag = false;

        while(j>=l && !stop_flag){
            QS_Th_Comp->count();
            if(arr[j] > buf){
                arr[j+1] = arr[j];
                j--;
                QS_Th_Ass -> count();
            }
            else{
                stop_flag = true;
            }
        }
        arr[j+1] = buf;
        QS_Th_Ass -> count();

    }

}

int Partition_Hybrid(int *arr, int l , int r ){

    int i = l-1;
    for(int j = l ; j<r ; j++){
        QS_Th_Comp -> count();
        if(arr[j] < arr[r]){
            i++;
            QS_Th_Ass -> count(3);
            swap_func(arr[j], arr[i]);
        }
    }

    QS_Th_Ass->count(3);
    swap_func(arr[i+1], arr[r]); 

    return i+1;
}


void QuickSort_Hybrid_DIESEL_ELECTRIC(int *arr, int l, int r, int Threshold){

    if(l>=r)
        return;
    
    if(r-l+1 < Threshold){
        Insertion_Sort(arr, l, r);
    }else{
        int pos = Partition_Hybrid(arr,l,r);
        QuickSort_Hybrid_DIESEL_ELECTRIC(arr,l, pos-1, Threshold);
        QuickSort_Hybrid_DIESEL_ELECTRIC(arr,pos+1,r, Threshold);

    }
    
}

// Threshold Value after evaluation is around 20 

void Threshold_Average(){

    int n = 10000;

    // from 100 , 100 till 1000'
    // for(int n = Step_Initial; n<= 2500; n+= Step_Size){
        int *arr_init=(int*)malloc((n+1) * sizeof(int));
        int *arr_copy = (int*)malloc((n+1) * sizeof(int));

        arr_init[0] = -1;
        arr_copy[0] = -1;

        for(int i = Test_start; i<= 5; i+= Test_step){
            printf("Running Threhsold values rn %d \n", n);
            // array dooo sorting with threshold 0 then thershold 10, .... 
            FillRandomArray(arr_init + 1, n, arr_min, arr_max, false, UNSORTED);
            
            for(int j = MIN_THRESHOLD ; j <= MAX_THRESHOLD ; j+= STEP_TH){
                CopyArray(arr_copy + 1, arr_init + 1, n);
                
                Operation ass = prf.createOperation("Assign Th",j);
                Operation cmp = prf.createOperation("Comps Th",j);

                // can use those for Hibrid
                QS_Th_Ass = &ass; // 10 to 10 ....
                QS_Th_Comp =&cmp;

                QuickSort_Hybrid_DIESEL_ELECTRIC(arr_copy,1,n,j);

                
            }
            QS_Th_Ass = nullptr;
            QS_Th_Comp = nullptr;
        }   
        // divide series now then add them up do a big cmp and see finally the threshold from comparisons 
        // then runtime run both make graphs for each add them up
        prf.divideValues("Assign Th",5);
        prf.divideValues("Comps Th",5);

        prf.addSeries("Total QS operations", "Assign Th", "Comps Th");

        free(arr_copy);
        free(arr_init);
    }

void Threshold_Average_Runtime(){

    int n = 10000;

    // for(int n = Step_Initial; n<= 2500; n+= Step_Size){

        int *arr_init=(int*)malloc((n+1) * sizeof(int));
        int *arr_copy = (int*)malloc((n+1) * sizeof(int));

        arr_init[0] = -1;
        arr_copy[0] = -1;

        for(int i = Test_start; i<= Test_attemtps; i+= Test_step){
            printf("Running Time Threhsold values rn %d \n", n);
            
            FillRandomArray(arr_init + 1, n, arr_min, arr_max, false, UNSORTED);
            
            for(int j = MIN_THRESHOLD ; j <= MAX_THRESHOLD ; j+= STEP_TH){                
                Operation ass = prf.createOperation("Assign Th",j);
                Operation cmp = prf.createOperation("Comps Th",j);

                QS_Th_Ass = &ass;
                QS_Th_Comp = &cmp;

                prf.startTimer("Running time comp", j);
                for(int z = 0; z<T_running_tine; z++){
                    CopyArray(arr_copy + 1, arr_init + 1, n);
                    QuickSort_Hybrid_DIESEL_ELECTRIC(arr_copy,1,n,j);
                }
                prf.stopTimer("Running time comp",j);

                printf("Runn test %d at Threshold %d \n",i, j);

            }

        }   


        free(arr_copy);
        free(arr_init);
}

void Create_Run_Grups(){
    prf.createGroup("Assigns vs Comparisons", "Assign Th", "Comps Th" );
    prf.createGroup("Total Operation Th", "Total QS operations" );
    prf.createGroup("Running time Th","Running time comp" );
   
}

const int Threshold_val_operations = 10;


// Compare QuickSort and HibrdQuickSort

void Operation_comp_QS_vs_HQS(){

        for(int n=Step_Initial; n<= Step_Final; n+= Step_Size){

        int *arr_init =(int*)malloc((n+1) * sizeof(int));
        int *arr_coppy =(int*)malloc((n+1) * sizeof(int));
        
        arr_init[0] = -1;
        arr_coppy[0] = -1;

        for(int i = Test_start; i<= 5; i+= Test_step){

            printf("Opearion comparisons QS : test %d , n %d \n ", i, n);

            FillRandomArray(arr_init+1,n, arr_min, arr_max, false, UNSORTED);
            CopyArray(arr_coppy+1, arr_init+1, n);

            Operation ass_QS_reg = prf.createOperation("Regular Ass QS", n);
            Operation cmp_QS_reg = prf.createOperation("Regular Comp QS", n);
            QS_Ass = &ass_QS_reg;
            QS_Comp = &cmp_QS_reg;
            QuickSort(arr_coppy,1,n);

            CopyArray(arr_coppy+1, arr_init+1, n);

            Operation ass_QS_hyb = prf.createOperation("Hybrid Ass QS", n);
            Operation cmp_QS_hyb = prf.createOperation("Hybrid Comp QS", n);
            QS_Th_Ass = &ass_QS_hyb;
            QS_Th_Comp = &cmp_QS_hyb;
            QuickSort_Hybrid_DIESEL_ELECTRIC(arr_coppy,1,n, Threshold_val_operations);

        }

        free(arr_init);
        free(arr_coppy);

        QS_Ass = nullptr;
        QS_Comp = nullptr;
        QS_Th_Ass = nullptr; 
        QS_Th_Comp = nullptr;
    }

    prf.divideValues("Regular Ass QS", 5);
    prf.divideValues("Regular Comp QS", 5);
    prf.divideValues("Hybrid Ass QS", 5);
    prf.divideValues("Hybrid Comp QS" , 5);

    prf.addSeries("QS_Reg_total", "Regular Ass QS", "Regular Comp QS" );
    prf.addSeries("QS_Hyb_total", "Hybrid Ass QS", "Hybrid Comp QS" );


    prf.createGroup("QS_Compare_TOTAL_Hybrid_REG", "QS_Reg_total", "QS_Hyb_total" );
    prf.createGroup("QS_Compare_Assigments", "Regular Ass QS", "Hybrid Ass QS" );
    prf.createGroup("QS_Compare_Compare", "Regular Comp QS", "Hybrid Comp QS" );
    

}

void Operation_comp_QS_vs_HQS_runtime(){

        for(int n=Step_Initial; n<= Step_Final; n+= Step_Size){

        int *arr_init =(int*)malloc((n+1) * sizeof(int));
        int *arr_coppy =(int*)malloc((n+1) * sizeof(int));
        
        arr_init[0] = -1;
        arr_coppy[0] = -1;

        for(int i = Test_start; i<= 5; i+= Test_step){

            FillRandomArray(arr_init+1,n, arr_min, arr_max, false, UNSORTED);

            printf("Running QS : test %d , n %d \n", i, n);

                        Operation ass_QS_reg = prf.createOperation("Regular Ass QS", n);
            Operation cmp_QS_reg = prf.createOperation("Regular Comp QS", n);
            QS_Ass = &ass_QS_reg;
            QS_Comp = &cmp_QS_reg;

            prf.startTimer("RUNN_QS_REG", n);
            for(int z = 0; z<T_running_tine; z++){
                CopyArray(arr_coppy+1, arr_init+1, n);
                QuickSort(arr_coppy,1,n);
            }
            prf.stopTimer("RUNN_QS_REG",n);

            Operation ass_QS_hyb = prf.createOperation("Hybrid Ass QS", n);
            Operation cmp_QS_hyb = prf.createOperation("Hybrid Comp QS", n);
            QS_Th_Ass = &ass_QS_hyb;
            QS_Th_Comp = &cmp_QS_hyb;

            prf.startTimer("RUNN_QS_HYB", n);
            for(int z = 0; z<T_running_tine; z++){
                CopyArray(arr_coppy+1, arr_init+1, n);
                QuickSort_Hybrid_DIESEL_ELECTRIC(arr_coppy,1,n, Threshold_val_operations);
            }
            prf.stopTimer("RUNN_QS_HYB",n);
        }
        free(arr_init);
        free(arr_coppy);

        QS_Ass = nullptr;
        QS_Comp = nullptr;
        QS_Th_Ass = nullptr; 
        QS_Th_Comp = nullptr;
    }

    

    prf.createGroup("QS_Running_TIMES", "RUNN_QS_HYB", "RUNN_QS_REG" );
    prf.createGroup("QS_Comp_Hybird_vs_Reg", "QS_Compare_Compare");

}

// QuickSelect (Randomized-Select)

int Randomized_Partition(int *arr, int l, int r){

    int x = l + rand() % (r - l + 1);   
    swap_func(arr[x], arr[r]);          

    int i = l-1;
    for(int j = l; j < r; j++){
        if(arr[j] < arr[r]){
            i++;
            swap_func(arr[i], arr[j]);
        }
    }
    swap_func(arr[i+1], arr[r]);

    return i+1;
}

int QuickSelect(int *arr, int l, int r, int k){

    if(k < 1 || k > r - l + 1)               
        return -1;

    if(l == r)
        return arr[l];

    int pos = Randomized_Partition(arr, l, r);
    int left_size = pos - l + 1;              

    if(k == left_size)
        return arr[pos];

    if(k < left_size)
        return QuickSelect(arr, l, pos-1, k);
    else
        return QuickSelect(arr, pos+1, r, k - left_size);
}


void DEMO(){

    int arr[11]={-1,1,2,3,5,71,23,0,23,44,55};
    int n = 11;
    
    Operation ass_QS = prf.createOperation("DEMO", n);
    
    QS_Th_Ass = QS_Th_Comp = QS_Ass = QS_Comp = QS_Th_Ass = QS_Th_Comp = HP_Ass = HP_Comp = &ass_QS;

    int coppy_arr[11];
    CopyArray(coppy_arr, arr, n);

    printf("Array original : ");
    print_array(coppy_arr,0,n);
    QuickSort(coppy_arr,1,n-1);



    printf("Quick Sort applied on the array : ");
    print_array(coppy_arr,0,n);

    CopyArray(coppy_arr, arr, n);
    Heap_Sort(coppy_arr,n-1);
    printf("HeapSorted array : ");
    print_array(coppy_arr,0,n);

    CopyArray(coppy_arr, arr, n);

    printf("Apply Quick Sort hybrid : ");
    QuickSort_Hybrid_DIESEL_ELECTRIC(coppy_arr, 1, n-1, 10);
    print_array(coppy_arr,0,n);

    int k_values[2] = {1, 5};
    for(int t_ind = 0; t_ind < 2; t_ind++){
        CopyArray(coppy_arr, arr, n);
        int k = k_values[t_ind];
        int k_pos = QuickSelect(coppy_arr, 1, n-1, k);
        printf("QuickSelect k = %d : %d \n", k, k_pos );
    }
    
}




int main(){

    if(demo_state){
        DEMO(); 
    
    }
    else{
        QuickSort_Comparisons();
        prf.reset("Heap VS QuickSort ");
        Average_Cases_QS_vs_HS();
        prf.reset("QuickSort Hibridization");
        Threshold_Average();
        Threshold_Average_Runtime();
        Create_Run_Grups();
        prf.reset("QuickSort vs HibrdQuickSort");
        Operation_comp_QS_vs_HQS();
        Operation_comp_QS_vs_HQS_runtime();
        prf.showReport();

    }
      

}