#ifndef LISTADINENCAD_H_INCLUDED
#define LISTADINENCAD_H_INCLUDED


//Arquivo ListaLDinEncad.h

#define FALSO      0
#define VERDADEIRO 1

#define OK         1
#define ERRO       0

typedef char Tipo_Dado;

//Definição do tipo ListaL
struct elementoLDES{
    Tipo_Dado dado[35];
    struct elementoLDES *prox;
};

typedef struct elementoLDES ElemL;

typedef struct elementoLDES* ListaL;

ListaL* cria_ListaL();
void libera_ListaL(ListaL* li);
int insere_ListaL_final(ListaL* li, Tipo_Dado dt);
int insere_ListaL_inicio(ListaL* li, Tipo_Dado dt);
int insere_ListaL_ordenada(ElemL* li, Tipo_Dado* dt);
int remove_ListaL(ListaL* li, Tipo_Dado dt);
int remove_ListaL_inicio(ListaL* li);
int remove_ListaL_final(ListaL* li);
int tamanho_ListaL(ListaL* li);
int ListaL_vazia(ListaL* li);
int ListaL_cheia(ListaL* li);
void imprime_ListaL(ListaL* li);
int consulta_ListaL_dado(ListaL* li, Tipo_Dado dt, ElemL **el);
int consulta_ListaL_pos(ListaL* li, int pos, ElemL **el);
int insere_aresta(ListaL* li, char* pSeguida);

#endif // LISTADINENCAD_H_INCLUDED
