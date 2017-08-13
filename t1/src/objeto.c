#include <objeto.h>

OBJETO *cria_objeto(PONTO *coordenadas, int n_coordenadas) {
	OBJETO *novo = (OBJETO *) malloc(sizeof(OBJETO));
	novo->coordenadas = coordenadas;
	novo->n_coordenadas = n_coordenadas;
	return novo;
}

void free_objeto(OBJETO *o) {
	free(o->coordenadas);
	free(o);
}