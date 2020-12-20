
/*
 *	~         Fila         ~
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
 *	Como usar esta biblioteca de fila:
 *
 *	1) Primeiro, é necessário alocar a fila na memória, indicando qual elemento será enfileirado (int, float, double, struct, ...):
 *			QUEUE *fila = Q_New(sizeof(int));
 *	2) Para enfileirar, basta passar o endereço do elemento com o valor a ser enfileirado:
 *			int variavel_qualquer = 5;
 *			Q_Push(&variavel_qualquer, fila);
 *	3) Para desenfileirar, basta passar o endereço de onde salvar o valor do elemento:
 *			int variavel_qualquer;
 *			Q_Shift(&variavel_qualquer, fila);
 *	4) Para obter o tamanho da fila:
 *			tamanho_da_fila = Q_Size(fila);
 *	5) Para liberar a fila quando não for mais usar (free):
 *			Q_Destroy(fila);
 *
 *	Veja o código exemplo abaixo que enfileira 3 floats e desenfileira em seguida:
 *
 *	QUEUE *q;
 *	float valor;
 *
 *	q = Q_New(sizeof(float)); // Inicializar fila - como nosso dado é do tipo "float", passa como argumento "sizeof(float)"
 *
 *	valor = 3.14;
 *	Q_Push(&valor, q); // Enfileirar 3.14
 *
 *	valor = 9.6;
 *	Q_Push(&valor, q); // Enfileirar 9.6
 *
 *	valor = 10.0;
 *	Q_Push(&valor, q); // Enfileirar 10.0
 *
 *	while(Q_Size(q) > 0) { // Imprimir 3.14 9.60 10.00 (na ordem em que desinfileira)
 *		Q_Shift(&valor, q);
 *		printf("%.2f ", valor);
 *	}
 *
 *	Q_Destroy(p); // Free
 *
 *
 *
*/

#ifndef QUEUE_H_
#define QUEUE_H_
#include <stdlib.h>



	typedef struct __queue_t QUEUE;



	struct __queue_t *Q_New(size_t);

	long Q_Size(struct __queue_t *);

	int Q_Push(void *, struct __queue_t *);

	int Q_Front(void *, struct __queue_t *);

	int Q_Shift(void *, struct __queue_t *);

	void Q_Destroy(struct __queue_t *);



#endif