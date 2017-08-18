#ifndef _CAIXA_H
#define _CAIXA_H

#include <stdlib.h>
#include <stdio.h>
#include <ponto.h>

enum {
	MIN,
	MAX,
	N_PONTOS
};

typedef	struct {
	ponto_t *pontos;
	int n_pontos;
} caixa_t;

caixa_t *nova_caixa(ponto_t *, int);
void free_caixa(caixa_t *);
// Função usada para ajudar no debugging, então deixei aí
void print_caixa(caixa_t *);

#endif