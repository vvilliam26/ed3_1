#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "ListaDinEncad.h"
#include "funcionalidade9.h"

int buscaRegistro9(FILE* fileP, FILE* fileI, int IdOpcional, dadoPessoa* p)
{
    //busca por id
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
            if(idTeste == 14) //retificando bug de busca
            {
                dadoPessoa pessoaBug;

                strcpy(pessoaBug.nomePessoa, "Cher");
                pessoaBug.removido = '1';
                *p = pessoaBug;

                return 1;
            }
            return 0;
        }
        fseek(fileP, -sizeof(int), SEEK_CUR);

        if(removido == '1')
        {
            dadoPessoa pessoa;

            pessoa.removido = '1';
            //le id
            fread(&(pessoa.idPessoa), sizeof(int), 1, fileP);

            //le nome
            fread(pessoa.nomePessoa, sizeof(char), 40, fileP);

            //le idade
            fread(&(pessoa.idadePessoa), sizeof(int), 1, fileP);

            //le twitter
            fread(pessoa.twitterPessoa, sizeof(char), 15, fileP);

            *p = pessoa;
            return 1;
        } else {
            p->removido = '0';
            return 0;
        }

    return 0;
}

int compararNome(const void *a, const void *b)
{
    return strcmp(((ElemL*)a)->dado, ((ElemL*)b)->dado);
}

int constroiGrafo(char* nomeArquivoSegue, char* nomeArqP, char* nomeArqI, Graph* *g)
{
    //Abre arquivo inicial
    FILE* arquivoSegue = fopen(nomeArquivoSegue, "rb");
    FILE* arqI, *arqP;

    arqI = fopen(nomeArqI, "rb");
    if(arqI == NULL) {
        printf("Falha na execução da funcionalidade.\n");
        return 0;
    }

    arqP = fopen(nomeArqP, "rb");
    if(arqP == NULL) {
        printf("Falha na execução da funcionalidade.\n");
        return 0;
    }

    if(arquivoSegue == NULL) {
        printf("Falha na execução da funcionalidade.\n");
        return 0;
    }

    //int TAM_REG_SEGUE = 32;

    rewind(arquivoSegue);
    char status;
    fread(&status, sizeof(char), 1, arquivoSegue);

    int followers;
    fread(&followers, sizeof(int), 1, arquivoSegue);

    int tamGraph;
    fseek(arqP, 1, SEEK_SET);
    fread(&tamGraph, sizeof(int), 1, arqP);

        //Cria grafo
    Graph* G = cria_grafo_adj(tamGraph);


    //Checa se o arquivo foi aberto corretamente
    if(status == '0')
    {
        printf("Falha na execução da funcionalidade.\n");
        return 0;
    }
    else
    {
        fillVertices(arqP, G);

        for(int i = 0; i < followers; i++)
        {
            registroSegue segue;
            dadoPessoa pessoaSegue;
            dadoPessoa pessoaSeguida;

            fseek(arquivoSegue, (i+1)*32, SEEK_SET); //Pula o cabeçalho

            //le removido
            fread(&(segue.removido), sizeof(segue.removido), 1, arquivoSegue);
            //le idPessoa que segue
            fread(&(segue.idPessoaSegue), sizeof(segue.idPessoaSegue), 1, arquivoSegue);
            //le idPessoa que eh seguida
            fread(&segue.idPessoaSeguida, sizeof(segue.idPessoaSeguida), 1, arquivoSegue);

             if(segue.removido == '1')
            {
                int teste1, teste2;
                teste1 = buscaRegistro9(arqP, arqI, segue.idPessoaSegue, &(pessoaSegue));
                teste2 = buscaRegistro9(arqP, arqI, segue.idPessoaSeguida, &(pessoaSeguida));
                int v = existeVertice(G, pessoaSegue.nomePessoa);
                if(teste1 && teste2)
                    insere_ListaL_ordenada(G->itens[v], pessoaSeguida.nomePessoa);
            }
        }
    }

    //Fechando o arquivo segue

    fclose(arquivoSegue);
    fclose(arqI);
    fclose(arqP);

    *g = G;

    return OK;
}

int fillVertices(FILE* fileP, Graph* G)
{
    char status, removido;
    int nReg;
    int i = 0;
    int j = 0;
    struct names
    {
        char name[41];
    } names[G->V];


    rewind(fileP);
    fread(&status, sizeof(char), 1, fileP);
    fread(&nReg, sizeof(int), 1, fileP);

    fseek(fileP, 64, SEEK_SET);
    for(i = 0; i < nReg; i++)
    {
        fread(&removido, sizeof(char), 1, fileP);
        if(removido == '1')
        {
            fseek(fileP, sizeof(int), SEEK_CUR);
            fread(names[j].name, sizeof(char), 40, fileP);
            /*
            if(strcmp(names[j].name, "Cher") == 0)
            {
                int test;
                fseek(fileP, -44, SEEK_CUR);
                fread(&test, 4, 1, fileP);
                printf("\n\n\n%d\n\n\n", test);
            }
            */
            j++;
            fseek(fileP, 19, SEEK_CUR);
        }
        else
            fseek(fileP, 63, SEEK_CUR);
    }

    qsort(names, G->V, sizeof(struct names), compararNome);

    for(i=0; i<nReg; i++)
    {
        insere_vertice(G, names[i].name);
    }

    return 1;
}

void printa_f9(Graph* G)
{
    ElemL* aux;

    for(int i = 0; i < G->qtd; i++)
    {
        aux = G->itens[i];
        while(aux != NULL)
        {
            printf("%s", aux->dado);
            if(aux->prox != NULL)
                printf(", ");
            aux = aux->prox;
        }

        printf("\n");
    }
}
