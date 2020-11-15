// Arquivo LDED.h - Lista Dinamica Encadeada Dupla
// LDED para dados tipo Void * [Multiplos tipos de dados diferentes em um só TAD]

#define FALSO      0
#define VERDADEIRO 1

#define OK         1
#define ERRO       0

// 3 tipos de dados diferentes para uso nas listas


typedef struct indexaPessoa {
    int idPessoa;
    int rrn;
} indexaPessoa;

//Definição do tipo lista
struct elemento{
    struct elemento *ant;
    indexaPessoa dado;
    struct elemento *prox;
};

typedef struct elemento Elem;

typedef struct elemento* Lista;

Lista* cria_lista();
void libera_lista(Lista* li);
int insere_lista_final(Lista* li, indexaPessoa dt);
int insere_lista_ordenada(Lista* li, indexaPessoa dt);
int insere_lista_inicio(Lista* li, indexaPessoa *dt);
int tamanho_lista(Lista* li);
int lista_vazia(Lista* li);
void imprime_lista_id(Lista* li);
int pegar_ultimo_rrn(Lista* li);
indexaPessoa retorna_ultimo_index(Lista* li);
