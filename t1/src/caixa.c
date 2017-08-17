#include <caixa.h>

caixa_t *nova_caixa(ponto_t *pontos, int n_pontos) {
	caixa_t *resp = (caixa_t *) malloc(sizeof(caixa_t));
	resp->pontos = pontos;
	resp->n_pontos = n_pontos;
	return resp;
}

void print_caixa(caixa_t *c) {
	for(int i = 0; i < c->n_pontos; i++) {
		printf("Ponto %d: ", i);
		print_ponto(c->pontos[i]);
	}
}

void free_caixa(caixa_t *c) {
	for(int i = 0; i < c->n_pontos; i++)
		free_ponto(c->pontos[i]);
	free(c->pontos);
	free(c);
}
