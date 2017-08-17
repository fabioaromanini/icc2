#include <ponto.h>

ponto_t *ler_pontos(int n_linhas) {
	ponto_t *pontos = (ponto_t *) malloc(sizeof(ponto_t) * n_linhas);
	for(int i = 0; i < n_linhas; i++) {
		pontos[i] = (ponto_t) malloc(sizeof(double) * N_EIXOS);
		scanf("%lf%*c%lf%*c%lf%*c", &(pontos[i][X]), &(pontos[i][Y]), &(pontos[i][Z]));
	}

	return pontos;
}

void print_pontos(ponto_t p) {
	printf("%lf %lf %lf\n\n", p[X], p[Y], p[Z]);
}

void free_ponto(ponto_t p) {
	free(p);
}
