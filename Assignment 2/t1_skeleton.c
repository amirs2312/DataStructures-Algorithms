#include <stdio.h>
#include <stdlib.h>
#include<time.h>
#include "t1.h"

int check_dupe(int *array, int size);
void selection_sort(int *array,int size);
void swap1(int *array,int A,int B);
void inverse_selection_sort(int *array,int size);

int seeded = 0;


//Fills the array with ascending, consecutive numbers, starting from 0.
void fill_ascending(int *array, int size)
{
    if(seeded == 0){
        srand(time(0));
        seeded = 1;
    }
    for(int i =0;i<size;i++){
        array[i] = rand();
    }

    selection_sort(array,size);
    
}
//Fills the array with descending numbers, starting from size-1
void fill_descending(int *array, int size)
{
     if(seeded == 0){
        srand(time(0));
        seeded = 1;
    }
    for(int i =0;i<size;i++){
        array[i] = rand();
    }

    inverse_selection_sort(array,size);
    
}

//Fills the array with uniform numbers.
void fill_uniform(int *array, int size)
{
     if(seeded == 0){
        srand(time(0));
        seeded = 1;
    }
    int x = rand();
    for(int i = 0;i<size;i++){
        array[i] = x;
    }
    
}

//Fills the array with random numbers within 0 and size-1. Duplicates are allowed and at least 1 is mandatory
void fill_with_duplicates(int *array, int size)
{
     if(seeded == 0){
        srand(time(0));
        seeded = 1;
    }
    for(int i =0;i<size;i++){
        array[i] = rand();
    }

    int x = rand()%size;
    int inserted = 0;
    while(inserted == 0) {
        int k = rand()%size;
        if(k != x){
            array[x] = array[k];
            inserted = 1;
        }
    }  
    
}


//Fills the array with unique numbers between 0 and size-1 in a shuffled order. Duplicates are not allowed.
void fill_without_duplicates(int *array, int size)
{
     if(seeded == 0){
        srand(time(0));
        seeded = 1;
    }
    for(int i =0;i<size;i++){
        array[i] = rand();
    }

    while(check_dupe(array,size) == 1){
        check_dupe(array,size);
    }


    
}

void printArray(int* arr, int size){
  int i;
  for(i=0; i<size;i++){
    printf("%d ", arr[i]);
  }
  printf("\n");
}

//returns 1 if a duplicate was detected 0 if none
int check_dupe(int *array,int size){
    int x = 0;
    
    for(int i = 0;i<size-1;i++){
        for(int j = 1;j+i<size;j++){
        if(array[i] == array[i+j]){
            array[i+j] = rand();
            x = 1;
            break;
        }}
      
    }
    if(x == 1){return 1;}
    else{return 0;}
}

void selection_sort(int *array,int size){
    for(int i = 0;i<size-1;i++){
        int mindex = i;
        int min = array[i];
        for(int j = i+1;j<size;j++){
            
            if(array[j]<min){
                min = array[j];
                mindex = j;
            }
        }
       if(mindex!=i) {swap1(array,i,mindex);}
    }

}

void swap1(int *array, int A, int B){

    if(A == B){}
    else{
    int temp;
    temp = array[A];
    array[A] = array[B];
    array[B] = temp;}
}

void inverse_selection_sort(int *array,int size){
    for(int i = 0;i<size-1;i++){
        int maxdex = i;
        int max = array[i];
        for(int j = i+1;j<size;j++){
            
            if(array[j]>max){
                max = array[j];
                maxdex = j;
            }
        }
       if(maxdex!=i) {swap1(array,i,maxdex);}
    }

}

