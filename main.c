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

// Vinicius William da Silva - 11233842
// Gabriel Fernandes Araujo - 11200334




//funcionalidade1.h -----------------------------------------------
static char LIXO = '$';
static int TAM_REG = 64;
static int STR_END = '\0';

int inicializaCabecalhoPessoa(FILE *fileP, cabecalhoArqPessoa *cp);
int atualizaCabecalhoPessoa(FILE *fileP, cabecalhoArqPessoa cp);
void insereBinario(FILE *fileP, cabecalhoArqPessoa *cp, Lista* li, dadoPessoa pessoa);
int montaIndex(char *nomeArqIndex, Lista* li);

//funcionalidade1.h -----------------------------------------------






//funcionalidade1.c -----------------------------------------------

int inicializaCabecalhoPessoa(FILE *fileP, cabecalhoArqPessoa *cp) {
    if(!fileP) {
        printf("Falha no carregamento do arquivo.\n");
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
       printf("Falha no carregamento do arquivo.\n");
       return ERRO;
   }

   rewind(fileP);
   fwrite(&(cp.status), sizeof(char), 1, fileP);
   fwrite(&(cp.qtdPessoas), sizeof(int), 1, fileP);

   return OK;
}

void insereBinario(FILE *fileP, cabecalhoArqPessoa *cp, Lista* li, dadoPessoa pessoa) {
    if(fileP == NULL) {
        printf("Falha no carregamento do arquivo.\n");
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
        printf("Falha no carregamento do arquivo.\n");
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
        }

        if(qtdPessoas == 0)
            printf("Registro inexistente.\n");

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
        printf("Idade: -\n");
    else
        printf("Idade: %d anos\n", pessoa.idadePessoa);

    printf("Twitter: %s\n\n", pessoa.twitterPessoa);



}


//funcionalidade2.c -----------------------------------------------






//funcionalidade3.h -----------------------------------------------

void buscaRegistro(FILE* fileP, FILE* fileI, char *nomeDoCampo);
int checaIntegridadeP(FILE* fileP);
int checaIntegridadeI(FILE *fileI);

//funcionalidade3.h -----------------------------------------------




//funcionalidade3.c -----------------------------------------------

void buscaRegistro(FILE* fileP, FILE* fileI, char *nomeDoCampo)
{
    //busca por id
    if(strcmp(nomeDoCampo, "idPessoa") == 0)
    {
        int id;
        int rrn;
        int idTeste;
        scanf("%d", &id);

        //acha o rrn pelo indexPessoa
        fseek(fileI, (id * 8)+4, SEEK_SET); //estah contando com o cabecalho
        fread(&rrn, sizeof(int), 1, fileI);

        //le os dados em pessoa pelo rrn
        char removido;
        fseek(fileP, ((rrn+1) * TAM_REG), SEEK_SET); //pula o cabecalho e os outros registros
        fread(&removido, sizeof(char), 1, fileP);
        fread(&idTeste, sizeof(int), 1, fileP);
        if(idTeste != id)
        {
            printf("Registro inexistente.\n");
            return;
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
        } else {
            printf("Registro inexistente."); //registro removido
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
                printf("Registro inexistente.\n ");
            else
                printaFormatado(pessoa);
        } else
            printf("Registro inexistente.\n");

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
            printf("Registro inexistente.");

    }
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

//funcionalidade3.c -----------------------------------------------







//funcionalidade4.h -----------------------------------------------


//funcionalidade4.h -----------------------------------------------



//funcionalidade4.c -----------------------------------------------

void insereRegistros(FILE* fileP, FILE* fileI)
{
    //int n;

    //scanf("%d", &d);


}


//funcionalidade4.c -----------------------------------------------

//funcionalidade6.h
int inicializaCabecalhoSegue(FILE *fileP, cabecalhoSegue *cp);
int atualizaCabecalhoSegue(FILE *fileP, cabecalhoSegue cp);
void insereBinarioSegue(FILE *fileP, cabecalhoSegue *cp, Lista2* li, registroSegue segue);

//funcionalidade6.c
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
    for(int i = 0; i < (TAM_REG - 5); i++) //fill de lixo
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
    fseek(fileP, ((novoRrn+1) * TAM_REG), SEEK_SET); //posiciona o ponteiro no registro a ser escrito pulando o cabecalho

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
    lixoTam = 10 - strlen(segue.startDateSegue) - 1;

    //escreve data final de seguidor
    fwrite(segue.endDateSegue, sizeof(char), strlen(segue.endDateSegue), fileP);
    fwrite(&STR_END, sizeof(char), 1, fileP);
    lixoTam = 10 - strlen(segue.endDateSegue) - 1;

    for(i = 0; i < lixoTam; i++)
    {
        fwrite(&LIXO, sizeof(char), 1, fileP); //fill de lixo
    }

    cp->followers += 1;

    insere_lista_segue(li, segue);
}



int main()
{
    int funcionalidade;


    scanf("%d", &funcionalidade);

    if(funcionalidade == 1) //leitura e gravacao de arquivos
    {
        char nomeArqCsv[40];
        char nomeArquivoPessoa[40], nomeArquivoIndex[40];
        FILE *csv; //arquivo de leitura
        FILE *fileP; //arquivos de escrita: pessoa e index
        Lista *li = cria_lista(); //criando lista duplamente encadeada
        cabecalhoArqPessoa cp; //cabecalho do arquivo pessoa

        scanf("%s", nomeArqCsv);
        csv = fopen(nomeArqCsv, "r");
        if(csv == NULL)
        {
            printf("Falha no carregamento do arquivo.\n");
            return ERRO;
        }

        scanf("%s", nomeArquivoPessoa);
        fileP = fopen(nomeArquivoPessoa, "wb");
        if(fileP == NULL)
        {
            printf("Falha no carregamento do arquivo.\n");
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

        buscaRegistro(fileP, fileI, nomeCampo);

        fclose(fileI);
        fclose(fileP);
    }

    else if(funcionalidade == 4)
    {

    }
    else if(funcionalidade == 6)
    {
        char nomeArqCsv[40];
        char nomeArquivoSegue[40];
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

        inicializaCabecalhoSegue(fileP, &cp); //monta cabecalho arquivo pessoa

        fseek(csv, 45, SEEK_SET); //pulando o cabecalho do arquivo csv
        int auxIdPessoa; //criei para auxiliar no while abaixo

        registroSegue segue;

        //leitura id
        while(fscanf(csv, "%d%*c", &auxIdPessoa) > 0)
        {
            //valores padrao

            segue.removido = '1';

            fscanf(csv, "%d%*c", &(segue.idPessoaSegue));
            fscanf(csv, "%d%*c", &(segue.idPessoaSeguida));
            fscanf(csv, "%[^,]", segue.grauAmizade);
            fscanf(csv, "%*c%[^,]", segue.startDateSegue);
            fscanf(csv, "%*c%[^,\n]", segue.endDateSegue);

            printf("\n%d,%d,%s,%s,%s \n", segue.idPessoaSegue, segue.idPessoaSeguida, segue.grauAmizade, segue.startDateSegue, segue.endDateSegue);

            segue.grauAmizade[2] = '$';
            //inserindo no arquivo binario
            insereBinarioSegue(fileP, &cp, li, segue);
        }
        cp.status = '1';
        atualizaCabecalhoSegue(fileP, cp);

        fclose(fileP);
        fclose(csv);

        libera_lista2(li);

        binarioNaTela2(nomeArquivoSegue);
    }

    return 0;
}
