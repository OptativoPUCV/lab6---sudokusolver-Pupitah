#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
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

int is_valid(Node* n) {
    int i, j;
    for (i = 0; i < 9; i++) {
        int row[10] = {0};
        for (j = 0; j < 9; j++) {
            int num = n->sudo[i][j];
            if (num != 0) {
                if (row[num] == 1) {
                    return 0;
                }
                row[num] = 1;  
            }
        }
    }
    return 1;  
}



List* get_adj_nodes(Node* n) {
    List* list = createList();
    int found = 0;

    for (int i = 0; i < 9 && !found; i++) {
        for (int j = 0; j < 9 && !found; j++) {
            if (n->sudo[i][j] == 0) {
                int valid_count = 0;
                for (int k = 1; k <= 9 && valid_count < 3; k++) {
                    Node* new_node = copy(n);
                    new_node->sudo[i][j] = k;
                    if (is_valid(new_node)) {
                        pushBack(list, new_node);
                        valid_count++;
                    } else {
                        free(new_node);
                    }
                }

                found = 1;
            }
        }
    }

    return list;
}



int is_final(Node* n){
   for (int i = 0; i < 9; i++){

      for (int j = 0; j < 9; j++){
         if (n->sudo[i][j]==0){
            return 0;
         }
      }
   }
    return 1;
}

Node* DFS(Node* initial, int* cont) {
    Stack* s = createStack();
    push(s, initial);
    *cont = 0;

    while (!is_empty(s)) {
        Node* current = (Node*)top(s);
        pop(s);
        (*cont)++;

        if (is_final(current)) {
            free(s);
            return current;
        }

        List* adj_nodes = get_adj_nodes(current);
        Node* adj_node = first(adj_nodes);
        while (adj_node != NULL) {
            push(s, adj_node);
            adj_node = next(adj_nodes);
        }

        clean(adj_nodes); 
        free(current);
    }

    free(s);

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