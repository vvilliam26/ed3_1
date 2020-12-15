#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcionalidade7.h"



int leBinarioSegue(char* nomeArquivoSegue, char* nomeArquivoSegueOrdenado)
{
    //Abre arquivo inicial
    FILE* arquivoSegue = fopen(nomeArquivoSegue, "rb");

    if(arquivoSegue == NULL) {
        printf("Falha no carregamento do arquivo.\n");
        return 0;
    }

    rewind(arquivoSegue);
    char status;
    fread(&status, sizeof(char), 1, arquivoSegue);

    //Cria Lista
    Lista2* li = cria_lista2();

    //Checa se o arquivo foi aberto corretamente
    if(status == '0')
    {
        printf("Falha no carregamento do arquivo.");
        return 0;
    }
    else
    {
        int followers;
        fread(&followers, sizeof(int), sizeof(followers), arquivoSegue);

        for(int i = 0; i <= followers; i++)
        {

            registroSegue segue;

            fseek(arquivoSegue, (i+1)*TAM_REG_SEGUE, SEEK_SET); //Pula o cabeçalho

            //le removido
            fread(&(segue.removido), sizeof(segue.removido), 1, arquivoSegue);
            //le idPessoa que segue
            fread(&(segue.idPessoaSegue), sizeof(segue.idPessoaSegue), 1, arquivoSegue);
            //le idPessoa que eh seguida
            fread(&segue.idPessoaSeguida, sizeof(segue.idPessoaSeguida), 1, arquivoSegue);
            //le grau de amizade
            fread(segue.grauAmizade, sizeof(segue.grauAmizade), 1, arquivoSegue);
            //le data inicio que segue
            fread(segue.startDateSegue, sizeof(segue.startDateSegue), 1, arquivoSegue);
            //le data fim que segue
            fread(segue.endDateSegue, sizeof(segue.endDateSegue), 1, arquivoSegue);

            insere_lista_ordenada_segue(li, segue);
        }

        if(followers == 0)
            printf("Registro inexistente.\n");

    }

    //Fechando o arquivo segue

    fclose(arquivoSegue);

    //Abrindo o arquivo segue ordenado
    FILE* arquivoSegueOrdenado = fopen(nomeArquivoSegueOrdenado, "wb");

    //Referente ao status do cabecalho e sua manipulacao
    char iniciaCabecalho;
    //27 espacos de lixo
    char lixo[] ={'$','$','$','$','$','$','$','$','$',
    '$','$','$','$','$','$','$','$','$',
    '$','$','$','$','$','$','$','$','$'};




    //Trabalho com elemento para percorrer até o final do registro
    Elem2* aux;
    aux = *li;
    iniciaCabecalho = '1';
    while(aux != NULL){
        fwrite(&iniciaCabecalho, sizeof(char), 1, arquivoSegue);
        fwrite(&aux->dado.idPessoaSegue, sizeof(int), 1, arquivoSegue);
        fwrite(&aux->dado.idPessoaSeguida, sizeof(int), 1, arquivoSegue);
        fwrite(aux->dado.grauAmizade, sizeof(aux->dado.grauAmizade), 1, arquivoSegue);
        fwrite(aux->dado.startDateSegue, sizeof(aux->dado.startDateSegue), 1, arquivoSegue);
        fwrite(aux->dado.endDateSegue, sizeof(aux->dado.endDateSegue), 1, arquivoSegue);
        aux = (*aux).prox;
    }

    libera_lista2(li);
    fclose(arquivoSegueOrdenado);

    binarioNaTela2(nomeArquivoSegueOrdenado);
    return OK;
}
