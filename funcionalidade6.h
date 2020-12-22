#ifndef FUNCIONALIDADE6_H_INCLUDED
#define FUNCIONALIDADE6_H_INCLUDED

#include "LDED.h"

int inicializaCabecalhoSegue(FILE *fileP, cabecalhoSegue *cp);
int atualizaCabecalhoSegue(FILE *fileP, cabecalhoSegue cp);
void insereBinarioSegue(FILE *fileP, cabecalhoSegue *cp, Lista2* li, registroSegue segue);

#endif // FUNCIONALIDADE6_H_INCLUDED
