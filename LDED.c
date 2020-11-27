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

Lista2* cria_lista2()
{
    Lista2* li = (Lista2*) malloc(sizeof(Lista2));
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
            free(no);
        }
        free(li);
    }
}

void libera_lista2(Lista2* li)
{
    if (li != NULL)
	{
        Elem2* no;
        while ((*li) != NULL)
		{
            no = *li;
            *li = (*li)->prox;
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

//---------- Funcionalidades Trabalho 2 ----------------

int insere_lista_segue(Lista2* li, registroSegue dt){
    Elem2 *no;

    if (li == NULL) return ERRO;
    no = (Elem2*) malloc(sizeof(Elem));
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

int insere_lista_ordenada_segue(Lista2* li, registroSegue dt)
{
    if (li == NULL)
        return ERRO;

    Elem2 *no = (Elem2*) malloc(sizeof(Elem2));
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
        Elem2 *ante, *atual = *li;
        while (atual != NULL)
		{
		    //1º Nivel de comparação, ainda sobre idPessoaSegue
		    if(atual->dado.idPessoaSegue > dt.idPessoaSegue){
                //Sai do Looping
                break;
            }

            // Se idPessoaSegue for igual, 2º nível de comparacao: idPessoaSeguida
            if(atual->dado.idPessoaSegue == dt.idPessoaSegue && atual->dado.idPessoaSeguida > dt.idPessoaSeguida){
                break;
            }

            // Se idPessoaSegue e idPessoaSeguida forem iguais(cada uma separadamente), 3º nivel de comparacao: startDateSegue
            if(atual->dado.idPessoaSegue== dt.idPessoaSegue && atual->dado.idPessoaSeguida == dt.idPessoaSeguida &&
                compareDates(atual->dado.startDateSegue, dt.startDateSegue) > 0){
                break;
            }

            // Caso todos os casos acima sejam iguais, o ultimo grau de comparacao: endDateSegue
            if(atual->dado.idPessoaSegue== dt.idPessoaSegue && atual->dado.idPessoaSeguida == dt.idPessoaSeguida
                && compareDates(atual->dado.startDateSegue, dt.startDateSegue) == 0 &&
                compareDates(atual->dado.endDateSegue, dt.endDateSegue) > 0){
                break;
            }

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

//A fim de facilitar a comparacao entre datas, a funcao analisa por dia, mes e ano se as datas sao correspondentes
int compareDates(char* date1, char* date2)
{
    char day1[2], day2[2],
    month1[2], month2[2],
    year1[4], year2[4];

    //Utilizando dos Looping e pulando os espacos enderecados com '/', coloca o valor das variaveis definidas acima em cada espaco, completando as datas e facilitando a comparacao
    //Para o Ano - 4 espacos
    for(int i = 0; i < 4; i++) {
        year1[i] = date1[i];
        year2[i] = date2[i];
    }
    //Para o mes - 2 espacos
    for(int i = 0; i < 2; i++) {
        month1[i] = date1[i+5];
        month2[i] = date2[i+5];
    }
    //Para o dia - 2 espacos
    for(int i = 0; i < 2; i++) {
        day1[i] = date1[i+8];
        day2[i] = date2[i+8];
    }

    //Comparacao sequencial de: ano, mes e dia
    if(strcmp(year1,year2) == 0){
        if(strcmp(month1,month2) == 0){
            if(strcmp(day1,day2) > 0){
                return 1;
            }
            else if(strcmp(day1,day2) < 0){
                return -1;
            }
            else if(strcmp(day1,day2) == 0){
                return 0;
            }
        }
        else if(strcmp(month1,month2) > 0){
            return 1;
        }
        else if(strcmp(month1,month2) < 0){
            return -1;
        }
    }
    else if(strcmp(year1,year2) > 0){
        return 1;
    }
    else if(strcmp(year1,year2) < 0){
        return -1;
    }

}
