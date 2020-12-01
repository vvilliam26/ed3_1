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
static int TAM_REG_SEGUE = 32;
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

int buscaRegistro(FILE* fileP, FILE* fileI, char *nomeDoCampo, int idOpcional);
int checaIntegridadeP(FILE* fileP);
int checaIntegridadeI(FILE *fileI);

//funcionalidade3.h -----------------------------------------------




//funcionalidade3.c -----------------------------------------------

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
        fseek(fileP, ((rrn+1) * TAM_REG), SEEK_SET); //pula o cabecalho e os outros registros
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

//funcionalidade3.c -----------------------------------------------







//funcionalidade4.h -----------------------------------------------


//-----------------------------------------------------------------



//funcionalidade4.c -----------------------------------------------

void insereRegistros(FILE* fileP, FILE* fileI)
{
    //int n;

    //scanf("%d", &d);


}


//-----------------------------------------------------------------

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

//funcionalidade7.c
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

//funcionalidade8.h -----------------------------------------------
int buscaRegistroBinario(FILE* fileSO, int idPessoa, int limInf, int limSup, int *found);
void printaSegue(registroSegue registro);

//-----------------------------------------------------------------


//funcionalidade8.c -----------------------------------------------
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
    int cont = 1;//contador para o seek
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

//-----------------------------------------------------------------



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

    return 0;
}
