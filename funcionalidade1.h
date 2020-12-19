#ifndef FUNCIONALIDADE1_H_INCLUDED
#define FUNCIONALIDADE1_H_INCLUDED

#include "LDED.h"
static int TAM_REG = 64;

int inicializaCabecalhoPessoa(FILE *fileP, cabecalhoArqPessoa *cp);
int atualizaCabecalhoPessoa(FILE *fileP, cabecalhoArqPessoa cp);
void insereBinario(FILE *fileP, cabecalhoArqPessoa *cp, Lista* li, dadoPessoa pessoa);
int montaIndex(char *nomeArqIndex, Lista* li);


#endif // FUNCIONALIDADE1_H_INCLUDED


