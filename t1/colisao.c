#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

/*__________________________

	Minhas Bibliotecas
__________________________*/

#include <bool.h>
/* --------------------
	Tipo bool que representa uma variável
	booleana, ou seja, só pode assumir
	TRUE ou FALSE
 --------------------*/
#include <ponto.h>
/* --------------------
	Estrutura abstrata de dados que representa
	um ponto em um espaço tridimensional
	
	ponto[X] = coordenada do ponto no eixo X
	ponto[Y] = coordenada do ponto no eixo Y
	ponto[Z] = coordenada do ponto no eixo Z
 --------------------*/
#include <malha.h>
/* --------------------
	Estrutura abstrata de dados que representa
	um conjunto de triângulos em um
	espaço tridimensional. Teoricamente
	deveria ser um conjunto, pois os vértices
	de um triângulo não possuem ordem. No entanto,
	para facilitar a implementação, utilizaremos um
	vetor, e atribuiremos uma ordem arbitrária (e também
	irrelevante para o algoritmo) aos vértices dos 
	triângulos que compõem a malha.

	exemplos:	
	malha->triangulos[i][0][X] = valor em x para o primeiro vértice do triângulo i
	malha->triangulos[i][0][Y] = valor em y para o primeiro vértice do triângulo i
	malha->triangulos[i][0][Z] = valor em z para o primeiro vértice do triângulo i
	
	malha->triangulos[j][2][X] = valor em x para o terceiro vértice do triângulo j
	malha->triangulos[j][2][Y] = valor em y para o terceiro vértice do triângulo j
	malha->triangulos[j][2][Z] = valor em z para o terceiro vértice do triângulo j

 --------------------*/
#include <caixa.h>
/* --------------------
	Estrutura abstrata de dados que representa
	uma caixa. Como a entrada do trabalho utiliza
	uma caixa representada por 8 vértices, a estrutura
	possui um valor variável para a quantidade de vértices.
	No entanto, eu optei por representar apenas os valores máximos
	e mínimos que a caixa assume nos 3 eixos do espaço, dado que a lógica
	utilizada para repartir a caixa em 8 octantes pode ser aplicada
	apenas com esse conjunto de informações, como veremos no algoritmo.
	Chamaremos essa forma de representar uma caixa de "caixa reduzida"

	caixa[MAX][X] = valor máximo do octante em x
	caixa[MIN][Z] = valor mínimo do octante em z

 --------------------*/

// Função que delimita uma caixa reduzida a partir de uma malha de triângulos
caixa_t *malha_para_caixa_reduzida(malha_t *malha);

// Função que cria uma caixa reduzida a partir
// de uma caixa semelhante à caixa explicada no pdf
caixa_t *caixa_para_caixa_reduzida(caixa_t *caixa);

// Função que escolhe um octante em uma caixa,
// de acordo com a posição de um ponto
void escolher_octante(caixa_t *caixa, ponto_t ponto);

// Função que determina se um objeto está
// contido dentro de uma caixa
bool colisao(malha_t *objeto, caixa_t *caixa, ponto_t colisor, int n);

