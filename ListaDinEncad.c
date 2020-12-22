#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ListaDinEncad.h"  //inclui os Protótipos

ListaL* cria_ListaL()
{
    ListaL* li = (ListaL*) malloc(sizeof(ListaL));
    if(li != NULL)
        *li = NULL;
    return li;
}

void libera_ListaL(ListaL* li)
{
    if(li != NULL){
        ElemL* no;
        while((*li) != NULL){
            no = *li;
            *li = (*li)->prox;
            free(no);
        }
        free(li);
    }
}

/*
int consulta_ListaL_pos(ListaL* li, int pos, ElemL **el)
{
    if(li == NULL || pos <= 0)
        return ERRO;
    ElemL *no = *li;
    int i = 1;
    while(no != NULL && i < pos){
        no = no->prox;
        i++;
    }
    if(no == NULL)
        return ERRO;
    else{
        *el = no;
        return OK;
    }
}

int consulta_ListaL_dado(ListaL* li, Tipo_Dado dt, ElemL **el)
{
    if(li == NULL)
        return ERRO;
    ElemL *no = *li;
    while(no != NULL && no->dado != dt){
        no = no->prox;
    }
    if(no == NULL)
        return ERRO;
    else{
        *el = no;
        return OK;
    }
}


int insere_ListaL_final(ListaL* li, Tipo_Dado dt)
{
    if(li == NULL)
        return ERRO;
    ElemL *no;
    no = (ElemL*) malloc(sizeof(ElemL));
    if(no == NULL)
        return ERRO;
    no->dado = dt;
    no->prox = NULL;
    if((*li) == NULL){ //ListaL vazia: insere início
        *li = no;
    }else{
        ElemL *aux;
        aux = *li;
        while(aux->prox != NULL){
            aux = aux->prox;
        }
        aux->prox = no;
    }
    return OK;
}

int insere_ListaL_inicio(ListaL* li, Tipo_Dado dt)
{
    if(li == NULL)
        return ERRO;
    ElemL* no;
    no = (ElemL*) malloc(sizeof(ElemL));
    if(no == NULL)
        return ERRO;
    no->dado = dt;
    no->prox = (*li);
    *li = no;
    return OK;
}
*/

int insere_ListaL_ordenada(ElemL* li, Tipo_Dado* dt)
{
    ElemL *no = (ElemL*) malloc(sizeof(ElemL));
    if(no == NULL)
        return ERRO;

    //no->dado = dt;
    strcpy(no->dado, dt);

    if(li->prox == NULL){ //ListaL vazia: insere início
        no->prox = NULL;
        li->prox = no;
        return OK;
    }
    else{
        ElemL *ant = li, *atual = li->prox;
        while(atual != NULL && strcmp(atual->dado, dt) < 0){
            ant = atual;
            atual = atual->prox;
        }
        if(atual == li->prox) { //insere início
            ant->prox = no;
            no->prox = atual;
            atual->prox = NULL;

        }else{
            no->prox = atual;
            ant->prox = no;
        }
        return OK;
    }
}

int remove_ListaL_inicio(ListaL* li)
{
    if(li == NULL)
        return ERRO;
    if((*li) == NULL) //ListaL vazia
        return ERRO;

    ElemL *no = *li;
    *li = no->prox;
    free(no);
    return OK;
}

int remove_ListaL_final(ListaL* li)
{
    if(li == NULL)
        return ERRO;
    if((*li) == NULL) //ListaL vazia
        return ERRO;

    ElemL *ant, *no = *li;
    while(no->prox != NULL){
        ant = no;
        no = no->prox;
    }

    if(no == (*li)) //remover o primeiro?
        *li = no->prox;
    else
        ant->prox = no->prox;
    free(no);
    return OK;
}

int tamanho_ListaL(ListaL* li)
{
    if(li == NULL)
        return 0;
    int cont = 0;
    ElemL* no = *li;
    while(no != NULL){
        cont++;
        no = no->prox;
    }
    return cont;
}

int ListaL_cheia(ListaL* li)
{
    return 0;
}

int ListaL_vazia(ListaL* li)
{
    if(li == NULL)
        return 1;
    if(*li == NULL)
        return 1;
    return 0;
}


