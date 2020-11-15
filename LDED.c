#include <stdio.h>
#include <stdlib.h>

#include "LDED.h"

Lista* cria_lista()
{
    Lista* li = (Lista*) malloc(sizeof(Lista));
    if (li != NULL)
        *li = NULL;
    return li;
}

void libera_lista(Lista* li)
{
    if (li != NULL)
	{
        Elem* no;
        while ((*li) != NULL)
		{
            no = *li;
            *li = (*li)->prox;
            free(&(no->dado));
            free(no);
        }
        free(li);
    }
}

int insere_lista_final(Lista* li, indexaPessoa dt)
{
    Elem *no;

    if (li == NULL) return ERRO;
    no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)  return ERRO;

    no->dado = dt;
    no->prox = NULL;

	if ((*li) == NULL)
	{   //lista vazia: insere início
        no->ant = NULL;
        *li = no;
    }else
	{
        Elem *aux;
        aux = *li;
        while (aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
        no->ant = aux;
    }
    return OK;
}

int insere_lista_inicio(Lista* li, indexaPessoa *dt)
{
    if (li == NULL)
        return ERRO;
    Elem* no;
    no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return ERRO;

    no->dado = *dt;
    no->prox = (*li);
    no->ant = NULL;

	if (*li != NULL) //lista não vazia: apontar para o anterior!
        (*li)->ant = no;
    *li = no;
    return OK;
}

int insere_lista_ordenada(Lista* li, indexaPessoa dt)
{
    if (li == NULL)
        return ERRO;

    Elem *no = (Elem*) malloc(sizeof(Elem));
    if (no == NULL)
        return ERRO;

    no->dado = dt;
    if ((*li) == NULL)
	{  //lista vazia: insere início
        no->prox = NULL;
        no->ant = NULL;
        *li = no;
        return OK;
    }
    else{
        Elem *ante, *atual = *li;
        while (atual != NULL && atual->dado.idPessoa < dt.idPessoa)
		{
            ante = atual;
            atual = atual->prox;
        }
        if (atual == *li)
		{   //insere início
            no->ant = NULL;
            (*li)->ant = no;
            no->prox = (*li);
            *li = no;
        } else
		{
            no->prox = ante->prox;
            no->ant = ante;
            ante->prox = no;
            if (atual != NULL)
                atual->ant = no;
        }
        return OK;
    }
}

int tamanho_lista(Lista* li)
{
    if (li == NULL)
        return 0;
    int cont = 0;
    Elem* no = *li;
    while (no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int lista_vazia(Lista* li)
{
    if (li == NULL)
        return OK;
    if (*li == NULL)
        return OK;
    return FALSO;
}

int pegar_ultimo_rrn(Lista* li) {
    if (li == NULL) return ERRO;

    Elem* aux = *li;

    if((*li) == NULL) //lista vazia
    {
        return 0;
    }

    while (aux->prox != NULL){
        aux = aux->prox;
    }

    return aux->dado.rrn;
}

void imprime_lista_id(Lista* li)
{
    if(li == NULL) return;

    Elem *aux = *li;

    if(lista_vazia(li))
        return;

    while(aux != NULL)
    {
        printf("%d  %d\n", aux->dado.idPessoa, aux->dado.rrn);
        aux = aux->prox;
    }
}

indexaPessoa retorna_ultimo_index(Lista* li) {
    Elem* aux = *li;

    while (aux->prox != NULL){
        aux = aux->prox;
    }

    return aux->dado;
}
