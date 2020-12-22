#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcionalidade12.h"
#include "stack.h"

int dfs(Graph* G, char *nomeFofoca)
{
    int path = 0, v, w; //variavel para armazenar o tamanho do caminho
    STACK *s = S_New(sizeof(char) * 41); //criando a fila
    ElemL* aux; //auxiliar pra percorrer as listas de adjacência
    char name[41];
    char marked[G->V]; //vetor para saber se um vértice ja foi visitado com 0 e 1
    char names[G->V][41];
    int j = 0;


    for(int i = 0; i< G->V; i++)
        marked[i] = '0';

    v = existeVertice(G, nomeFofoca);
    S_Push(G->itens[v]->dado, s);

    while(S_Size(s) > 0)
    {
        S_Pop(name, s);
        v = existeVertice(G, name); //funcao que checa se existe o vertice e retorna o id no array
        if(marked[v] == '0')
        {
            marked[v] = '1';
            aux = G->itens[v];
            path++; //contador para o caminho
            aux = aux->prox; //indo para o primeiro vizinho

            while(aux != NULL)
            {
                w = existeVertice(G, aux->dado);
                if(marked[w] == '0')
                {
                    strcpy(names[j], aux->dado); //ha a necessidade de se inserir ao contrario na pilha
                    j++;
                }
                aux = aux->prox;
            }

            for(int i = j; i>=0; i--)
            {
                S_Push(names[i], s); //inserindo ao contrario
            }
            j = 0;
        } else{
            return path;
        }
    }

    return 0;
}


