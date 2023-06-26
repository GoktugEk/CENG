#include "the4.h"
#define MAX(a,b) (((a)>(b))?(a):(b))

int MAX3(int a, int b, int c){
    if (a > b && a > c) return a;
    else if (b > a && b > c) return b;
    else return c;
}

int recursive_sln(int i, int*& arr, int &number_of_calls){ //direct recursive
    number_of_calls+=1; //{ 7, 49, 73, 58, 30, 72, 44, 78, 23, 9 }

    if (i == 0) return arr[i];
    else if (i == 1) return MAX(arr[0],arr[1]);
    else if (i == 2) return MAX(arr[0],MAX(arr[1], arr[2]));
    else {
        int a = recursive_sln(i - 3, arr, number_of_calls) + arr[i];
        int b = recursive_sln(i - 1, arr, number_of_calls);
        return MAX(a, b);
    }
}



int memoization_sln(int i, int*& arr, int*& mem){ //memoization

    if (i == 0){
        mem[i] = arr[i];
        return mem[i];
    }
    else if (i == 1){
        mem[i] = MAX(arr[0],arr[1]);
        return mem[i];
    }
    else if (i == 2) {
        mem[i] = MAX(arr[0],MAX(arr[1], arr[2]));
        return mem[i];
    }
    else{
        int x,y;
        if(mem[i-3] == -1) x = memoization_sln(i-3,arr,mem) + arr[i];
        else x = mem[i-3] + arr[i];

        if(mem[i-1] == -1) y = memoization_sln(i-1,arr,mem);
        else y = mem[i-1];

        mem[i] = MAX(x,y);
        return mem[i];
    }

}


int dp_sln(int size, int*& arr, int*& mem){ //dynamic programming
    if (size == 1) {
        mem[0] = arr[0];
        return mem[0];
    }
    else if (size == 2){
        mem[0] = arr[0];
        mem[1] = MAX(arr[0],arr[1]);
        return mem[1];
    }
    else{
        mem[0] = arr[0];
        mem[1] = MAX(arr[0], arr[1]);
        mem[2] = MAX(arr[2], mem[1]);

        for (int i = 3; i < size; ++i) {
            mem[i] = MAX(mem[i - 3] + arr[i], mem[i - 1]);
        }

        return mem[size - 1];
    }

}

