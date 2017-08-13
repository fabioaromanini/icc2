#ifndef _PONTO_H
#define _PONTO_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
	double x;
	double y;
	double z;
} PONTO;

PONTO *ler_pontos(int);

#endif