#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include <bool.h>
#include <ponto.h>
#include <objeto.h>

#define MAX 0
#define MIN 1

// Função que delimita uma caixa a partir de um objeto
CAIXA *delimitar_caixa(OBJETO *o);

int main(int argc, char *argv[]) {
	// Primeiro, obteremos todas as informações
	// necessárias para determinar se houve colisão:

	// Caso o programa não receba a caixa delimitadora do objeto,
	// precisaremos implementá-la.
	bool precisa_fazer_caixa;
	scanf("%d%*c", (int *)(&precisa_fazer_caixa));
	printf("%d\n", (int) precisa_fazer_caixa);

	// Numero de iterações para rodar o algoritmo
	int n_max;
	scanf("%d%*c", &n_max);
	printf("%d\n", n_max);

	// Número de triângulos que compõe o objeto
	int n_triangulos;
	scanf("%d%*c", &n_triangulos);
	printf("%d\n", n_triangulos);

	// Como cada triângulo é delimitado por 3 pontos
	int n_pontos = 3 * n_triangulos;

	// Coordenadas do ponto colisor
	PONTO* ponto_colisor = ler_pontos(1);
	printf("%lf %lf %lf\n", ponto_colisor->x, ponto_colisor->y, ponto_colisor->z);

	// Coordenadas de todos os pontos que compõe o objeto
	PONTO *pontos_objeto = ler_pontos(n_pontos);
	for(int i = 0; i < n_pontos; i++)
		printf("%lf %lf %lf\n", pontos_objeto[i].x, pontos_objeto[i].y, pontos_objeto[i].z);

	// Encapsularemos o vetor de coordenadas e
	// seu tamanho em uma struct para facilitar
	// a iteração sobre o conjunto de dados
	OBJETO *objeto = cria_objeto(pontos_objeto, n_pontos);

	// Agora que temos as coordenadas do objeto, podemos,
	// ou fazer a caixa, ou ler ela da entrada principal
	CAIXA *caixa;
	if(precisa_fazer_caixa)
		caixa = delimitar_caixa(objeto);
	else {
		PONTO *pontos_caixa = ler_pontos(8);
		OBJETO *caixa_auxiliar = cria_objeto(pontos_caixa, 8);
		caixa = delimitar_caixa(caixa_auxiliar);

		// printf("Caixa real\n");
		for(int i = 0; i < 8; i++)
			printf("%lf %lf %lf\n", caixa_auxiliar->coordenadas[i].x, caixa_auxiliar->coordenadas[i].y, caixa_auxiliar->coordenadas[i].z);


		// printf("\n\nCaixa fake\n");
		// for(int i = 0; i < 2; i++)
			// printf("%lf %lf %lf\n", caixa->coordenadas[i].x, caixa->coordenadas[i].y, caixa->coordenadas[i].z);
		
		free_objeto(caixa_auxiliar);
	}

	// Uma vez que temos os dados necessários, executaremos o 
	// algoritmo responsável por escolher entre os 8 possíveis
	// octantes da caixa delimitadora.
	int nivel = 1;
	bool colisao = TRUE;
	while(nivel <= n_max) {

		nivel++;
	}

	if(colisao)
		printf("1\n");
	else
		printf("0\n");

	free_objeto(objeto);
	free_objeto(caixa);
	free(ponto_colisor);

	return 0;
}

CAIXA *delimitar_caixa(OBJETO *o) {
	// Começamos encontrando os limites do objeto em cada eixo
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

	PONTO *coord = (PONTO *) malloc(sizeof(PONTO) * 2);

	(coord + MAX)->x = max_x;
	(coord + MAX)->y = max_y;
	(coord + MAX)->z = max_z;
	(coord + MIN)->x = min_x;
	(coord + MIN)->y = min_y;
	(coord + MIN)->z = min_z;

	CAIXA *resp = (CAIXA *) malloc(sizeof(CAIXA));

	resp->coordenadas = coord;
	resp->n_coordenadas = 2;
	return resp;
}