#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
#include "LDED.h"
#include "fornecido.h"
#include "funcionalidade1.h"
#include "funcionalidade2.h"
*/
#include "LDED.h"
#include "fornecido.h"

//funcionalidade1.h -----------------------------------------------
char LIXO = '$';
int TAM_REG = 64;
int NULL_INT = -1;
int STR_END = '\0';

int inicializaCabecalhoPessoa(FILE *fileP, cabecalhoArqPessoa *cp);
int atualizaCabecalhoPessoa(FILE *fileP, cabecalhoArqPessoa cp);
void insereBinario(FILE *fileP, cabecalhoArqPessoa *cp, Lista* li, dadoPessoa pessoa);
int montaIndex(char *nomeArqIndex, Lista* li);
//funcionalidade1.h -----------------------------------------------






//funcionalidade1.c -----------------------------------------------

int inicializaCabecalhoPessoa(FILE *fileP, cabecalhoArqPessoa *cp) {
    if(!fileP) {
        printf("Falha no processamento do arquivo.\n");
        return ERRO;
    }

    //inicializando valores da struct
    cp->status = '0';
    cp->qtdPessoas = 0;

    rewind(fileP);
    fwrite(&(cp->status), sizeof(char), 1, fileP);
    fwrite(&cp->qtdPessoas, sizeof(int), 1, fileP);
    for(int i = 0; i < (TAM_REG - 5); i++) //fill de lixo
    {
        fwrite(&LIXO, sizeof(char), 1, fileP);
    }

    return OK;
}

int atualizaCabecalhoPessoa(FILE *fileP, cabecalhoArqPessoa cp)
{
   if(fileP == NULL)
   {
       printf("Falha no processamento do arquivo.\n");
       return ERRO;
   }

   rewind(fileP);
   fwrite(&(cp.status), sizeof(char), 1, fileP);
   fwrite(&(cp.qtdPessoas), sizeof(int), 1, fileP);

   return OK;
}

void insereBinario(FILE *fileP, cabecalhoArqPessoa *cp, Lista* li, dadoPessoa pessoa) {
    if(fileP == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return;
    }

    //atualização cabecalho
    int i;

    //escrever informacao
    int novoRrn = cp->qtdPessoas; //rrn da pessoa atual
    fseek(fileP, ((novoRrn+1) * TAM_REG), SEEK_SET); //posiciona o ponteiro no registro a ser escrito pulando o cabecalho

    //escreve removido
    fwrite(&(pessoa.removido), sizeof(char), 1, fileP);

    //escreve id
    fwrite(&(pessoa.idPessoa), sizeof(int), 1, fileP);

    //escreve nome pessoa
    fwrite(pessoa.nomePessoa, sizeof(char), strlen(pessoa.nomePessoa), fileP);
    fwrite(&STR_END, sizeof(char), 1, fileP);//para casos de vetor cheio
    int lixoTam = 40 - strlen(pessoa.nomePessoa) - 1; //espaco que sobrou considerando o \0
    for(i = 0; i < lixoTam; i++)
    {
        fwrite(&LIXO, sizeof(char), 1, fileP); //fill de lixo
    }

    //escreve idade
    fwrite(&(pessoa.idadePessoa), sizeof(int), 1, fileP); //caso de idade = -1 feito fora da funcao

    //escreve twitter pessoa
    fwrite(pessoa.twitterPessoa, sizeof(char), strlen(pessoa.twitterPessoa), fileP);
    fwrite(&STR_END, sizeof(char), 1, fileP);
    lixoTam = 15 - strlen(pessoa.twitterPessoa) - 1;
    for(i = 0; i < lixoTam; i++)
    {
        fwrite(&LIXO, sizeof(char), 1, fileP); //fill de lixo
    }

    cp->qtdPessoas += 1;

    //inserindo na lista
    indexaPessoa ip;
    ip.idPessoa = pessoa.idPessoa;
    ip.rrn = novoRrn;

    insere_lista_ordenada(li, ip);
}

int montaIndex(char *nomeArqIndex, Lista* li)
{
    FILE *fileI;

    fileI = fopen(nomeArqIndex, "wb");
    char status = '0';

    if(fileI == NULL) {
        printf("Falha no processamento do arquivo.\n");
        return ERRO;
    }

    Elem *aux = *li; //ponteiro para percorrer a lista ordenada

    //construindo cabecalho
    rewind(fileI);
    fwrite(&(status), sizeof(char), 1, fileI);
    for(int i = 0; i < 7; i++)
    {
        fwrite(&LIXO, sizeof(char), 1, fileI);
    }


    //insere index
    while(aux != NULL)
    {
        fwrite(&(aux->dado.idPessoa), sizeof(int), 1, fileI);
        fwrite(&(aux->dado.rrn), sizeof(int), 1, fileI);
        aux = aux->prox;
    }

    status = '1';
    rewind(fileI);
    fwrite(&(status), sizeof(char), 1, fileI);

    fclose(fileI);

    return OK;
}

//funcionalidade1.c -----------------------------------------------






//funcionalidade2.h -----------------------------------------------

void printaFormatado(dadoPessoa pessoa);
void printaFormatado(dadoPessoa pessoa);

//funcionalidade2.h -----------------------------------------------






