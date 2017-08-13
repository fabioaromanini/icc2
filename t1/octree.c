#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include <bool.h>
#include <ponto.h>
#include <objeto.h>

// Função que delimita uma caixa a partir de um objeto
CAIXA *delimitar_caixa(OBJETO *o);

int main(int argc, char *argv[]) {
	// Primeiro, obteremos todas as informações
	// necessárias para determinar se houve colisão:

	// Caso o programa não receba a caixa delimitadora do objeto,
	// precisaremos implementá-la.
	bool precisa_fazer_caixa;
	scanf("%d%*c", (int *)(&precisa_fazer_caixa));

	// Altura limite para percorrer a octree
	int h_max;
	scanf("%d%*c", &h_max);

	// Número de triângulos que compõe o objeto
	int n_triangulos;
	scanf("%d%*c", &n_triangulos);

	// Como cada triângulo é delimitado por 3 pontos
	int n_pontos = 3 * n_triangulos;

	// Coordenadas do ponto colisor
	PONTO* ponto_colisor = ler_pontos(1);

	// Coordenadas de todos os pontos que compõe o objeto
	PONTO *pontos_objeto = ler_pontos(n_pontos);

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
		caixa = cria_objeto(pontos_caixa, 8);
	}


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

	PONTO *coord = (PONTO *) malloc(sizeof(PONTO) * 8);
	// Agora, com as coordenadas limites, estabeleceremos a caixa da seguinte maneira:

/*
	PS: Só esse desenho já vale uns pontinhos

		 | z 	  / -z
		 |	 	 /
		 |	    /
		2|_____/____1
	    /	  	    |
	   / |         /|
	  /	    	  / |
   3 /___|_______/0 |
	|	   	    |   |
-y__|_ _ | _ _ _|_ _|________________ y
	|    6      |   /5
	|  / |  	|  / 
	|     	    | /  
	|/___|______|/
    /7	 |        4
   /	 |
  / 	 |
 / x 	 | -z

*/

	coord->x = max_x;
	coord->y = max_y;
	coord->z = max_z;

	(coord + 1)->x = min_x;
	(coord + 1)->y = max_y;
	(coord + 1)->z = max_z;

	(coord + 2)->x = min_x;
	(coord + 2)->y = min_y;
	(coord + 2)->z = max_z;

	(coord + 3)->x = max_x;
	(coord + 3)->y = min_y;
	(coord + 3)->z = max_z;

	(coord + 4)->x = max_x;
	(coord + 4)->y = max_y;
	(coord + 4)->z = min_z;
	
	(coord + 5)->x = min_x;
	(coord + 5)->y = max_y;
	(coord + 5)->z = min_z;
	
	(coord + 6)->x = min_x;
	(coord + 6)->y = min_y;
	(coord + 6)->z = min_z;

	(coord + 7)->x = max_x;
	(coord + 7)->y = min_y;
	(coord + 7)->z = min_z;

	CAIXA *resp = (CAIXA *) malloc(sizeof(CAIXA));

	resp->coordenadas = coord;
	resp->n_coordenadas = 8;
	return resp;
}