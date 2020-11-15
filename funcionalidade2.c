/*#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "LDED.h"
#include "funcionalidade2.h"

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

        for(int i = 0; i < qtdPessoas; i++)
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
    printf("Dados da pessoa de código %d\n", pessoa.idadePessoa);

    if(strlen(pessoa.nomePessoa) > 0)
        printf("Nome: %s\n", pessoa.nomePessoa);
    else
        printf("Nome: -\n");

    if(pessoa.idadePessoa == -1)
        printf("Idade: - anos\n", pessoa.idadePessoa);
    else
        printf("Idade: %d anos\n", pessoa.idadePessoa);

    printf("Twitter: %s\n\n", pessoa.twitterPessoa);

}
*/
