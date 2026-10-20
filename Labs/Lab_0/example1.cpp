#include "Profiler.h"
#include <cmath>
Profiler prf("Lab0");

int array_numb[100]={0};

void generate_array(int *array, int start , int finish, int step, int *indx){
    *indx = 0;
    while(start<=finish){
        array[*indx] = start;
        start += step;
        (*indx)++;
    }
}

void make_graphs(int *array, int indx){
    for(int i=0; i< indx; i++)
    {
        float Oy = array[i];
        float Ox = array[i];
        prf.countOperation("O(n)", Ox, Oy);
        prf.countOperation("O(log(n))", Ox , 100*log(Oy) );
        prf.countOperation("O(10 ori n)", Ox , 10*Oy);
        prf.countOperation("O(n ori log(n))", Ox, Oy * log(Oy) );
        prf.countOperation("O(n la 2) ori 0.1)", Ox, 0.1*Oy*Oy);
        prf.countOperation("O(n la 3) ori 0.01", Ox, Oy*Oy*Oy * 0.01);
    }
}

int main(){

        int indx = 0;
        generate_array(array_numb,100,10000,100,&indx);
        make_graphs(array_numb, indx );
        prf.createGroup("grup O(n) vs O(nlogn)" ,"O(n ori log(n))", "O(n)");
        prf.createGroup("O(n)" , "O(n)");
        prf.createGroup("O(n log n)" , "O(n ori log(n))");
        prf.showReport();
        return 0;
}
