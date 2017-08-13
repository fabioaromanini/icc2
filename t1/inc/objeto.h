#ifndef _OBJETO_H
#define _OBJETO_H

#include <stdlib.h>
#include <ponto.h>

// Essa estrutura encapsula o vetor de pontos que compõe um objeto,
// e seu tamanho, a fim de facilitar a iteração sobre o conjunto de dados.
// Como uma caixa é um paralelepipedo de 8 coordenadas, utilizaremos a mesma
// estrutura de dados para representá-la.

typedef struct {
	PONTO *coordenadas;
	int n_coordenadas;
} OBJETO, CAIXA;

OBJETO *cria_objeto(PONTO *, int);
void free_objeto(OBJETO *);

#endif
