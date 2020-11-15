
/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcionalidade1.h"
#include "fornecido.h"

char LIXO = '$';
int TAM_REG = 64;
int NULL_INT = -1;
int STR_END = '\0';

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

*/
