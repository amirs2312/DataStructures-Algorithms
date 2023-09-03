//Saad Amir 20334372

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

const int ARRAY_SIZE = 99991;
const int FIELD_LENGTH = 30;


typedef struct {
    char p_ID[10];
    char d_ID[30];
    char surname[30];
    char forename[30];
    int  age;
    char person_type[30];
    char gender[30];
    char nationality[30];
    char religion[30];
    char occupation[30];
    struct person* next;

}person;

typedef struct {
  char held_name[18];
  int used;
  
  struct person* subject;

}element;




int hash_function(char* s);
void print_person(person* subject);
void remove_quotes(char text[30]);


int main(){
    

    element* data = (element*)malloc(sizeof(element)*ARRAY_SIZE);
    
    
    char *stringpointer;
    char searchname[FIELD_LENGTH];
    int collisions = 0;
    float load;
    int lines;
    char linecount;
    int terms = 0;
    int search = 1;
    int searchkey;
    char buffer[512];


    for(int i = 0;i<=ARRAY_SIZE-1;i++){
      data[i].used = 0;
      data[i].subject = NULL;

      
    }

    //counts number of lines/names in file as to know how many times to run future loops
    FILE *filepointer;
    filepointer = fopen("people.csv","r");
    

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
       fgets(buffer,512,filepointer);

       person* people = (person*)malloc(sizeof(person)*lines);

      

       int x = 0;
       char* sp2;
       do{
        
        fgets(buffer,512,filepointer);
         sp2 = strtok(buffer,",");
        strcpy(people[x].p_ID,sp2);

         sp2 = strtok(NULL,",");
        strcpy(people[x].d_ID,sp2);

        //the surname is read in differently to the rest as we dont want the quotation marks
        //to be considered during the hash function
        fgetc(NULL);
         sp2 = strtok(NULL,"\"");
        strcpy(people[x].surname,sp2);
        
        
         sp2 = strtok(NULL,",");
        strcpy(people[x].forename,sp2);

         sp2 = strtok(NULL,",");
        people[x].age = atoi(sp2);

         sp2 = strtok(NULL,",");
        strcpy(people[x].person_type,sp2);

         sp2 = strtok(NULL,",");
        strcpy(people[x].gender,sp2);

         sp2 = strtok(NULL,",");
        strcpy(people[x].nationality,sp2);

         sp2 = strtok(NULL,",");
        strcpy(people[x].religion,sp2);

         sp2 = strtok(NULL,",");
        strcpy(people[x].occupation,sp2);

        people[x].next = NULL;
        
        
        x++;

       } while(!feof(filepointer));

       fclose(filepointer);

   
       //where the hashing and inserting is done
       //we will use linear probing as i am lazy
       for(int i = 0;i<lines;i++){

        
       
       stringpointer = people[i].surname;
       int key = hash_function(stringpointer);
      
       int inserted = 0;
       person* personpointer;
       

       while(inserted == 0){
        if(data[key].used == 0){
          data[key].used = 1;
          terms++;
          data[key].subject = &people[i];
          strcpy(data[key].held_name,stringpointer);
          inserted = 1;
        
        }
        else if(strcmp(data[key].held_name,stringpointer) == 0){
          personpointer = data[key].subject;
          while(personpointer->next != NULL){
            personpointer = personpointer->next;
          }

          personpointer->next = &people[i];
          inserted = 1;
      
          terms++;
         
        }
        else{
          key++;
          key = key%ARRAY_SIZE;
          collisions++;
      
          } 
         }
        }


       
        //reminder to free up memory 

       


        load = (float)terms/(float)ARRAY_SIZE;

        printf("File people.csv loaded\n");
        printf("%11s", "Capacity: ");
        printf("%i\n",ARRAY_SIZE);
        printf("%12s","Num Terms: ");
        printf("%i\n", terms);
        printf("%13s", "Collisions: ");
        printf("%i\n", collisions);
        printf("%7s","Load: ");
        printf("%.6f\n",load);
        printf("\nEnter term to get frequency or type \"quit\" to escape" );
        

        while(search == 1){
        printf("\n>>> ");
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
           printf("\nPerson ID Deposition ID           Surname            Forename Age   Person Type    Gender    Nationality   Religion       Occupation");
           print_person(data[searchkey].subject);
           searchloop = 1;
            }


           else{
           searchkey++;
           searchkey = searchkey%ARRAY_SIZE;
           checkcount++;
           if(checkcount>=ARRAY_SIZE){
            searchloop = 1;
            printf("%s is not in the table",searchname);
            
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


//outputs all the attributes of a person and recursively calls itself to iterate
//through the linked list
void print_person(person* subject){

  

  remove_quotes(subject->forename);
  remove_quotes(subject->person_type);
  remove_quotes(subject->gender);
  remove_quotes(subject->nationality);
  remove_quotes(subject->religion);
  remove_quotes(subject->occupation);

  printf("\n%9s%14s%18s%20s%4i%14s%10s%13s%13s%17s", 
  subject->p_ID,
  subject->d_ID,
  subject->surname,
  subject->forename,
  subject->age,
  subject->person_type,
  subject->gender,
  subject->nationality,
  subject->religion,
  subject->occupation
  );

  if(subject->next != NULL)
  { print_person(subject->next);}
    
}


void remove_quotes(char text[20]){
  int i = 0;

  if(text[0] == '"'){

   if(strcmp(text,"\" \"")==0){
    text[0] = ' ';
    text[1] = '\0';

    }

  else {
    while(text[i+1]!='"'){
    text[i] = text[i+1];
    i++;
   }

   text[i] = '\0';}}
}


