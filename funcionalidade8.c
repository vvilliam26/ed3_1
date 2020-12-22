#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "funcionalidade8.h"

int buscaRegistroBinario(FILE* fileSO, int idPessoa, int limInf, int limSup, int *found)
{
    int meio;
    int id;
    if(limInf > limSup) return 0;
    else
    {
        meio = (limInf + limSup);
        if((meio / 32) % 2 != 0)
            meio += 32;
        meio = meio/2;
        fseek(fileSO, meio+1, SEEK_SET);
        fread(&id, sizeof(int), 1, fileSO);
        if(idPessoa < id)
            return buscaRegistroBinario(fileSO,idPessoa, limInf, meio - 32, found);
        else if(idPessoa > id)
            return buscaRegistroBinario(fileSO, idPessoa, meio + 32, limSup, found);
        else if(idPessoa == id)
        {
            char removido;
            fseek(fileSO, -(sizeof(int)+sizeof(char)), SEEK_CUR);
            fread(&removido, sizeof(char), 1, fileSO);

            if(removido == '0')
            {
                printf("Registro inexistente.");
                return 0;
            }
            else
            {
                /*
                registroSegue registro;
                registro.removido = '1';
                fread(&(registro.idPessoaSegue), sizeof(int), 1, fileSO);
                fread(&(registro.idPessoaSeguida), sizeof(int), 1, fileSO);
                fread(&(registro.grauAmizade), sizeof(char), 3, fileSO);
                fread(registro.startDateSegue, sizeof(char), 10, fileSO);
                fread(registro.endDateSegue, sizeof(char), 10, fileSO);

                printaSegue(registro);
                */
                *found = meio;
                return 1;
            }
        }
    }
    return 0;
}

void printaSegue(registroSegue registro)
{
    char auxDate[11]; //caso nao tenha \0

    printf("Segue a pessoa de código: %d\n", registro.idPessoaSeguida);
    printf("Justificativa para seguir: ");
    if(registro.grauAmizade[0] == '0')
        printf("segue porque é uma celebridade\n");
    else if(registro.grauAmizade[0] == '1')
        printf("segue porque é amiga de minha amiga\n");
    else if(registro.grauAmizade[0] == '2')
    {
        printf("segue porque é minha amiga\n");
    }

        strncpy(auxDate, registro.startDateSegue, 10);
        strcat(auxDate, "\0");

    printf("Começou a seguir em: %s\n", auxDate);

        strncpy(auxDate, registro.endDateSegue, 10);
        strcat(auxDate, "\0");

    printf("Parou de seguir em: %s\n", auxDate);
    printf("\n");
}

void retornaRegistros(FILE* fileSO, int idPessoa) //funcao para achar outros registro que seguem uma id, se houver
{
    int tam;
    int found = 0;

    fseek(fileSO, 1, SEEK_SET);
    fread(&tam, sizeof(int), 1, fileSO);

    buscaRegistroBinario(fileSO, idPessoa, 32, ((tam-1) * 32), &found);

    int id = 0; //para teste de igualdade
    //int cont = 1;//contador para o seek
    //fseek(fileSO, found, SEEK_SET);

    //posicionando
    do
    {
        fread(&id, sizeof(int), 1, fileSO);
        if(id != idPessoa)
            break;

        fseek(fileSO, -36, SEEK_CUR);
    } while(id == idPessoa);


    registroSegue registro;
    fseek(fileSO, 27, SEEK_CUR);
    //printando
    do
    {
        fread(&(registro.removido), sizeof(char), 1, fileSO);
        fread(&(registro.idPessoaSegue), sizeof(int), 1, fileSO);
        if(registro.idPessoaSegue != idPessoa)
            break;
        fread(&(registro.idPessoaSeguida), sizeof(int), 1, fileSO);
        fread(registro.grauAmizade, sizeof(char), 3, fileSO);
        fread(registro.startDateSegue, sizeof(char), 10, fileSO);
        fread(registro.endDateSegue, sizeof(char), 10, fileSO);

        if(registro.removido == '1')
            printaSegue(registro);
    } while(idPessoa == registro.idPessoaSegue);

}
