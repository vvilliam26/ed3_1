
/*
 *	~         Pilha         ~
 *
 *	Matheus Carvalho Raimundo
 *	mcarvalhor@usp.br
 *	 _______ _______ _______
 *	|   |   |               \
 *	|   |   |      \    |___|
 *	|   |    \      |   |
 *	|_______ _______|___|
 *
*/



/*
 *	Como usar esta biblioteca de pilha:
 *
 *	1) Primeiro, é necessário alocar a pilha na memória, indicando qual elemento será empilhado (int, float, double, struct, ...):
 *			STACK *pilha = S_New(sizeof(int));
 *	2) Para empilhar, basta passar o endereço do elemento com o valor a ser empilhado:
 *			int variavel_qualquer = 5;
 *			S_Push(&variavel_qualquer, pilha);
 *	3) Para desempilhar, basta passar o endereço de onde salvar o valor do elemento:
 *			int variavel_qualquer;
 *			S_Pop(&variavel_qualquer, pilha);
 *	4) Para obter o tamanho da pilha:
 *			tamanho_da_pilha = S_Size(pilha);
 *	5) Para liberar a pilha quando não for mais usar (free):
 *			S_Destroy(pilha);
 *
 *	Veja o código exemplo abaixo que empilha 3 floats e desempilha em seguida:
 *
 *	STACK *p;
 *	float valor;
 *
 *	p = S_New(sizeof(float)); // Inicializar pilha - como nosso dado é do tipo "float", passa como argumento "sizeof(float)"
 *
 *	valor = 3.14;
 *	S_Push(&valor, p); // Empilhar 3.14
 *
 *	valor = 9.6;
 *	S_Push(&valor, p); // Empilhar 9.6
 *
 *	valor = 10.0;
 *	S_Push(&valor, p); // Empilhar 10.0
 *
 *	while(S_Size(p) > 0) { // Imprimir 10.00 9.60 3.14 (na ordem em que desempilha)
 *		S_Pop(&valor, p);
 *		printf("%.2f ", valor);
 *	}
 *
 *	S_Destroy(p); // Free
 *
 *
 *
*/

#ifndef STACK_H_
#define STACK_H_
#include <stdlib.h>



	typedef struct __stack_t STACK;



	struct __stack_t *S_New(size_t);

	long S_Size(struct __stack_t *);

	int S_Push(void *, struct __stack_t *);

	int S_Top(void *, struct __stack_t *);

	int S_Pop(void *, struct __stack_t *);

	void S_Destroy(struct __stack_t *);



#endif