int main(int argc, char *argv[]) {
	// Primeiro, obteremos todas as informações
	// necessárias para determinar se houve colisão:

	// Caso o programa não receba a caixa delimitadora do objeto,
	// precisaremos implementá-la.
	bool precisa_fazer_caixa;
	scanf("%d%*c", (int *)(&precisa_fazer_caixa));
	// printf("%d\n", (int) precisa_fazer_caixa);

	// Numero de iterações para rodar o algoritmo
	// que reduz a caixa, de acordo com a posição do ponto
	int n_max;
	scanf("%d%*c", &n_max);
	printf("%d\n", n_max);

	// Número de triângulos que compõem o objeto
	int n_triangulos;
	scanf("%d%*c", &n_triangulos);
	printf("%d\n", n_triangulos);

	// Coordenadas do ponto colisor:
	ponto_t* ponto_colisor = ler_pontos(1);
	// print_ponto(*ponto_colisor);

	// Leitura da malha de triangulos que compõem o objeto:
	malha_t *objeto = ler_malha(n_triangulos);
	// print_malha(objeto);

	// Agora que temos as coordenadas do objeto, podemos,
	// ou fazer a caixa, ou ler ela da entrada principal
	caixa_t *caixa;
	if(precisa_fazer_caixa)
		caixa = malha_para_caixa_reduzida(objeto);
	else {
		ponto_t *pontos_caixa_aux = ler_pontos(8);
		caixa_t *caixa_aux = nova_caixa(pontos_caixa_aux, 8);
		
		caixa = caixa_para_caixa_reduzida(caixa_aux);

		// printf("Caixa real\n");
		// print_caixa(caixa_aux);

		free_caixa(caixa_aux);
	}

	// printf("\n\nCaixa fake\n");
	// print_caixa(caixa);

	// Uma vez que temos os dados necessários, executaremos
	// o que detecta se houve colisão ou não.
	if(colisao(objeto, caixa, *ponto_colisor, n_max))
		printf("1 - RODO CERTIN\n");
	else
		printf("0 - FAIO\n");

	free_malha(objeto);
	free_caixa(caixa);
	free_ponto(*ponto_colisor);
	free(ponto_colisor);

	return 0;
}

caixa_t *malha_para_caixa_reduzida(malha_t *m) {
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

			if(m->triangulos[i][j][X] > max_x)
				max_x = m->triangulos[i][j][X];
			if(m->triangulos[i][j][Y] > max_y)
				max_y = m->triangulos[i][j][Y];
			if(m->triangulos[i][j][Z] > max_z)
				max_z = m->triangulos[i][j][Z];
		}
	}

	ponto_t *pontos_caixa = (ponto_t *) malloc(sizeof(ponto_t) * N_PONTOS);

	pontos_caixa[MAX] = (ponto_t) malloc(sizeof(double) * N_EIXOS);
	pontos_caixa[MAX][X] = max_x;
	pontos_caixa[MAX][Y] = max_y;
	pontos_caixa[MAX][Z] = max_z;
	
	pontos_caixa[MIN] = (ponto_t) malloc(sizeof(double) * N_EIXOS);
	pontos_caixa[MIN][X] = min_x;
	pontos_caixa[MIN][Y] = min_y;
	pontos_caixa[MIN][Z] = min_z;

	return nova_caixa(pontos_caixa, N_PONTOS);
}

caixa_t *caixa_para_caixa_reduzida(caixa_t *caixa) {
	// Começamos encontrando os limites da caixa em cada eixo
	double max_x = INT_MIN;
	double max_y = INT_MIN;
	double max_z = INT_MIN;

	double min_x = INT_MAX;
	double min_y = INT_MAX;
	double min_z = INT_MAX;

	for(int i = 0; i < caixa->n_pontos; i++) {
		if(caixa->pontos[i][X] < min_x)
			min_x = caixa->pontos[i][X];
		if(caixa->pontos[i][Y] < min_y)
			min_y = caixa->pontos[i][Y];
		if(caixa->pontos[i][Z] < min_z)
			min_z = caixa->pontos[i][Z];

		if(caixa->pontos[i][X] > max_x)
			max_x = caixa->pontos[i][X];
		if(caixa->pontos[i][Y] > max_y)
			max_y = caixa->pontos[i][Y];
		if(caixa->pontos[i][Z] > max_z)
			max_z = caixa->pontos[i][Z];
	}

	ponto_t *pontos_caixa = (ponto_t *) malloc(sizeof(ponto_t) * N_PONTOS);

	pontos_caixa[MAX] = (ponto_t) malloc(sizeof(double) * N_EIXOS);
	pontos_caixa[MAX][X] = max_x;
	pontos_caixa[MAX][Y] = max_y;
	pontos_caixa[MAX][Z] = max_z;
	
	pontos_caixa[MIN] = (ponto_t) malloc(sizeof(double) * N_EIXOS);
	pontos_caixa[MIN][X] = min_x;
	pontos_caixa[MIN][Y] = min_y;
	pontos_caixa[MIN][Z] = min_z;

	return nova_caixa(pontos_caixa, N_PONTOS);
}

