#include <ponto.h>

PONTO *ler_pontos(int n_linhas) {
	PONTO *pontos = (PONTO *) malloc(sizeof(PONTO) * n_linhas);
	for(int i = 0; i < n_linhas; i++)
		scanf("%lf%*c%lf%*c%lf%*c", &(pontos+i)->x, &(pontos+i)->y,&(pontos+i)->z);
	return pontos;
}