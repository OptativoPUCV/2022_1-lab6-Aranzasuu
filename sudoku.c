#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n = (Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new = (Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){

    int i, j, k;
    //int ii, jj;

    // Revisar por columna
    for(i = 0; i < 9; i++){
        for(j = 0; j < 9; j++){
            if(n->sudo[i][j]){
                for(k = j + 1; k < 9; k++){
                if(n->sudo[i][j] == n->sudo[i][k]) return 0;
                }
            }
        }
    }

    // Revisar por fila
    for(j = 0; j < 9; j++){
        for(i = 0; i < 9; i++){
            if(n->sudo[i][j]){
                for(k = i + 1; k < 9; k++){
                    if(n->sudo[i][j] == n->sudo[k][j]) return 0;
                }
            }
        }
    }
    // Revisar cuadro
    
    for(i = 0; i < 9; i++){
        int validar[10] = {0};
        for(j = 0; j < 9; j++){
            int subI = 3*(i/3) + (j / 3);
            int subJ = 3*(i % 3) + (j % 3);
            if(validar[n->sudo[subI][subJ]] != 0) return 0;
            if(validar[n->sudo[subI][subJ]] == 0 && n->sudo[subI][subJ] != 0) validar[n->sudo[subI][subJ]] = 1;
        }
    }
    
    return 1;
}


List* get_adj_nodes(Node* n){
    
    List* list = createList();
    
    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(n->sudo[i][j] == 0){
                for(int k = 1; k < 10; k++){
                    Node *copia = copy(n);
                    copia->sudo[i][j] = k;
                    if(is_valid(copia)) pushBack(list,copia);
                }
                return list;
            }
        }
    }
    return list;
}


int is_final(Node* n){

    for(int i = 0; i < 9; i++){
        for(int j = 0; j < 9; j++){
            if(n->sudo[i][j] == 0) return 0;
        }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
    Stack *S = createStack();

    push(S, initial);

    while(is_empty(S) == 0){
        Node *aux = top(S);
        pop(S);
        if(is_final(aux)) return aux;
        List *lista = get_adj_nodes(aux);
        Node *primero = first(lista);
        while(primero != NULL){
            push(S,primero);
            primero = next(lista);
        }
        (*cont)++;
    }
    
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