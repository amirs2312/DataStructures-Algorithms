//Saad Amir 20334372
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct{
    char title[256];
    char platform[60];
    int  score;
    int release_year;
}review;

//selection sort used as if we only want to see top 15 only need to sort top 15
void selectionSort(review* arr[], int size); 
void swap_pos(review* arr[], int A, int B);
void print_list(review* arr[],int size);
void print_list_top(review* arr[], int size,int howmany);



int main(){

    int lines;
    int linecount;
    

    char buffer[512];

    FILE *filepointer;
    filepointer = fopen("t4_ign.csv","r");

    
    //count the amount of lines to sew how many review spaces need to be initialised
    if(filepointer==NULL){
      printf("error opening file.\n");
      return 1;
    }

       lines = 1;
       do{
        linecount = fgetc(filepointer);
        if(linecount == '\n'){lines ++;}

       }while(linecount != EOF);


       rewind(filepointer);

       review* data = (review*)malloc(sizeof(review)*lines);


       //skip the first line of the csv file 
       fgets(buffer,512,filepointer);

       int x;
       char string[512];
       char string2[128];
       int commacount;

       do{

        fgets(buffer,512,filepointer);


        //if a quotation mark is seen continue reasing the title unitl quotation marks followed by a comma is seen
        if(buffer[0] == '\"'){
            int done = 0;
            int i = 0;
            commacount = 0;
          while(done == 0){
            
            string[i] = buffer[i];
            if(buffer[i] == '\"' && buffer[i+1] == ','){
                done = 1;
            }
            if(buffer[i] == ','){
                commacount++;
            }
            i++;

          }
          strcpy(string2,strtok(buffer,","));

          for(int j = 0;j<commacount;j++){
            strcpy(string2,strtok(NULL,","));  
          }
            } 
        else{
        strcpy(string,strtok(buffer,","));
        strcpy(data[x].title,string);
        }

        strcpy(string,strtok(NULL,","));
        strcpy(data[x].platform,string);

        strcpy(string,strtok(NULL,","));
        data[x].score = atoi(string);

        strcpy(string,strtok(NULL,","));
        data[x].release_year = atoi(string);
        //incase we want to sort by year as well better to convert the year to an int

        x++;

       }while(!feof(filepointer));


    fclose(filepointer);

    //We'll sort an array of review pointers as opposed to the reviews themselves
    review* list[lines];

    for(int i = 0;i<lines;i++){
        list[i] = &data[i];
    }


    //could be modified to only sort the top X amount to save time if wanted
    selectionSort(list,lines);


    print_list_top(list,lines,10);


    return 0;








}










//swapping two pointerse is less time consuming then copying a structure 3 times
void swap_pos(review* arr[], int A, int B){

    review* temp;
    temp =  arr[A];
    arr[A] = arr[B];
    arr[B] = temp;   
}




void print_list(review* arr[], int size){

    for(int i = 0;i<size;i++){
        printf("\n%s",arr[i]->title);
        printf("\n%s",arr[i]->platform);
        printf("\n%i",arr[i]->score);
        printf("\n%i",arr[i]->release_year);
        printf("\n");
    }

}


//alterted selection sort
void selectionSort(review* arr[], int size) 
{ 
  for(int i = 0;i<size-1;i++){
        int mindex = i;
        int min = arr[i]->score;
        for(int j = i+1;j<=size-1;j++){
            
            if(arr[j]->score<min){
                min = arr[j]->score;
                mindex = j;
                
            }
            
        }
       if(mindex!=i) {
        swap_pos(arr,i,mindex);
        }
    }
} 


void print_list_top(review* arr[], int size,int howmany){

    for(int i = size - 1;i>=size - howmany;i--){
        printf("\n Title: %s",arr[i]->title);
        printf("\n Platform: %s",arr[i]->platform);
        printf("\n Score: %i",arr[i]->score);
        printf("\n Release Year: %i",arr[i]->release_year);
        printf("\n");
    }

}

