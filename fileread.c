#include <complex.h>
#include <stddef.h>
#define ROWS 3
#define COLS 2
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int con=1;
size_t len_max[COLS+1]={0,0,0};
char table[ROWS][COLS+1][100];
char input[100];
void normalize_stringlength(char a[100],int j){
    int len = strlen(a);  // Get the current length of the string
    if (len < len_max[j]) {
        int spaces_to_add = len_max[j] - len;  // Calculate how many spaces to add
        for (int i = 0; i < spaces_to_add; i++) {
            a[len + i] = ' ';  // Add a space at the appropriate position
        }
        a[len_max[j]] = '\0';  // Ensure the string is null-terminated
    }

}
void max_length(int COL){
    len_max[COL]=0;
    for (int i=0; i<ROWS; i++) {
        if (strlen(table[i][COL])>len_max[COL]) {
            len_max[COL]=strlen(table[i][COL]);
        }
    
    }
}
void max_lengths(){
    for (int i=0; i<COLS+1; i++) {
        max_length(i);
    }
}
void trim_string(char* string){
    for (int i=0; string[i]!='\0'; i++) {
        if (string[i]==' ') {
            string[i]='\0';
            break;
        
        }
    
    }

}
void trim_table(){
    for (int i=0; i<ROWS; i++) {
        for (int j=0; j<COLS; j++) {
            trim_string(table[i][j]);
        }
    }
}
void printtable(){
    trim_table();
    max_lengths();
    for (int i=0; i<ROWS; i++) {
        for (int j=0; j<COLS+1; j++) {
            normalize_stringlength(table[i][j],j);
            printf("%s|",table[i][j]);
            
            
        }
        printf("\n");
    }
}
void percentage(){
    
    
    for (int i=0; i<ROWS; i++) {
        int count=0;
        double sum=0;
        for (int j=1; j<COLS; j++) {
            sum+=atof(table[i][j]);
            count++;
        }
    //table[i][COLS]=sum[i];
        sprintf(table[i][COLS], "%.2f%%",(sum/(40*count))*100);
        
        
    }
    
}

void change_values(int* rows,int* cols,char** new_vals,int n){
    for (int i=0; i<n; i++) {
        strcpy(table[rows[i]][cols[i]],new_vals[i]);
    
    }
    
}

void save_file(){
    FILE* saved_file;
    saved_file=fopen("savedfile.txt", "w");
    for (int i=0; i<ROWS; i++) {
        for (int j=0; j<COLS; j++) {
            if (j==0) {
                fprintf(saved_file, "%s",table[i][j]);
            }
            else if (j==COLS-1) {
                fprintf(saved_file, ",%s\n",table[i][j]);
        
            }
            else{
                fprintf(saved_file, ",%s",table[i][j]);
            }
        }
    }
    fclose(saved_file);
}
int main(){
FILE* ptr=fopen("test.txt","r");
char str[100];

//char lines[ROWS][100];
char* a;
size_t len;
for(int i=0;i<ROWS;i++){
    fgets(str,100,ptr);
    len=strlen(str);
    str[len-1]='\0';
    for (int j=0;j<COLS; j++) {
        if (j==0) {
            a=strtok(str,",");
        }
        else {
            a=strtok(NULL,",");
        }
        strcpy(table[i][j],a);
    }
}
percentage();
printtable();
while(con){
printf("What would you like to do? \n");
scanf("%s",input);
    
    if (strcmp(input, "exit")==0) {
        printf("you're exiting the programm, farewell!\n");
        con=0;
    }
    
    else if (strcmp(input, "savefile")==0) {
        printf("The file gets saved\n");
        trim_table();
        save_file();
        printf("the table was saved\n");
    
    }
    else if (strcmp(input, "changevals")==0) {
        int number_of_vals;
        printf("How many values would you like to change\n");
        scanf("%d",&number_of_vals);
        int* rows=malloc(number_of_vals*sizeof(int));
        int* cols=malloc(number_of_vals*sizeof(int));
        char** new_vals=malloc(number_of_vals*sizeof(char*));
        for(int i=0;i<number_of_vals;i++){
            new_vals[i]=malloc(100*sizeof(char));
        }
        printf("Enter the postion and the new values one by one in the format: ROW COL new_value\n");
        printf("further note that the index starts at 0\n");
        for (int i=0; i<number_of_vals; i++) {
            scanf("%d %d %s",&rows[i],&cols[i],new_vals[i]);
        
        }
        change_values(rows,cols,new_vals,number_of_vals);
        trim_table();
        percentage();
        printtable();
    }
    else{
        printf("unknown command please try again\n");
    }
    

    
}
//printf("%s \n",a);
fclose(ptr);
printf("\n%zu,%zu,%zu\n",len_max[0],len_max[1],len_max[2]);

}
/*
Name   | Punkte |Blatt 1| Vorgerechnet| Gesamt in %
------------------------------------------------
Gabriel| 10/20 |



*/