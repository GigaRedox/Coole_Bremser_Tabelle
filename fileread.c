#include <complex.h>
#include <stddef.h>
#include <sys/types.h>
int ROWS;//=3;
int COLS;//=2;
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int con=1;
size_t* len_max;//[COLS+1]={0,0,0};
//char table[ROWS][COLS+1][100];
char*** table;
char input[100];
double* percentages_col;//=calloc(ROWS, sizeof(char*));
void normalize_stringlength(char* a,int j){
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
        if (COL<COLS) {
                if (strlen(table[i][COL])>len_max[COL]) {
                len_max[COL]=strlen(table[i][COL]);
            }
        }
        else {
            char buffer[100];
            sprintf(buffer,"%.2f%%", percentages_col[i]);
            if (strlen(buffer)>len_max[COL]) {
                len_max[COL]=strlen(buffer);
        
            }
        }
    
    }
}
void max_lengths(){
    for (int i=0; i<COLS; i++) {
        max_length(i);
    }
}
void trim_string(char* string){
    int count=0;
    for (int i=0; string[i]!='\0'; i++) {
        if (string[i]==' ') {
            count++;
        
        }
    if (count==2) {
        string[i-1]='\0';
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
void printtable(){//!needs to be changed include headline with labels and convert percentages into strings and print them as (virtual column) table[i][COLS] !!! last cols is actually COLS-1
    trim_table();
    max_lengths();
    for (int i=0; i<ROWS; i++) {
        for (int j=0; j<COLS+1; j++) {// note only prints really exiting rows and cols
            if(j<COLS){
                normalize_stringlength(table[i][j],j);
                printf("%s|",table[i][j]);
            }
            else {
                char* buffer=calloc(1024, sizeof(char));
                sprintf(buffer,"%.2f%%", percentages_col[i]);
                normalize_stringlength(buffer,j);
                printf("%s|",buffer);
                free(buffer);
                
            }    
            
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
        percentages_col[i]=(sum/(40*count))*100;
        //sprintf(table[i][COLS], "%.2f%%",(sum/(40*count))*100);
        
        
    }
    
}

void change_values(int* rows,int* cols,char** new_vals,int n){
    for (int i=0; i<n; i++) {
        strcpy(table[rows[i]][cols[i]],new_vals[i]);
    
    }
    
}

void save_file(char* name){
    FILE* saved_file;
    saved_file=fopen(name, "w");
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
void number_of_rows(char* file_name){
    int num_of_rows=0;
    char buffer[1024];
    FILE* file=fopen(file_name, "r");
    while(fgets(buffer,1024*sizeof(char),file)!=NULL){
        num_of_rows++;
    }
    fclose(file);
    ROWS=num_of_rows;
}
void number_of_cols(char* file_name){
    int num_of_cols=0;               
    char buffer[1024];
    char* token;
    FILE* file=fopen(file_name, "r");
    fgets(buffer, sizeof(buffer), file);
    token=strtok(buffer, ",");
    while (token!=NULL) {
        num_of_cols++;
        token=strtok(NULL, ",");
    }
    COLS=num_of_cols;
    
}
void allocate_table(){
    table=calloc(ROWS,sizeof(char*));
    for (int i=0; i<ROWS; i++) {
        table[i]=calloc(COLS, sizeof(char*));
        for (int j=0;j<COLS; j++) {
            table[i][j]=calloc(1024, sizeof(char));
        }
    }
    
}
void add_table_row(){
    //ROWS++;
    char*** temp=realloc(table, ROWS*sizeof(char*));
    table=temp;
    table[ROWS-1]=calloc(COLS, sizeof(char*));
    for(int i=0;i<COLS;i++){
        table[ROWS-1][i]=calloc(1024, sizeof(char));
        table[ROWS-1][i]="0";
    }

}
void add_table_col(){
    //COLS++;
    char** temp;
    for (int i=0; i<ROWS; i++) {
        temp=realloc(table[i], COLS);
        table[i]=temp;
        table[i][COLS-1]=calloc(1024, sizeof(char));
        table[i][COLS-1]="0";
    }
}
void free_table(){
    for (int i=0; i<ROWS; i++) {
        for (int j=0; j<COLS; j++) {
            free(table[i][j]);
        }
        free(table[i]);
    }
    free(table);
}
void allocate_percentages_col(){
    percentages_col=calloc(COLS, sizeof(double));
    
}
void add_percentages_col_col(){
    //cant do COLS++; because COLS is a global variable that influences multiple pointers
    // before call need to increment COLS by one 
    double* temp=realloc(percentages_col, COLS);//effevtively COLS+1
    percentages_col[COLS]=0;
}
void free_percentages_cols(){
    free(percentages_col);
}
void allocate_len_max(){
    len_max=calloc(COLS, sizeof(size_t));
}
void add_len_max_col(){
    size_t* temp=realloc(len_max, COLS+1);//again effectively COLS+1
    len_max=temp;
    len_max[COLS]=0;
}
void free_len_max(){
    free(len_max);
}
void load(char* file_name){
FILE* ptr=fopen(file_name,"r");
    char str[1024];

    //char lines[ROWS][100];
    char* a;
    size_t len;
    for(int i=0;i<ROWS;i++){
        fgets(str,sizeof(str),ptr);
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
    fclose(ptr);
}
int main(){
    char file_name[100];
    printf("Which file should be loaded?\n");
    fgets(file_name,100,stdin);
    file_name[strcspn(file_name,"\n")]='\0';
    number_of_cols(file_name);
    number_of_rows(file_name);
    allocate_len_max();
    allocate_percentages_col();
    allocate_table();
    load(file_name);
    percentage();
    printtable();
    while(con){//while con==true <=> con==1
    printf("What would you like to do? \n");
    fgets(input,sizeof(input),stdin);
    //trim_string(input);
    input[strcspn(input, "\n")] = '\0';    
    if (strcmp(input, "exit")==0) {
        printf("you're exiting the programm, farewell!\n");
        con=0;
    }
    
    else if (strcmp(input, "savefile")==0) {
        printf("The file gets saved\n");
        trim_table();
        save_file(file_name);
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
            scanf("%d %d ",&rows[i],&cols[i]);
            fgets(new_vals[i], 100*sizeof(char), stdin);
            new_vals[i][strcspn(new_vals[i], "\n")]='\0';
        }
        change_values(rows,cols,new_vals,number_of_vals);
        free(rows);
        free(cols);
        for (int i=0; i<number_of_vals; i++) {
            free(new_vals[i]);
        }
        free(new_vals);
        trim_table();
        percentage();
        printtable();
    }
    else{
        printf("unknown command please try again\n");
        printf("%i %li\n",strcmp(input,"exit"),strlen(input));
    }
    

    
}
//printf("%s \n",a);
    //fclose(ptr);    
    printf("\n%zu,%zu,%zu\n",len_max[0],len_max[1],len_max[2]);

}
/*
Name   | Punkte |Blatt 1| Vorgerechnet| Gesamt in %
------------------------------------------------
Gabriel| 10/20 |



*/