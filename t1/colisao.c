#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <bool.h>

#include <ponto.h>
#include <malha.h>
#include <caixa.h>

// Função que delimita uma caixa a partir de uma malha de triângulos
caixa_t *delimitar_caixa_malha(malha_t *malha);

// Função que, a partir de uma caixa propriamente
// dita, cria uma caixa reduzida, ou seja,
// armazena apenas o valor máximo e mínimo de cada eixo
caixa_t* *delimitar_caixa_caixa(caixa_t *caixa);


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

	// Número de triângulos que compõem o objeto
	int n_triangulos;
	scanf("%d%*c", &n_triangulos);
	printf("%d\n", n_triangulos);

	// Coordenadas do ponto colisor:
	ponto_t* ponto_colisor = ler_pontos(1);
	print_pontos(ponto_colisor, 1);

	// Leitura da malha de triangulos que compõem o objeto:
	malha_t *objeto = ler_malha(n_triangulos);
	print_malha(objeto);

	// Agora que temos as coordenadas do objeto, podemos,
	// ou fazer a caixa, ou ler ela da entrada principal
	caixa_t *caixa;
	if(precisa_fazer_caixa)
		caixa = delimitar_caixa_malha(objeto);
	else {
		ponto_t *pontos_caixa_aux = ler_pontos(8);
		caixa_t *caixa_aux = nova_caixa(pontos_caixa_aux, 8);
		
		caixa = delimitar_caixa_caixa(caixa_aux);

		printf("Caixa real\n");
		print_caixa(caixa_aux);

		printf("\n\nCaixa fake\n");
		print_caixa(caixa);
		
		free_caixa(caixa_aux);
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

	free_malha(objeto);
	free_caixa(caixa);
	free_ponto(ponto_colisor);

	return 0;
}

caixa_t *delimitar_caixa_malha(malha_t *m) {
	// Começamos encontrando os limites do objeto em cada eixo
	double max_x = INT_MIN;
	double max_y = INT_MIN;
	double max_z = INT_MIN;

	double min_x = INT_MAX;
	double min_y = INT_MAX;
	double min_z = INT_MAX;

	for(int i = 0; i < m->n_triangulos; i++) {
		for(int j = 0; j < 3; j++) {
			if(m->triangulos[i][j][X] < min_x)
				min_x = m->triangulos[i][j][X];
			if(m->triangulos[i][j][Y] < min_y)
				min_y = m->triangulos[i][j][Y];
			if(m->triangulos[i][j][Z] < min_z)
				min_z = m->triangulos[i][j][Z];

			if(m->triangulos[i][j][x] > max_x)
				max_x = m->triangulos[i][j][x];
			if(m->triangulos[i][j][Y] > max_y)
				max_y = m->triangulos[i][j][Y];
			if(m->triangulos[i][j][Z] > max_z)
				max_z = m->triangulos[i][j][Z];
		}
	}

	ponto_t *pontos_caixa = (ponto_t *) malloc(sizeof(ponto_t) * N_PONTOS);

	pontos_caixa[MAX][X] = max_x;
	pontos_caixa[MAX][Y] = max_y;
	pontos_caixa[MAX][Z] = max_z;
	
	pontos_caixa[MIN][X] = min_x;
	pontos_caixa[MIN][Y] = min_y;
	pontos_caixa[MIN][Z] = min_z;

	return nova_caixa(pontos_caixa, N_PONTOS);
}

caixa_t* *delimitar_caixa_caixa(caixa_t *caixa) {
	// Começamos encontrando os limites da caixa em cada eixo
	double max_x = INT_MIN;
	double max_y = INT_MIN;
	double max_z = INT_MIN;

	double min_x = INT_MAX;
	double min_y = INT_MAX;
	double min_z = INT_MAX;

	for(int i = 0; i < caixa->n_pontos; i++) {
		if(m->pontos[i][X] < min_x)
			min_x = m->pontos[i][X];
		if(m->pontos[i][Y] < min_y)
			min_y = m->pontos[i][Y];
		if(m->pontos[i][Z] < min_z)
			min_z = m->pontos[i][Z];

		if(m->pontos[i][x] > max_x)
			max_x = m->pontos[i][x];
		if(m->pontos[i][Y] > max_y)
			max_y = m->pontos[i][Y];
		if(m->pontos[i][Z] > max_z)
			max_z = m->pontos[i][Z];
	}

	ponto_t *pontos_caixa = (ponto_t *) malloc(sizeof(ponto_t) * N_PONTOS);

	pontos_caixa[MAX][X] = max_x;
	pontos_caixa[MAX][Y] = max_y;
	pontos_caixa[MAX][Z] = max_z;
	
	pontos_caixa[MIN][X] = min_x;
	pontos_caixa[MIN][Y] = min_y;
	pontos_caixa[MIN][Z] = min_z;

	return nova_caixa(pontos_caixa, N_PONTOS);
}