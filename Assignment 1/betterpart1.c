//Saad Amir 20334372

#include<stdio.h>
#include<stdlib.h>
#include<string.h>




const int ARRAY_SIZE = 59;
const int NAME_LENGTH = 18;

typedef struct {
  int frequency;
  char held_name[18];
  int used;

}element;

int hash_function(char* s);

int main(){

    element data[ARRAY_SIZE];
    char names[ARRAY_SIZE][NAME_LENGTH];
    char *stringpointer;
    char searchname[NAME_LENGTH];
    int collisions = 0;
    float load;
    int lines;
    char linecount;
    int terms = 0;
    int search = 1;
    int searchkey;
    

    //initialising all "useds" to zero to indicate nothing is occupied
    for(int i = 0;i<=ARRAY_SIZE-1;i++){
      data[i].frequency = 0;
      data[i].used = 0;
      
    }


    //counts number of lines/names in file as to know how many times to run future loops
    FILE *filepointer;
    filepointer = fopen("names.csv","r");

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

    //removes newline at the end of all names for added convenience when searching for strings
    for(int i = 0;i<=lines - 1;i++){
       fgets(names[i],NAME_LENGTH,filepointer);
       names[i][strcspn(names[i], "\n")] = 0;
    }
    fclose(filepointer);
    


    //hashing and inserting code
    for(int i =0 ;i<lines;i++){
      stringpointer = names[i];
      int key = hash_function(stringpointer);
      
      int inserted = 0;
      
    //the main idea is:
    //check if the element is in use
    //if it isnt, set it to be in use and then copy the current name down
    //increment the elements frequency
    //if it is in use increment collisions, but check the names agaisnt eachother
    //if theyre the same name increment frequency and stop trying to insert the current name
    //if theyre not the same name use whatever probing method to find a new element and repeat
      while(inserted == 0){
        if(data[key].used == 0){
        strcpy(data[key].held_name,stringpointer);
        data[key].used = 1;
        data[key].frequency++;
        terms++;
        inserted = 1;
        }
        else if(strcmp(data[key].held_name,stringpointer)==0){
          data[key].frequency++;
          collisions++;
          inserted = 1;
        }
        else{
            key++;
            key = key%ARRAY_SIZE;
            collisions++;
        }
      }
     

    }

    load = (float)terms/(float)ARRAY_SIZE;

  printf("File names.csv loaded\n");
  printf("%11s", "Capacity: ");
  printf("%i\n",ARRAY_SIZE);
  printf("%12s","Num Terms: ");
  printf("%i\n", terms);
  printf("%13s", "Collisions: ");
  printf("%i\n", collisions);
  printf("%7s","Load: ");
  printf("%.6f\n",load);
  printf("\nEnter term to get frequency or type \"quit\" to escape" );
  printf("\n");

  while(search == 1){
    printf(">>> ");
    fgets(searchname,sizeof(searchname),stdin);
    searchname[strcspn(searchname, "\n")] = 0;
    

    int checkcount = 0;
    int searchloop = 0;

    if(strcmp(searchname,"quit") == 0){
      search = 0;
    }
    else{
        searchkey = hash_function(searchname);

        while(searchloop == 0){
        if(strcmp(data[searchkey].held_name,searchname) == 0){
          printf("- %i\n",data[searchkey].frequency);
          
          searchloop = 1;
        }
        else{
          searchkey++;
          searchkey = searchkey%ARRAY_SIZE;
          checkcount++;
          if(checkcount>=ARRAY_SIZE){
            searchloop = 1;
            printf("%s is not in the table",searchname);
            printf("\n");
        }
     }
   }
  }
  }






return 0;
}



int hash_function(char* s){ 
    int hash = 0;
    while(*s){
    hash = hash + *s;
    //printf("+");
    s++;
}
return (hash % ARRAY_SIZE);
}

   