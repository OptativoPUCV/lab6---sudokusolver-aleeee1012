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

/*Node* DFS(Node* initial, int* cont)
{
  Stack *S = createStack();
  bool visited = false;
  push(S, initial);

  while(size(S) != 0)
  {
    Node *n = pop(S);

  }
  
  return NULL;
}*/

Node* DFS(Node* initial, int* cont)
{
  Stack *S = createStack();
  bool visited[9][9] = {false};
  push(S, initial);

  while(size(S) != 0)
  {
    Node *n = pop(S);
    
    // Si el nodo aún no ha sido visitado, lo marcamos como visitado y lo procesamos
    if (!visited[n->sudo[0][0]-1][n->sudo[0][1]-1]) {
      // Marcar el nodo actual como visitado
      visited[n->sudo[0][0]-1][n->sudo[0][1]-1] = true;
  
      // Incrementar el contador de nodos visitados
      (*cont)++;
  
      // Aquí se puede realizar cualquier acción necesaria con el nodo actual, como verificar si es una solución válida
      
      // Recorrer los vecinos del nodo actual y agregarlos al stack si aún no han sido visitados
      // En este caso, los vecinos serían los posibles movimientos válidos en el sudoku
      for (int i = 1; i <= 9; i++) {
        if (!visited[n->sudo[0][0]-1][i-1]) {
          Node* neighbor = (Node*) malloc(sizeof(Node));
          memcpy(neighbor, n, sizeof(Node));
          neighbor->sudo[0][1] = i;
          push(S, neighbor);
        }
        if (!visited[i-1][n->sudo[0][1]-1]) {
          Node* neighbor = (Node*) malloc(sizeof(Node));
          memcpy(neighbor, n, sizeof(Node));
          neighbor->sudo[0][0] = i;
          push(S, neighbor);
        }
      }
      
      // Devolver el puntero al último nodo visitado
      return n;
    }
  }
  
  // Si no se encontró ningún nodo sin visitar en el stack, se devuelve NULL
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