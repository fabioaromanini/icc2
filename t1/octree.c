#include <stdlib.h>
#include <stdio.h>
#include <boolean.h>

typedef struct {
	double x;
	double y;
	double z;
} PONTO;

void print_ponto(PONTO *p, int n) {
	for(int i = 0; i < n; i++) {
		printf("x = %lf\n", p->x);
		printf("y = %lf\n", p->y);
		printf("z = %lf\n", p->z);
		printf("\n");
	}
}

int main(int argc, char *argv[]) {
	// 1 - Leitura dos dados
	boolean tem_caixa;
	scanf("%d%*c",  (int *)(&tem_caixa));

	// Altura limite para percorrer a octree
	int h_max;
	scanf("%d%*c",  &h_max);

	// Caso seja passada uma caixa delimitadora, a variável n conterá a quantidade de vértices 
	// do objeto. Caso contrário, ela conterá a quantidade de triângulos.
	int n;
	scanf("%d%*c",  &n);

	PONTO *ponto_colisor = (PONTO *) malloc(sizeof(PONTO));
	scanf("%lf%*c%lf%*c%lf%*c", &ponto_colisor->x, &ponto_colisor->y, &ponto_colisor->z);

	// De acordo com a informação passada, leeremos o número de triângulos ou vértices
	PONTO *objeto = (PONTO *) malloc(sizeof(PONTO) * n);
	for(int i = 0; i < n; i++)
		scanf("%lf%*c%lf%*c%lf%*c", &(objeto + i)->x, &(objeto + i)->y, &(objeto + i)->z);

	print_ponto(objeto, n);

	free(objeto);
	free(ponto_colisor);
	return 0;
}