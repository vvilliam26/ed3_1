#include <stdio.h>
#include <stdlib.h>
#include "ListaDinEncad.h"

int main()
{
    Elem *Ptr;
    Lista* li = cria_lista();

    printf("Tamanho: %d\n\n\n\n",tamanho_lista(li));

    int i;
    for(i=0; i <= 8; i+=2)
        insere_lista_ordenada(li,i);

    imprime_lista(li);
    printf("\n\n\n\n Tamanho: %d\n",tamanho_lista(li));

    for(i=0; i < 5; i++){
        remove_lista_final(li);
        imprime_lista(li);
        printf("\n Tamanho: %d\n\n\n",tamanho_lista(li));
    }

    for(i=0; i < 8; i++)
        insere_lista_ordenada(li,i);
    imprime_lista(li);

    if (consulta_lista_dado(li, 3, &Ptr))
        printf("Consulta Dado: 3 => Achou - %p \n",Ptr);
    else
        printf("Consulta Dado: 3 => Nao Achou\n");

    if (consulta_lista_dado(li, 44, &Ptr))
        printf("Consulta Dado: 44 => Achou - %p \n",Ptr);
    else
        printf("Consulta Dado: 44 => Nao Achou\n");

    libera_lista(li);
    system("pause");
    return 0;
}

