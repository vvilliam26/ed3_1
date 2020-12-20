#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fornecido.h"
#include "LDED.h"
#include "graph.h"

#include "funcionalidade1.c"
#include "funcionalidade2.c"
#include "funcionalidade3.c"
#include "funcionalidade6.c"
#include "funcionalidade7.c"
#include "funcionalidade8.c"

// Vinicius William da Silva - 11233842
// Gabriel Fernandes Araujo - 11200334


int main()
{
    int funcionalidade;
    char nomeArqCsv[40];
    char nomeArquivoSegueOrdenado[300];
    char nomeArquivoSegue[40];

    scanf("%d", &funcionalidade);

    if(funcionalidade == 1) //leitura e gravacao de arquivos
    {
        char nomeArquivoPessoa[40], nomeArquivoIndex[40];
        FILE *csv; //arquivo de leitura
        FILE *fileP; //arquivos de escrita: pessoa e index
        Lista *li = cria_lista(); //criando lista duplamente encadeada
        cabecalhoArqPessoa cp; //cabecalho do arquivo pessoa

        scanf("%s", nomeArqCsv);
        csv = fopen(nomeArqCsv, "r");
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
        char auxNomePessoa[100]; //aux criado para validacao
        dadoPessoa pessoa;

        //leitura id
        while(fscanf(csv, "%d%*c", &auxIdPessoa) > 0)
        {
            //valores padrao
            pessoa.idPessoa = auxIdPessoa;
            pessoa.removido = '1';
            strcpy(auxNomePessoa, "init"); //retirando o lixo da variavel

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

    else if(funcionalidade == 3)
    {
        char nomeFileP[20], nomeFileI[20];
        char nomeCampo[20];
        FILE* fileP, *fileI;

        scanf("%s", nomeFileP);
        scanf("%s", nomeFileI);

        fileP = fopen(nomeFileP, "rb");

        if(fileP == NULL)
        {
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }

        fileI = fopen(nomeFileI, "rb");
        if(fileI == NULL)
        {
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }

        scanf("%s", nomeCampo);


        //checa integridade do arquivo
        if(checaIntegridadeP(fileP) == -1 || checaIntegridadeI(fileI) == -1)
        {
           printf("Falha no processamento do arquivo.\n");
           return 0;
        }
        else if(checaIntegridadeP(fileP) == 0)
        {
            printf("Registro inexistente.\n");
            return 0;
        }

        buscaRegistro(fileP, fileI, nomeCampo, 0);

        fclose(fileI);
        fclose(fileP);
    }

    else if(funcionalidade == 4)
    {

    }
    else if(funcionalidade == 6)
    {
        FILE *csv; //arquivo de leitura
        FILE *fileP; //arquivos de escrita: segue
        Lista2 *li = cria_lista2(); //criando lista duplamente encadeada
        cabecalhoSegue cp; //cabecalho do arquivo segue

        scanf("%s", nomeArqCsv);
        csv = fopen(nomeArqCsv, "r");
        if(csv == NULL)
        {
            printf("Falha no carregamento do arquivo.\n");
            return ERRO;
        }

        scanf("%s", nomeArquivoSegue);
        fileP = fopen(nomeArquivoSegue, "wb");
        if(fileP == NULL)
        {
            printf("Falha no carregamento do arquivo.\n");
            return ERRO;
        }

        inicializaCabecalhoSegue(fileP, &cp); //monta cabecalho arquivo segue

        fseek(csv, 83, SEEK_SET); //pulando o cabecalho do arquivo csv

        registroSegue segue;
        int auxFunc = 1118;
        //leitura id
        for(int j = 0; j < auxFunc; j++)
        {
            //valores padrao
            segue.removido = '1';
            fscanf(csv, "%d%*c", &(segue.idPessoaSegue));
            fscanf(csv, "%d%*c", &(segue.idPessoaSeguida));
            fscanf(csv, "%[^,]", segue.grauAmizade);
            fscanf(csv, "%*c%[^,]", segue.startDateSegue);
            fscanf(csv, "%*c%[^,\n]", segue.endDateSegue);


            //inserindo no arquivo binario
            insereBinarioSegue(fileP, &cp, li, segue);
        }
        cp.status = '1';
        atualizaCabecalhoSegue(fileP, cp);
        //Fechando os dois arquivos
        fclose(fileP);
        fclose(csv);

        libera_lista2(li);

        binarioNaTela2(nomeArquivoSegue);
    }

    else if(funcionalidade == 7) {
        scanf("%s %s", nomeArquivoSegue, nomeArquivoSegueOrdenado);
        leBinarioSegue(nomeArquivoSegue,nomeArquivoSegueOrdenado);
    }

    else if(funcionalidade == 8)
    {
        FILE *fileP, *fileI, *fileSO;
        char nomeCampo[20], nomeArqPessoa[20],
        nomeArqIndex[20], nomeArqSegue[20];
        int idPessoa;
        char status;

        scanf("%s %s %s %d %s", nomeArqPessoa, nomeArqIndex, nomeCampo, &idPessoa, nomeArqSegue);

        fileP = fopen(nomeArqPessoa, "rb");
        if(fileP == NULL)
        {
            printf("Falha no processamento do arquivo.");
            return 0;
        }

        fileI = fopen(nomeArqIndex, "rb");
        if(fileI == NULL)
        {
            printf("Falha no processamento do arquivo.");
            return 0;
        }

        fileSO = fopen(nomeArqSegue, "rb");
        if(fileSO == NULL)
        {
            printf("Falha no processamento do arquivo.");
            return 0;
        }

        rewind(fileP);
        fread(&status, sizeof(char), 1, fileP);
        if(status == '0')
        {
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }

        rewind(fileI);
        fread(&status, sizeof(char), 1, fileI);
        if(status == '0')
        {
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }

        rewind(fileSO);
        fread(&status, sizeof(char), 1, fileSO);
        if(status == '0')
        {
            printf("Falha no processamento do arquivo.\n");
            return 0;
        }

        if(buscaRegistro(fileP, fileI, nomeCampo, idPessoa) == OK)
            retornaRegistros(fileSO, idPessoa);


        fclose(fileP);
        fclose(fileI);
        fclose(fileSO);
    }

    else if(funcionalidade == 9)
    {

    }

    return 0;
}
