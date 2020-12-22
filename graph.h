#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "ListaDinEncad.h"


struct graph {
    int V; //número de vértices
    int A; //número de arestas
    int qtd; //quantidade de espaços preenchidos no array
    ElemL* *itens;
};

typedef struct graph Graph;

//typedef struct node* link;

Graph* cria_grafo_adj(int V);
void libera_grafo_adj(Graph* G);
int insere_vertice(Graph* G, char* nome);
void ordena_grafo(Graph* G);
int existeVertice(Graph* G, char* nome);
void insertionSortNome(ElemL* V, int N);
int numArestas(ElemL* vertex);


#endif // GRAPH_H_INCLUDED
