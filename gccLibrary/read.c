#include <stdio.h>
#include <stdlib.h>
 
#define LEN 50
 
int main(){
      
    FILE *fp;
    /*  
    To read strings of maximum length of 50 characters,
    an array of characters of dimension 51 must be declared,
    because after the string the termination character '\0' must be stored
    */
    char row[LEN+1]; 
    char ch;
    int intValue;
    float floatValue;

    /* Reading the content of the file file.txt */
    /* Opening the file */
    printf("READING file.txt\n");
    fp = fopen("file.txt", "r");
  
    /* Control if the file has been opened without errors */
    if (fp == NULL){
        printf("Error: impossible to open the file file.txt\n");
        exit(1);
    }
  
    /* Reading the file row-by-row */
    printf("First reading method:\n");
    while ( fgets(row, LEN, fp) != NULL ) {
      printf("READ: %s\n", row);
    }
  
    
    rewind(fp);
  
    /* Reading the file word-by-word */
    printf("Second reading method:\n");
    while ( fscanf(fp, "%s", row) != EOF ) {
      printf("READ: %s\n", row);
    }
  
    rewind(fp);
  
    /* Reading the file character-by-character */
    printf("Third reading method:\n");
    while ( (ch=getc(fp)) != EOF ) {
      printf("%c ", ch);
    }
  
    fclose(fp); /* Closing the file */
  
    /* Reading the content of the file file2.txt */
    /* Note: the file contains in each row a string, an integer number and a real number */
  
    /* Opening the file */
    printf("\nREADING file2.txt\n");
    if ( (fp = fopen("file2.txt", "r")) == NULL){
        printf("Error: impossible to open the file file2.txt\n");
        exit(1);
    }
  
    /* First reading method */
    /* Recommended becase it is more compact */
    printf("First reading method:\n");
    while ( fscanf(fp, "%s %d %f", row, &intValue, &floatValue) != EOF ) {
      printf("READ: %s %d %f\n", row, intValue, floatValue);
    }
  
    rewind(fp);
  
    /* Second reading method */
    printf("Second reading method:\n"); 
    while ( fgets(row, LEN, fp) != NULL ) { /* E' consigliabile il metodo precedente */
      sscanf(row, "%s %d %f", row, &intValue, &floatValue);
      printf("READ: %s %d %f\n", row, intValue, floatValue);
    }
  
    /* Closing the file */
    fclose(fp);
  
    return 0;
}