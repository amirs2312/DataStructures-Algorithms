#include <stdio.h> 
#include "t2.h"
//This file doesn't know whether its C or C++

int number_comparisons = 0;
int number_swaps = 0;

void swap2(int *array,int A,int B);
void partition(int arr[],int start,int end);



void selectionSort(int arr[], int size) 
{ 
  for(int i = 0;i<size-1;i++){
        int mindex = i;
        int min = arr[i];
        for(int j = i+1;j<size;j++){
            
            if(arr[j]<min){
                min = arr[j];
                mindex = j;
                
            }
            number_comparisons++;
        }
       if(mindex!=i) {
        swap2(arr,i,mindex);
        number_swaps++;}
    }
} 



void insertionSort(int arr[], int size) 
{ 
    for(int i = 1;i<size;i++){
        if(arr[i]<arr[i-1]){
            int inserted = 0;
            int j = i;
            number_comparisons++;

            while(inserted == 0){
                if(arr[j]<arr[j-1]&& j!= 0){
                    swap2(arr,j,j-1);
                    j--;
                    number_comparisons++;
                    number_swaps++;
                }
                else if(j == 0){
                    inserted = 1;
                    number_comparisons++;}

                else{
                    number_comparisons++;
                    inserted = 1;}

            }

        }
        number_comparisons++;
    }
  
  
}




void quickSort(int arr[], int size) 
{ 
 partition(arr,0,size-1);
}



void swap2(int *array, int A, int B){

    int temp;
    temp = array[A];
    array[A] = array[B];
    array[B] = temp;
}

void partition(int arr[],int start,int end){
    //pivot is taken as the rightmost entry in the subarray
    int i;
    int j;

    if(start<end){
        
        i = start;
        j = end;
        

        while(i<j){
            while(arr[i]<=arr[end] && i<end){
                i++;
                number_comparisons++;
                }
                number_comparisons++;
            while(arr[j]>arr[end]){
                j--;
                number_comparisons++;
            }
            number_comparisons++;
            if(i<j){
                swap2(arr,i,j);
                number_swaps++;
            }
        }

        swap2(arr,j,end);
        number_swaps++;
        partition(arr,start,j-1);
        partition(arr,j+1,end);
 }
}



     




