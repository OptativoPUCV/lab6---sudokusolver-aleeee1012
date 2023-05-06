#include <stdio.h>
#include <stdlib.h>
#include "list.h"

typedef struct
{
   int sudo[9][9];
}Node;

Node* createNode()
{
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n)
{
  Node* new=(Node*) malloc(sizeof(Node));
  *new = *n;
  return new;
}

Node* read_file (char* file_name)
{
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  
  for(i=0;i<9;i++)
  {
    for(j=0;j<9;j++)
    {
      if(!fscanf (file, "%d", &n->sudo[i][j]))
      printf("failed to read data!");
    }
  }
  fclose (file);
  return n;
}

void print_node(Node* n)
{
  int i,j;
  for(i=0;i<9;i++)
  {
    for(j=0;j<9;j++)
      printf("%d ", n->sudo[i][j]);
    printf("\n");
  }
  printf("\n");
}

int is_valid(Node* n)
{
  int num1, num2, num3;
  
  for(int i = 0; i < 9; i++)
  {
    int fila[10] = {0,0,0,0,0,0,0,0,0,0};
    int colu[10] = {0,0,0,0,0,0,0,0,0,0};
    
    for(int k = 0; k < 9; k++)
    {
      num1 = n->sudo[i][k];
      if(num1 != 0)
      {
        if(fila[num1] == 0) fila[num1] = 1;
          
        else return 0;
      }
      
      num2 = n->sudo[k][i];
      if(num2 != 0)
      {
        if(colu[num2] == 0) colu[num2] = 1;
          
        else return 0;
      }
    }
    
      for(int a = 0; a < 9; a = (a + 3))
  {
    for(int t = 0; t < 9; t = (t + 3))
    {
      //int valo[10] = {0,0,0,0,0,0,0,0,0,0};

      for(int l = a; l < (a + 3); l++)
      {
        for(int j = t; j < (t + 3); j++)
        {
          num3 = n->sudo[l][j];
          if(num3 != 0)
          {
            if(fila[num3] == 1 && colu[num3])
            {
              return 0;
            }
            /*else
            {
              valo[num3] = 1;
            }*/
          }
        }
      }
    }
  }
  }



  return 1;
}

List* get_adj_nodes(Node* n)
{
  List *list = createList();

  for(int i = 0; i < 9; i++)
  {
    for(int k = 0; k < 9; k++)
    {
      if(n->sudo[i][k] == 0)
      {
        for(int num = 1; num <= 9; num++)
        {
          if(is_valid(n))
          {
            Node *adjN = copy(n);
            adjN->sudo[i][k] = num;
            pushBack(list, adjN);  
          }
        }
        return list;
      }
    }
  }
  return list;
}

int is_final(Node* n){
    return 0;
}

Node* DFS(Node* initial, int* cont){
  return NULL;
}

/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/