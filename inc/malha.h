#ifndef _MALHA_H
#define _MALHA_H

#include <stdlib.h>
#include <stdio.h>
#include <ponto.h>

typedef ponto_t * triangulo_t;

typedef struct {
	triangulo_t *triangulos;
	int n_triangulos;
} malha_t;

malha_t *ler_malha(int);
void print_malha(malha_t *);
void free_malha(malha_t *);

#endif