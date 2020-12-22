#ifndef FUNCIONALIDADE9_H_INCLUDED
#define FUNCIONALIDADE9_H_INCLUDED

#include "LDED.h"

int buscaRegistro9(FILE* fileP, FILE* fileI, int IdOpcional, dadoPessoa* p);
int constroiGrafo(char* nomeArquivoSegue, char* nomeArqP, char* nomeArqI, Graph* *g);
void printa_f9(Graph* G);
int fillVertices(FILE* fileP, Graph* G);
int compararNome(const void *a, const void *b);

#endif // FUNCIONALIDADE9_H_INCLUDED
