/* Example about the functions useful to write some data into a file */
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define LEN 50
#define N_STUD 2
 
/* Definition of a new type stud_t */
typedef struct stud{
    char name[LEN+1];
    unsigned int student_id;
    float average;
}stud_t;
 
 
int main() {
  
  FILE *fp;
  stud_t students[N_STUD];
  int i;
  char row[LEN+1];
 
  /* Filling of the first two records of the vector of type stud_t */
  strcpy(students[0].name, "Jules");
  students[0].student_id = 122333;
  students[0].average = 23.5;
 
  strcpy(students[1].name, "Laia");
  students[1].student_id = 122334;
  students[1].average = 29.5;
 
  /* Opening the file for write */
  fp = fopen("out.txt", "w");
  if (fp == NULL){
    printf("Error: impossible to open the file out.txt\n");
    exit(1);
  }
 
  /* Write data into the file: first method using the function fprintf */
  fprintf(fp, "First writing method\n"); /* Recommended */
  for(i=0; i<N_STUD; i++){
    fprintf(fp, "%s %d %f\n", students[i].name, students[i].student_id, students[i].average);
  }
 
  /* Write data into the file: second method using the function fputs */
  fputs("Second writing method\n", fp);
  for(i=0; i<N_STUD; i++){
    sprintf(row, "%s %d %f\n", students[i].name, students[i].student_id, students[i].average);
    fputs(row, fp);
  }
 
    fclose(fp); /* Closing the file */
 
  return 0;
}