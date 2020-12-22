#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "ListaDinEncad.h"
#include "stack.h"


//nesse caso, usamos listas encadeadas simples

Graph* cria_grafo_adj(int V)
{
    Graph* G = (Graph *) malloc(sizeof(Graph));

    if(G != NULL)
    {
        G->V = V;
        G->A = 0;
        G->qtd = 0;
        G->itens = (ElemL**)
            malloc(V * sizeof(ElemL*));
        if(G->itens == NULL)
        {
            free(G);
            return NULL;
        }

        for(int i = 0; i<G->V; i++)
            G->itens[i] = NULL;
    }

    return G;
}

void libera_grafo_adj(Graph* G)
{
    if(G != NULL)
    {
        for(int i =0; i< G->V; i++)
        {
            if(G->itens[i] != NULL)
                free(G->itens[i]);
        }
        free(G->itens);
        free(G);
    }
}

int insere_vertice(Graph* G, char* nome)
{
    if(G == NULL || G->qtd == G->V)
        return 0;

    ElemL* novo = (ElemL*) malloc(sizeof(ElemL));
    if(novo == NULL)
        return 0;

    strcpy(novo->dado, nome);
    novo->prox = NULL;

    G->itens[G->qtd] = novo;

    G->qtd++;

    return 1;
}



int existeVertice(Graph* G, char* nome)
{
    for(int i=0; i < G->qtd; i++)
    {
        if(strcmp(G->itens[i]->dado, nome) == 0)
            return i;
    }

    return 0;
}

int numArestas(ElemL* vertex)
{
    int A = 0;
    ElemL* aux = vertex->prox;

    while(aux != NULL)
    {
        A++;
        aux = aux->prox;
    }

    return A;
}