//funcionalidade2.c -----------------------------------------------

void leBinario(FILE* fileP)
{
    if(fileP == NULL)
    {
        printf("Falha no processamento do arquivo.");
    }

    rewind(fileP);
    char status;
    fread(&status, sizeof(char), 1, fileP);

    if(status == '0')
    {
        printf("Falha no processamento do arquivo.");
        return;
    }
    else
    {
        int TAM_REG = 64;
        int qtdPessoas;
        fread(&qtdPessoas, sizeof(int), 1, fileP);

        for(int i = 0; i <= qtdPessoas; i++)
        {
            char removido;
            dadoPessoa pessoa;

            fseek(fileP, (i+1)*TAM_REG, SEEK_SET);
            fread(&removido, sizeof(char), 1, fileP);

            if(removido == '1')
            {
                //lendo id
                fread(&(pessoa.idPessoa), sizeof(int), 1, fileP);

                //lendo nome
                fread(pessoa.nomePessoa, sizeof(char), 40, fileP);

                //lendo idade
                fread(&(pessoa.idadePessoa), sizeof(int), 1, fileP);

                //lendo twitter
                fread(pessoa.twitterPessoa, sizeof(char), 15, fileP);

                printaFormatado(pessoa);
            }
            else
            {
                printf("Registro inexistente.");
            }
        }
    }
}

void printaFormatado(dadoPessoa pessoa)
{
    printf("Dados da pessoa de código %d\n", pessoa.idPessoa);

    if(strlen(pessoa.nomePessoa) > 0)
        printf("Nome: %s\n", pessoa.nomePessoa);
    else
        printf("Nome: -\n");

    if(pessoa.idadePessoa == -1)
        printf("Idade: -\n", pessoa.idadePessoa);
    else
        printf("Idade: %d anos\n", pessoa.idadePessoa);

    printf("Twitter: %s\n\n", pessoa.twitterPessoa);

}


//funcionalidade2.c -----------------------------------------------





int main()
{
    int funcionalidade;


    scanf("%d", &funcionalidade);

    if(funcionalidade == 1) //leitura e gravacao de arquivos
    {
        char buffer[40];
        char nomeArquivoPessoa[40], nomeArquivoIndex[40];
        FILE *csv; //arquivo de leitura
        FILE *fileP; //arquivos de escrita: pessoa e index
        Lista *li = cria_lista(); //criando lista duplamente encadeada
        cabecalhoArqPessoa cp; //cabecalho do arquivo pessoa

        scanf("%s", buffer);
        csv = fopen(buffer, "r");
        if(csv == NULL)
        {
            printf("Falha no processamento do arquivo.\n");
            return ERRO;
        }

        scanf("%s", nomeArquivoPessoa);
        fileP = fopen(nomeArquivoPessoa, "wb");
        if(fileP == NULL)
        {
            printf("Falha no processamento do arquivo.\n");
            return ERRO;
        }

        scanf("%s", nomeArquivoIndex); //guardando nome


        inicializaCabecalhoPessoa(fileP, &cp); //monta cabecalho arquivo pessoa

        fseek(csv, 45, SEEK_SET); //pulando o cabecalho do arquivo csv
        int auxIdPessoa; //criei para auxiliar no while abaixo
        char auxNomePessoa[60]; //aux criado para validacao
        dadoPessoa pessoa;

        //leitura id
        while(fscanf(csv, "%d%*c", &auxIdPessoa) > 0)
        {
            //valores padrao
            pessoa.idPessoa = auxIdPessoa;
            pessoa.removido = '1';
            strcpy(auxNomePessoa, "init");

            //lendo nome pessoa
            if(fscanf(csv, "%[^,]s", auxNomePessoa) > 0)
            {
                trim(auxNomePessoa);
                strncpy(pessoa.nomePessoa, auxNomePessoa, 39);
            }
            else
            {
                auxNomePessoa[0] = '\0';
                trim(auxNomePessoa);
                strncpy(pessoa.nomePessoa, auxNomePessoa, 1);
            }

            //printf("\n%s\n", pessoa.nomePessoa);

            fscanf(csv, "%*c%d%*c", &(pessoa.idadePessoa));

            //leitura twitter pessoa
            fscanf(csv, "%s", pessoa.twitterPessoa);
            trim(pessoa.twitterPessoa);

            //printf("\n%d,%s,%d,%s \n", pessoa.idPessoa, pessoa.nomePessoa, pessoa.idadePessoa, pessoa.twitterPessoa);


            //inserindo no arquivo binario
            insereBinario(fileP, &cp, li, pessoa);
        }
        cp.status = '1';
        atualizaCabecalhoPessoa(fileP, cp);

        fclose(fileP);
        fclose(csv);

        montaIndex(nomeArquivoIndex, li);

        libera_lista(li);

        binarioNaTela1(nomeArquivoPessoa, nomeArquivoIndex);
    }

    else if(funcionalidade == 2)
    {
        char nomeArq[20];
        FILE* fileP;

        scanf("%s", nomeArq);

        fileP = fopen(nomeArq, "rb");
        if(fileP == NULL)
        {
            printf("Falha no processamento do arquivo.");
            return ERRO;
        }

        leBinario(fileP);
    }


    return 0;
}
