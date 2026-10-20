#ifndef _CONSTANT_H
#define _CONSTANT_H

//Demo or graphs
const bool Demo_state = false;

// Testing and mostly average cases
const int Step_start = 100;
const int Step_size = 50;
const int Step_final = 10000;

const int test = 0;
const int nr_test = 25;
const int test_step = 1;


//Array to be sorted
const int N_MAX = 10000;
int array_numb[N_MAX+1]; // we accesss N_MAX too
int array_numb_aux[N_MAX+1];
const int min_arr = 11;
const int max_arr = 32142;

// Avg cel mic pe interet
char const *Average_Assigments = "Average Assigments";
char const *Average_Comparisons = "Average Comparisons";
char const *Average_full = "Average Sink vs Swim";

// Worst case 
char const *Worst_assigments ="Worst Assigments";
char const *Worst_Comparisons = "Worst Comparisons";
char const *Worst_full = "Worst Sink vs Swim";

// Heap building - name constant 
char const *Swim_assign ="Assigments - Swim";
char const *Swim_comp ="Comparisons - Swim";
char const *Swim_tot = "Total - swim";

char const *Sink_assign ="Assigments - Sink";
char const *Sink_comp ="Comparisons - Sink";
char const *Sink_tot = "Total - sink";

// Heap Sort - name constants
char const *Heap_Sort_assign = "Assigments Heap Sort";
char const *Heap_Sort_comp = "Comparisons Heap Sort";


// Runtime constant 

// Iterative vs Recursive sorts
const char *SS_IT_assign = "Selection Solt Iterative assigments";
const char *SS_IT_comp = "Selection Solt Iterative compare";
const char *SS_IT_total = "Selection Solt Iterative total";

const char *SS_REC_assign = "Selection Solt Recursive assigments";
const char *SS_REC_comp = "Selection Solt Recursive compare";
const char *SS_REC_total = "Selection Solt Recursive total";

//Recursive function has now a for 
const char *SS_REC2_assign = "Selection Solt Recursive with for assigments";
const char *SS_REC2_comp = "Selection Solt Recursive with for compare";
const char *SS_REC2_total = "Selection Solt Recursive with for total";

// Timer names
const char *SS_IT_Timer ="Timer Selection Sort Iterative";
const char *SS_REC_Timer ="Timer Selection Sort Recursive";
const char *SS_REC2_Timer = "Timer Selection Sort Recursive with for";

// Iter vs Rec step

const int ss_serie = 100;
const int ss_serie_step = 100;
const int ss_max_serie = 10000;

const int ss_test = 0;
const int ss_test_attempt = 5;
const int ss_test_step = 1;

const int timer_t_start = 100;
const int timer_t_max = 10000;
const int timer_t_step = 500;

const int time_rep = 100;




#endif