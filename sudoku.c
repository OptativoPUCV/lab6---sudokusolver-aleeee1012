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

int is_valid(Node * n)
{
  int fila[9][9] = {0};
  int colu[9][9] = {0};
  int miniSudo[9][9] = {0};
  int num;

  for(int i = 0; i < 9; i++)
  {
    for(int k = 0; k < 9; k++)
    {
      num = n->sudo[i][k];
      int subSudo = (i/3)*3 + k/3;

      if(num != 0)
      {
        if(fila[i][num-1] != 0) return 0;
        fila[i][num-1] = 1;

        if(colu[k][num-1] != 0) return 0;
        colu[k][num-1] = 1;

        if(miniSudo[subSudo][num-1] != 0) return 0;
        miniSudo[subSudo][num-1] = 1;
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
          Node *adjN = copy(n);
          adjN->sudo[i][k] = num;
          if(is_valid(adjN))
          {
            pushBack(list, adjN); 
          }
        }          
        return list;
      }
    }
  }
  return list;
}

int is_final(Node* n)
{
  for(int i = 0; i < 9; i++)
  {
    for(int k = 0; k < 9; k++)
    {
      if(n->sudo[i][k] == 0) return 0;
    }
  }
  return 1;
}

Node* DFS(Node* initial, int* cont)
{
  Stack * S = createStack();
  push(S, initial);
  
    while (!is_empty(S)) {
        Node* current_node = top(S);
        pop(S);
        (*cont)++; // Incrementa el contador en cada iteración
        if (is_final(current_node)) {
            // Se encontró un estado final, se retorna el nodo
            return current_node;
        }
        Node** adjacent_nodes = get_adj_nodes(current_node);
        for (int i = 0; adjacent_nodes[i] != NULL; i++) {
            push(S, adjacent_nodes[i]);
        }
        free(current_node); // Libera la memoria usada por el nodo
    }
    // Si se recorrió todo el grafo sin encontrar una solución, retorna NULL
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