#include <stdlib.h>
#include <stdio.h>
#include <bool.h>
#include <limits.h>

typedef struct {
	double x;
	double y;
	double z;
} PONTO;

typedef struct {
	PONTO *coordenadas;
	int n_coordenadas;
} OBJETO, CAIXA;

void free_objeto(OBJETO *o) {
	free(o->coordenadas);
	free(o);
}

void print_objeto(OBJETO *o) {
	for(int i = 0; i < o->n_coordenadas; i++) {
		printf("x = %lf\n", o->coordenadas[i].x);
		printf("y = %lf\n", o->coordenadas[i].y);
		printf("z = %lf\n", o->coordenadas[i].z);
		printf("\n");
	}
}

// Função que delimita uma caixa a partir de um objeto
CAIXA *delimitar_caixa(OBJETO *o) {
	double max_x = INT_MIN;
	double max_y = INT_MIN;
	double max_z = INT_MIN;

	double min_x = INT_MAX;
	double min_y = INT_MAX;
	double min_z = INT_MAX;

	for(int i = 0; i < o->n_coordenadas; i++) {
		if(o->coordenadas[i].x < min_x)
			min_x = o->coordenadas[i].x;
		if(o->coordenadas[i].y < min_y)
			min_y = o->coordenadas[i].y;
		if(o->coordenadas[i].z < min_z)
			min_z = o->coordenadas[i].z;

		if(o->coordenadas[i].x > max_x)
			max_x = o->coordenadas[i].x;
		if(o->coordenadas[i].y > max_y)
			max_y = o->coordenadas[i].y;
		if(o->coordenadas[i].z > max_z)
			max_z = o->coordenadas[i].z;
	}

	PONTO *coord = (PONTO *) malloc(sizeof(PONTO) * 8);
	CAIXA *resp = (CAIXA *) malloc(sizeof(CAIXA));
	resp->coordenadas = coord;
	resp->n_coordenadas = 8;
	return resp;
}

int main(int argc, char *argv[]) {
	// Primeiro, obtemos todas as informações
	// necessárias parar esolver o problema
	bool precisa_fazer_caixa;
	scanf("%d%*c", (int *)(&precisa_fazer_caixa));

	if(precisa_fazer_caixa) printf("Precisa fazer a caixa\n");
	else printf("precisa ler a caixa\n");

	// Altura limite para percorrer a octree
	int h_max;
	scanf("%d%*c", &h_max);
	printf("A altura maxima e %d\n", h_max);

	// Número de triângulos que compões o objeto
	int n;
	scanf("%d%*c", &n);
	printf("O objeto possui %d triangulos\n", n);
	int n_coordenadas = 3 * n;

	PONTO *ponto_colisor = (PONTO *) malloc(sizeof(PONTO));
	scanf("%lf%*c%lf%*c%lf%*c", &ponto_colisor->x, &ponto_colisor->y, &ponto_colisor->z);
	printf("Obejeto colisor: %lf %lf %lf \n", ponto_colisor->x, ponto_colisor->y, ponto_colisor->z);

	PONTO *pontos_objeto = (PONTO *) malloc(sizeof(PONTO) * n_coordenadas);
	for(int i = 0; i < n_coordenadas; i++) {
		scanf("%lf%*c%lf%*c%lf%*c", &pontos_objeto[i].x, &pontos_objeto[i].y, &pontos_objeto[i].z);
		printf("coordanda %d: %lf %lf %lf \n", i, pontos_objeto[i].x, pontos_objeto[i].y, pontos_objeto[i].z);
		if(i > 0 && i % 3 == 2) printf("leu o triangulo %d\n", i / 3 + 1);
	}

	OBJETO *objeto = (OBJETO *) malloc(sizeof(OBJETO));
	objeto->n_coordenadas = n_coordenadas;
	objeto->coordenadas = pontos_objeto;

	CAIXA *caixa;
	if(precisa_fazer_caixa) {
		caixa = delimitar_caixa(objeto);
	}
	else {
		caixa = (CAIXA *) malloc(sizeof(CAIXA));
		caixa->n_coordenadas = 8;
		caixa->coordenadas = (PONTO *) malloc(sizeof(PONTO) * 8);

		for(int i = 0; i < 8; i++)
			scanf("%lf%*c%lf%*c%lf%*c", &caixa[i].coordenadas->x, &caixa[i].coordenadas->y, &caixa[i].coordenadas->z);
	}

	free(ponto_colisor);
	free_objeto(objeto);
	free_objeto(caixa);
	return 0;
}