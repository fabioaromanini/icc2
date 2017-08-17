#include <malha.h>

malha_t *ler_malha(int n_triangulos) {
	// Leremos os pontos do triangulo, e depois
	// atribuiremos à variável do tipo malha_t
	triangulo_t *triangulos = (triangulo_t *) malloc(sizeof(triangulo_t) * n_triangulos);
	
	// Cada triangulo é um vetor de 3 pontos
	for(int i = 0; i < n_triangulos; i++)
		triangulos[i] = ler_pontos(3);

	malha_t *m = (malha_t *) malloc(sizeof(malha_t));
	m->triangulos = triangulos;
	m->n_triangulos = n_triangulos;
	return m;
}

void print_malha(malha_t *m) {
	for(int i = 0; i < m->n_triangulos; i++) {
		printf("Triangulo %d:\n", i);

		for(int j = 0; j < 3; j++)
			print_ponto(m->triangulos[i][j]);

		printf("\n\n");
	}
}

void free_malha(malha_t *m) {
	for(int i = 0; i < m->n_triangulos; i++) {
		for(int j = 0; j < 3; j++)
			free_ponto(m->triangulos[i][j]);
	
		free(m->triangulos[i]);
	}

	free(m);
}