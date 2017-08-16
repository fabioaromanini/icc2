#ifndef _OBJETO_H
#define _OBJETO_H

#include <stdlib.h>
#include <ponto.h>

// Essa estrutura encapsula o vetor de pontos que compõe um objeto,
// e seu tamanho, a fim de facilitar a iteração sobre o conjunto de dados.
// Como os pontos de uma caixa são uma combinaçao de 6 coordenadas
// tomada de 3 em 3, utilizaremos a mesma estrutura de dados para representá-la.

typedef struct {
	PONTO *coordenadas;
	int n_coordenadas;
} OBJETO, CAIXA;

OBJETO *cria_objeto(PONTO *, int);
void free_objeto(OBJETO *);

#endif
