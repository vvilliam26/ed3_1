#define FALSO      0
#define VERDADEIRO 1

#define OK         1
#define ERRO       0

//Structs referentes ao trabalho 1
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

//Structs referentes ao trabalho 2
typedef struct {
    char status;
    int followers; //Seguidores
} cabecalhoSegue;

typedef struct registroSegue
{
    char removido;
    int idPessoaSegue;
    int idPessoaSeguida;
    char grauAmizade[3];
    char startDateSegue[10];
    char endDateSegue[10];
}registroSegue;
// -------------------//-----------------------

//Definição do tipo lista
struct elemento{
    struct elemento *ant;
    indexaPessoa dado;
    struct elemento *prox;
};

//Struct e funções com 2 e segue referentes ao trabalho 2
struct elemento2{
    struct elemento2 *ant;
    registroSegue dado;
    struct elemento *prox;
};

typedef struct elemento Elem;
typedef struct elemento* Lista;

typedef struct elemento2 Elem2;
typedef struct elemento2* Lista2;

Lista* cria_lista();

void libera_lista(Lista* li);

//Funcoes Trabalho 2

Lista2* criaLista2();
void liberaLista2(Lista2* li);
int insere_lista_segue(Lista2* li, registroSegue dt);
int insere_lista_ordenada_segue(Lista2* li, registroSegue dt);
// -------------------//-----------------------

int insere_lista_final(Lista* li, indexaPessoa dt);
int insere_lista_ordenada(Lista* li, indexaPessoa dt);
int insere_lista_inicio(Lista* li, indexaPessoa *dt);
int tamanho_lista(Lista* li);
int lista_vazia(Lista* li);
void imprime_lista_id(Lista* li);
int pegar_ultimo_rrn(Lista* li);
indexaPessoa retorna_ultimo_index(Lista* li);
