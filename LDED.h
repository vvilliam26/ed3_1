#define FALSO      0
#define VERDADEIRO 1

#define OK         1
#define ERRO       0

typedef struct {
    char status;
    int qtdPessoas;
} cabecalhoArqPessoa;

typedef struct dadoPessoa
{
    char removido;
    int idPessoa;
    char nomePessoa[40];
    int idadePessoa;
    char twitterPessoa[15];
} dadoPessoa;

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
