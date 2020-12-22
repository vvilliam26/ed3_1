#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "LDED.h"
#include "funcionalidade3.h"
#include "funcionalidade2.h"

int buscaRegistro(FILE* fileP, FILE* fileI, char *nomeDoCampo, int IdOpcional)
{
    //busca por id
    if(strcmp(nomeDoCampo, "idPessoa") == 0)
    {
        int id = IdOpcional;
        int rrn;
        int idTeste;
        //scanf("%d", &id);

        //acha o rrn pelo indexPessoa
        fseek(fileI, (id * 8)+4, SEEK_SET); //estah contando com o cabecalho
        fread(&rrn, sizeof(int), 1, fileI);

        //le os dados em pessoa pelo rrn
        char removido;
        fseek(fileP, ((rrn+1) * 64), SEEK_SET); //pula o cabecalho e os outros registros
        fread(&removido, sizeof(char), 1, fileP);
        fread(&idTeste, sizeof(int), 1, fileP);
        if(idTeste != id)
        {
            printf("Registro inexistente.\n");
            return 0;
        }
        fseek(fileP, -sizeof(int), SEEK_CUR);

        if(removido == '1')
        {
            dadoPessoa pessoa;

            //le id
            fread(&(pessoa.idPessoa), sizeof(int), 1, fileP);

            //le nome
            fread(pessoa.nomePessoa, sizeof(char), 40, fileP);

            //le idade
            fread(&(pessoa.idadePessoa), sizeof(int), 1, fileP);

            //le twitter
            fread(pessoa.twitterPessoa, sizeof(char), 15, fileP);

            printaFormatado(pessoa);
            return 1;
        } else {
            printf("Registro inexistente."); //registro removido
            return 0;
        }
    }

    else if(strcmp(nomeDoCampo, "nomePessoa") == 0)
    {
        char nomeValor[45];
        dadoPessoa pessoa;
        int qtdPessoas;
        scanf("%s", nomeValor);

        fseek(fileP, 1, SEEK_SET);
        fread(&qtdPessoas, sizeof(int), 1, fileP);
        pessoa.removido = '0';

        rewind(fileP);
        if(qtdPessoas > 0 )
        {

            while(fseek(fileP, (64+5), SEEK_CUR) == 0) //cabecalho + 5 bytes de removido e id
            {
                fread(pessoa.nomePessoa, sizeof(char), 40, fileP);

                if(strcmp(nomeValor, pessoa.nomePessoa) == 0)
                {
                    fseek(fileP, -(40+4+1), SEEK_CUR); //volta o ponteiro pro comeco do registro

                    //le removido
                    fread(&(pessoa.removido), sizeof(char), 1, fileP);
                    if(pessoa.removido == '0') //sai do looping pois n adianta ler mais nada
                        break;


                    //nome ja foi lido
                    fseek(fileP, 40, SEEK_CUR);


                    //le idade
                    fread(&(pessoa.idadePessoa), sizeof(int), 1, fileP);

                    //le twitter
                    fread(pessoa.twitterPessoa, sizeof(char), 15, fileP);

                    break;
                }
            }

            if(pessoa.removido == '0')
            {
                printf("Registro inexistente.\n ");
                return 0;
            }
            else
            {
              printaFormatado(pessoa);
              return 1;
            }
        } else
        {
            printf("Registro inexistente.\n");
            return 0;
        }

        return 1;
    }

    else if(strcmp(nomeDoCampo, "idadePessoa") == 0)
    {
        int idade;
        dadoPessoa pessoa;
        int qtd = 0; //quantidade de registros achados

        scanf("%d", &idade);

        fseek(fileP, 45, SEEK_SET); //posicionando para cair na parte de idades

        while(idade) //pula removida, id pessoa e nome
        {
            fseek(fileP, (64), SEEK_CUR);
            if(fread(&(pessoa.idadePessoa), sizeof(int), 1, fileP) == 0)
                break;

            if(pessoa.idadePessoa == idade)
            {
                fseek(fileP, -(4+40+4+1), SEEK_CUR);

                fread(&(pessoa.removido), sizeof(char), 1, fileP);
                if(pessoa.removido == '1')
                {
                    fread(&(pessoa.idPessoa), sizeof(int), 1, fileP);

                    fread(pessoa.nomePessoa, sizeof(char), 40, fileP);

                    //idade ja lida
                    fseek(fileP, sizeof(int), SEEK_CUR);

                    fread(pessoa.twitterPessoa, sizeof(char), 15, fileP);

                    printaFormatado(pessoa);

                    qtd++;

                    fseek(fileP, -(15+4), SEEK_CUR);
                }
                else
                    fseek(fileP, 4+40+4, SEEK_CUR);
            }
            else
            {
                fseek(fileP, -4, SEEK_CUR);
            }
        }

        if(qtd == 0)
        {
            printf("Registro inexistente.");
            return 0;
        }
    }

    return 0;
}

int checaIntegridadeP(FILE* fileP)
{
    if(fileP == NULL)   return 0;

    int qtdPessoas;
    char status;

    rewind(fileP);
    fread(&status, sizeof(char), 1, fileP);
    fread(&qtdPessoas, sizeof(int), 1, fileP);

    if(status == '0')
        return -1;
    else if(qtdPessoas <= 0)
        return 0;

    return 1;
}

int checaIntegridadeI(FILE *fileI)
{
    if(fileI == NULL)   return 0;

    char status;

    rewind(fileI);
    fread(&status, sizeof(char), 1, fileI);

    if(status == '0')
        return -1;

    return 1;
}