bool colisao(malha_t *objeto, caixa_t *caixa, ponto_t ponto_colisor, int n) {
	// Primeiro, checaremos se o ponto 
	// colisor está nos limites do objeto.
	if(ponto_colisor[X] < caixa->pontos[MIN][X] ||
	   ponto_colisor[Y] < caixa->pontos[MIN][Y] ||
	   ponto_colisor[Z] < caixa->pontos[MIN][Z] ||
	   ponto_colisor[X] > caixa->pontos[MAX][X] ||
	   ponto_colisor[Y] > caixa->pontos[MAX][Y] ||
	   ponto_colisor[Z] > caixa->pontos[MAX][Z]) {
		printf("Ponto fora da caixa inicial!\n");
		return TRUE;
	}

	// Aqui optei por reduzir a caixa ao máximo antes de checar
	// se houve colisão, pois isso torna o algoritmo menos custoso
	// quando analisamos o pior caso.
	for(int i = 0; i < n; i++)
		escolher_octante(caixa, ponto_colisor);

	// Agora, checaremos se o objeto intercepta o octante final.
	for(int i = 0; i < objeto->n_triangulos; i++) {
		for(int j = 0; j < 3; j++) {
			// Primeiro, checaremos os vértices de todos os triangulos
			if(objeto->triangulos[i][j][X] >= caixa->pontos[MIN][X] && objeto->triangulos[i][j][X] >= caixa->pontos[MIN][X] &&
			   objeto->triangulos[i][j][Y] >= caixa->pontos[MIN][Y] && objeto->triangulos[i][j][Y] >= caixa->pontos[MIN][Y] &&
			   objeto->triangulos[i][j][Z] >= caixa->pontos[MIN][Z] && objeto->triangulos[i][j][Z] >= caixa->pontos[MIN][Z]) {
				printf("INTERCEPTOU!\n");
				printf("triangulo %d vertice %d\n", i, j);
				print_ponto(objeto->triangulos[i][j]);
				return TRUE;
			}

		}
	}

	return TRUE;
}

void escolher_octante(caixa_t *caixa, ponto_t ponto) {
	// Substituiremos as coordenadas antigas da caixa com as novas
	// coordenadas encontradas.Isso se deve à escolha de não
	// manter um log de caixas, visto que não tem nenhuma utilidade
	// para esse trabalho. No entanto, imutabilidade de objetos
	// é tido como uma boa prática, uma vez que é possível manter
	// um histórico, e o uso de memória não é tão elevado ( O(n_max) )

	// Como temos garantido que o ponto está
	// dentro da caixa, os ifs ficam bem simples
	double meio = (caixa->pontos[MAX][X] + caixa->pontos[MIN][X]) / 2;
	if(ponto[X] >= meio)
		caixa->pontos[MIN][X] = meio;
	else
		caixa->pontos[MAX][X] = meio;

	meio = (caixa->pontos[MAX][Y] + caixa->pontos[MIN][Y]) / 2;
	if(ponto[Y] >= meio)
		caixa->pontos[MIN][Y] = meio;
	else
		caixa->pontos[MAX][Y] = meio;

	meio = (caixa->pontos[MAX][Z] + caixa->pontos[MIN][Z]) / 2;
	if(ponto[Z] >= meio)
		caixa->pontos[MIN][Z] = meio;
	else
		caixa->pontos[MAX][Z] = meio;

	print_caixa(caixa);
}