#ifndef _PONTO_H
#define _PONTO_H

#include <stdlib.h>
#include <stdio.h>

// Cada ponto_t é um vetor com 3 doubles, um para cada eixo (X, Y e Z, conforme o enum)
typedef double * ponto_t;

enum {
	X,
	Y,
	Z,
	N_EIXOS
};

ponto_t *ler_pontos(int);
void print_ponto(ponto_t);
void free_ponto(ponto_t);

#endif
