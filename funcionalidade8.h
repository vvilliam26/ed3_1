#ifndef FUNCIONALIDADE8_H_INCLUDED
#define FUNCIONALIDADE8_H_INCLUDED

#include "LDED.h"

int buscaRegistroBinario(FILE* fileSO, int idPessoa, int limInf, int limSup, int *found);
void printaSegue(registroSegue registro);
void retornaRegistros(FILE* fileSO, int idPessoa);

#endif // FUNCIONALIDADE8_H_INCLUDED
