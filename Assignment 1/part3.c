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
int hash3(char* s);

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
      int j = 1;

      
      int inserted = 0;
      
    
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
            key = (key + j*hash3(stringpointer))%ARRAY_SIZE;
            collisions++;
            j++;
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
    int j = 1;

    if(strcmp(searchname,"quit") == 0){
      search = 0;
    }
    else{
        int searchkey = hash_function(searchname);

        while(searchloop == 0){
        if(strcmp(data[searchkey].held_name,searchname) == 0){
          printf("- %i\n",data[searchkey].frequency);
          
          searchloop = 1;
        }
        else{
          searchkey = (searchkey +j*hash3(searchname))%ARRAY_SIZE;

          checkcount++;
          if(checkcount>=59){
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
    
    s++;
}
return (hash % ARRAY_SIZE);
}

//a multiple of this will determine our step size after dealing with a collision
int hash3(char* s){
int hash = 0;
while(*s){
hash = 1+ (hash + *s) % (ARRAY_SIZE-1);
s++;
}
return hash;}
