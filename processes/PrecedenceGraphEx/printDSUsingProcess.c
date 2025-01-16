#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/*
  Illustrate the usage of Fork() inside for() loop
*/

// Function signatures
void handleArray(int n);
void handleMatrix(int row, int column);
void handleLinkedList(int n);


// Linked List
struct Node{
  int data;
  struct Node *next;
};


// Main function
int main(int argc, char **argv){

  int choice;
  int n;

  if(argc != 2){
    fprintf(stderr,"Insert an integer for dimensions => Array[n], Matrix[n,n] => linkedList length :)\n");
    exit(1);
  }

  n = atoi(argv[1]);

  fprintf(stdout,"\nWhich Data Structure would you like to use?\n1. Array[n]\n2. Matrix[n][n]\n3. LinkedList[n]\n\n");
  scanf("%d", &choice);

  switch (choice)
  {
  case 1:
    handleArray(n);
    break;
  case 2:
    handleMatrix(n,n);
    break;
  case 3:
    handleLinkedList(n);
    break;
  default:
    fprintf(stdout,"wrong input :/\n");
    break;
  }


  return 0;
}

// Function prototypes

void handleArray(int n){
  int *array = (int *) malloc (n * sizeof(int));
  pid_t pid;
  int status;

  if(array == NULL){
    fprintf(stderr,"Memory allocation 404\n");
    exit(1);
  }

  fprintf(stdout,"Insert Array\n");
  for(int i = 0; i < n ; i++){
    fprintf(stdout,"Array[%d]: ", i);
    scanf("%d", &array[i]);
  }

  fprintf(stdout,"\n\nOUTPUT\n\n");

  // Nested Fork
  for(int i = 0; i < n; i++){
    pid = fork();

    if(pid){
      pid = wait(&status);
    }
    else if(!pid){
      fprintf(stdout,"Pid %d => Array[%d] = %d \n", getpid(), i, array[i]);
      exit(1);
    }
    else{
      fprintf(stderr,"Forking 404\n");
      exit(404);
    }
  }
  free(array);
}

void handleMatrix(int row, int column){

  int **matrix = (int **) malloc (row * sizeof(int *));
  pid_t pid;
  int status;

  if(matrix == NULL){
    fprintf(stderr,"Memory allocation 404\n");
    exit(1);
  }

  fprintf(stdout,"Insert matrix\n");
  for(int i = 0; i < row ; i++){
    matrix[i] = (int *) malloc (column * sizeof(int));
    for(int j = 0; j < column; j++){
      fprintf(stdout,"matrix[%d][%d]: ", i, j);
      scanf("%d", &matrix[i][j]);
    }

  }

  fprintf(stdout,"\n\nOUTPUT\n\n");

  // Nested Fork
  for(int i = 0; i < row; i++){
   for(int j = 0; j < column ; j++){
    pid = fork();

    if(pid){
      pid = wait(&status);
    }
    else if(!pid){
      fprintf(stdout,"Pid %d => matrix[%d][%d] = %d \n", getpid(), i, j, matrix[i][j]);
      exit(2);
    }
    else{
      fprintf(stderr,"Forking 404\n");
      exit(404);
    }
   }
  }

  // Free Data Structure
  for(int i = 0;i < row; i++){
    free(matrix[i]);
  }
  free(matrix);
}


struct Node *createNode(int data){

  struct Node *newNode = (struct Node *) malloc (sizeof(struct Node));

  if(newNode == NULL){
    fprintf(stderr,"Memory Allocation 404\n");
    exit(404);
  }
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

void handleLinkedList(int n){

  struct Node *head = NULL, *current = NULL, *temp = NULL;
  pid_t pid;
  int status;


  fprintf(stdout,"Insert Linked List\n");
  for(int i = 0; i < n; i++){
    int value;
    fprintf(stdout,"Node[%d]: ", i);
    scanf("%d", &value);

    struct Node *newNode = createNode(value);
    if(newNode == NULL){
      fprintf(stderr,"Memory Allocation 404\n");
      exit(404);
    }
    if(head == NULL){
      head = newNode;
    }
    else{
      temp->next = newNode;
    }
    temp = newNode;
  }

  fprintf(stdout,"\n\nOUTPUT\n\n");

  current = head;

  for(int i = 0 ; i < n ; i++){
    pid = fork();

  // This section is critical cause it's better to avoid using exit in here
    if(pid){
      pid = wait(&status);
      break;
    }
    fprintf(stdout,"Pid %d => Node[%d] = %d \n", getpid(), i, current->data);
    current = current->next;

  }
  current = head;
  while (current!=NULL){
    struct Node *next = current->next;
    free(current);
    current = next;
  }
}