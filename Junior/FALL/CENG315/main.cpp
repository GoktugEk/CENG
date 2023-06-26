//
// Created by Göktuğ Ekinci on 5.11.2021.
//

#include <iostream>

int sillySortHelper(int* arr, long &comparison, long & swap, int size, int f, int l)
{

    int num_of_calls=1;

    if (size == 0 && size == 1) return 1;
    else if(size == 2) {
        if (arr[l] >= arr[f]){
            int temp = arr[f];
            arr[f] = arr[l];
            arr[l] = temp;
            swap += 1;

        }
        comparison += 1;
    }
    else{
        int newsize = size*2 / 3;
        std::cout << newsize << "\n";
        if (arr[l] >= arr[f]){
            int temp = arr[f];
            arr[f] = arr[l];
            arr[l] = temp;
            swap += 1;
        }
        num_of_calls += sillySortHelper(arr, comparison, swap, newsize, f, f+newsize-1);
        num_of_calls += sillySortHelper(arr, comparison, swap, newsize, l-newsize+1, l);
        num_of_calls += sillySortHelper(arr, comparison, swap, newsize, f, f+newsize-1);

    }



    return num_of_calls;
}


int main(){
    long comparison;
    long swap;
    int *arr = new int[8];
    int dummy[8] = {3,2,4,6,5,9,1,10};
    for (int i = 0; i < 8; ++i) {
        arr[i]  = dummy[i];
    }
    sillySortHelper(arr , comparison, swap, 8, 0 ,7);


    return 0;
}