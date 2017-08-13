#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include <bool.h>

typedef struct {
	double x;
	double y;
	double z;
} PONTO;

typedef struct {
	PONTO *coordenadas;
	int n_coordenadas;
} OBJETO, CAIXA;

OBJETO *cria_objeto(PONTO *coordenadas, int n_coordenadas) {
	OBJETO *novo = (OBJETO *) malloc(sizeof(OBJETO));
	novo->coordenadas = coordenadas;
	novo->n_coordenadas = n_coordenadas;
	return novo;
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

// Só esse desenho já vale uns pontinhos


						   /*
				 | z 	  / -z
				 |	 	 /
				 |	    /
				2|_____/____1
			    / 	  	    |
			   /           /|
			  /	    	  / |
		   3 /___________/0 |
			|	   	    |   |
-y__________|	   	    |   |________________ y
			|           |   /6
			|	    	|  / 
			|      	    | /  
			|___________|/
		   /8	|        5
		  /		|
		 / 		|
		/ x 	| -z
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

void free_objeto(OBJETO *o) {
	free(o->coordenadas);
	free(o);
}

int main(int argc, char *argv[]) {
	// Primeiro, obtemos todas as informações
	// necessárias para mapear o objeto, o ponto
	// colisor, e a caixa delimitadora.
	bool precisa_fazer_caixa;
	scanf("%d%*c", (int *)(&precisa_fazer_caixa));

	// Altura limite para percorrer a octree
	int h_max;
	scanf("%d%*c", &h_max);

	// Número de triângulos que compões o objeto
	int n_triangulos;
	scanf("%d%*c", &n_triangulos);

	// Como cada triângulo é delimitado por 3 pontos
	int n_pontos = 3 * n_triangulos;

	// Coordenadas do ponto colisor
	PONTO ponto_colisor;
	scanf("%lf%*c%lf%*c%lf%*c", &(ponto_colisor.x), &(ponto_colisor.y), &(ponto_colisor.z));

	// Coordenadas de todos os pontos que compõe o objeto
	PONTO *pontos_objeto = (PONTO *) malloc(sizeof(PONTO) * n_pontos);
	for(int i = 0; i < n_pontos; i++)
		scanf("%lf%*c%lf%*c%lf%*c", &(pontos_objeto+i)->x, &(pontos_objeto+i)->y,&(pontos_objeto+i)->z);

	// Encapsularemos o vetor de coordenadas e
	// seu tamanho em uma struct para facilitar
	// a iteração sobre o conjunto de dados
	OBJETO *objeto = cria_objeto(pontos_objeto, n_pontos);

	CAIXA *caixa;
	if(precisa_fazer_caixa)
		caixa = delimitar_caixa(objeto);
	else {
		PONTO *pontos_caixa;

		for(int i = 0; i < 8; i++)
			scanf("%lf%*c%lf%*c%lf%*c",&(pontos_caixa + i)->x,&(pontos_caixa + i)->y,&(pontos_caixa + i)->z);

		caixa = cria_objeto(pontos_caixa, 8);
	}

	free_objeto(objeto);
	free_objeto(caixa);
	return 0;
}