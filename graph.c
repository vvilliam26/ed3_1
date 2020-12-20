#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"

struct graph {
    int V;
    int A;
    link *node;
};

struct node {
    vertex w;
    link prox;
};


link newNode(vertex w, link prox)
{
    link no = malloc(sizeof(struct node));
    strcpy(no->w, w);
    no->prox = prox;

    return no;
}

Graph cria_grafo_adj(int V)
{
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->A = 0;
    G->node = malloc(V * sizeof(link));
    for(vertex v = 0; v < V; v++)
        G->node[v] = NULL;

    return G;
}

void insere_aresta_grafo(Graph G, vertex v, vertex w)
{
    for(link a = G->node[v]; a != NULL; a = a->prox)
        if(strcmp(a->w, w) == 0)   return;
    G->node[v] = newNode(w, G->node[v]);
    G->A++;
}
