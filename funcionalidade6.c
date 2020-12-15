#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcionalidade6.h"

static char LIXO = '$';
static int TAM_REG_SEGUE = 32;
static int STR_END = '\0';

int inicializaCabecalhoSegue(FILE *fileP, cabecalhoSegue *cp)
{
    if(!fileP) {
        printf("Falha no carregamento do arquivo.\n");
        return ERRO;
    }

    //inicializando valores da struct
    cp->status = '0';
    cp->followers = 0;

    rewind(fileP);
    fwrite(&(cp->status), sizeof(char), 1, fileP);
    fwrite(&cp->followers, sizeof(int), 1, fileP);
    for(int i = 0; i < (TAM_REG_SEGUE - 5); i++) //fill de lixo
    {
        fwrite(&LIXO, sizeof(char), 1, fileP);
    }

    return OK;
}

int atualizaCabecalhoSegue(FILE *fileP, cabecalhoSegue cp)
{
   if(fileP == NULL)
   {
       printf("Falha no carregamento do arquivo.\n");
       return ERRO;
   }

   rewind(fileP);
   fwrite(&(cp.status), sizeof(char), 1, fileP);
   fwrite(&(cp.followers), sizeof(int), 1, fileP);

   return OK;
}

void insereBinarioSegue(FILE *fileP, cabecalhoSegue *cp, Lista2* li, registroSegue segue) {
    if(fileP == NULL) {
        printf("Falha no carregamento do arquivo.\n");
        return;
    }

    //atualização cabecalho
    int i;
    int novoRrn = cp->followers;

    //escrever informacao
    fseek(fileP, ((novoRrn+1) * TAM_REG_SEGUE), SEEK_SET); //posiciona o ponteiro no registro a ser escrito pulando o cabecalho

    //escreve removido
    fwrite(&(segue.removido), sizeof(char), 1, fileP);

    //escreve idPessoaSegue
    fwrite(&(segue.idPessoaSegue), sizeof(int), 1, fileP);

    //escreve idPessoaSeguida
    fwrite(&(segue.idPessoaSeguida), sizeof(int), 1, fileP);

    //escreve grau de amizade
    fwrite(segue.grauAmizade, sizeof(char), strlen(segue.grauAmizade), fileP);
    fwrite(&STR_END, sizeof(char), 1, fileP);//para casos de vetor cheio
    int lixoTam = 3 - strlen(segue.grauAmizade) - 1; //espaco que sobrou considerando o \0
    for(i = 0; i < lixoTam; i++)
    {
        fwrite(&LIXO, sizeof(char), 1, fileP); //fill de lixo
    }

    //escreve data de inicio de seguidor
    fwrite(segue.startDateSegue, sizeof(char), strlen(segue.startDateSegue), fileP);
    fwrite(&STR_END, sizeof(char), 1, fileP);//para casos de vetor cheio
    lixoTam = 10 - strlen(segue.startDateSegue) - 1;
    for(i = 0; i < lixoTam; i++)
    {
        fwrite(&LIXO, sizeof(char), 1, fileP); //fill de lixo
    }

    //escreve data final de seguidor
    fwrite(segue.endDateSegue, sizeof(char), strlen(segue.endDateSegue), fileP);
    fwrite(&STR_END, sizeof(char), 1, fileP);
    lixoTam = 10 - strlen(segue.endDateSegue) - 1;

    for(i = 0; i < lixoTam; i++)
    {
        fwrite(&LIXO, sizeof(char), 1, fileP); //fill de lixo
    }


    cp->followers+= 1;
    insere_lista_segue(li, segue);
}
