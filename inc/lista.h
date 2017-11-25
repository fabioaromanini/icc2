#ifndef _LISTA_H_
#define _LISTA_H_

#include <stdlib.h>
#include <stdio.h>

#define vazio -1

typedef struct No {
	int valor;
	int peso;
	struct No *prox;
} No;

typedef struct {
	No *comeco;
	int tam;
} Lista;

// Cria uma lista nova de tamanho 0
Lista *lista();
// Adiciona um nó ao fim da lista
void listaAdd(Lista *, int valor, int peso);
// Adiciona elemento no começo da lista
void listaAddCab(Lista *, int valor, int peso);
// Adiciona um elemento de maneira a manter os elementos ordenados
void listaAddOrd(Lista *, int valor, int peso);
// Procura um determinado elemento na lista, e retorna o nó que o contém
// Retorna NULL caso o elemento não esteja na lista
No *listaSrc(Lista *, int valor);
// Remove um nó da lista
void listaRm(Lista *, int valor);
// Imprime todos os elementos da lista
void listaPrint(Lista *);
// Imprime os valores e pesos dos elementos da lista
void listaPrintPeso(Lista *);
// Libera o espaço alocado para uma lista
void listaFree(Lista *);

// Faz umas gambiarras, mas organiza a lista
void listaSort(Lista *);
#endif

/*
	TESTES!
#include <lista.h>

int main(int argc, char *argv[]) {
	int n;
	// scanf("%d", &n);
	n = 10;
	Lista *teste = lista();

	for(int i = n; i > 0; i--) {
		listaAdd(teste, i, n - i + 1);
	}
	listaAdd(teste, n + 1, 0);
	listaAdd(teste, 0, n + 1);

	No *aux = teste->comeco;

	while(aux) {
		printf("Valor: %d\tPeso: %d\n", aux->valor, aux->peso);
		aux = aux->prox;
	}

	printf("Tam: %d\n", teste->tam);

	aux = listaSrc(teste, n / 2);
	if(aux)
		printf("O valor %d esta na lista\n", n / 2);
	
	aux = listaSrc(teste, 2 * n);
	if(aux)
		printf("O valor %d esta na lista\n", 2 * n);
	else
		printf("O valor %d n esta na lista\n", 2 * n);

	aux = teste->comeco;

	listaRm(teste, 11);
	printf("Valor do primeiro apos remover 11(10):%d \n", teste->comeco->valor);
	printf("Apagando o 9\n");
	listaRm(teste, 9);
	printf("Apagando o 7\n");
	listaRm(teste, 7);

	printf("Apagando o 2\n");
	listaRm(teste, 2);
	printf("Apagando o 1\n");
	listaRm(teste, 1);
	printf("Apagando o 0\n");
	listaRm(teste, 0);
	printf("Ok\n");
	aux = teste->comeco;

	while(aux) {
		printf("Valor: %d\tPeso: %d\n", aux->valor, aux->peso);
		aux = aux->prox;
	}

	listaFree(teste);

	printf("Lista ordenada:\n");
	teste = lista();

	int trap = (n - 1)/ 2;
	for(int i = n; i > 0; i--) {
		if(i != trap) {
			printf("Adicionou o %d\n", i);
			listaAddOrd(teste, i, n - i + 1);
			listaPrint(teste);
		}
	}

	printf("Adicionou o %d\n", trap);
	listaAddOrd(teste, trap, n - n/2);
	listaPrint(teste);
	
	printf("Adicionou o %d\n", n + 1);
	listaAddOrd(teste, n + 1, 0);
	listaPrint(teste);
	printf("Adicionou o %d\n", 0);
	listaAddOrd(teste, 0, n + 1);
	listaPrint(teste);
	
	listaFree(teste);


	printf("Teste do SORT!\n");
	teste = lista();

	printf("Adicionou o %d\n", 5);
	listaAddCab(teste, 5, vazio);
	printf("Adicionou o %d\n", 1);
	listaAddCab(teste, 1, vazio);
	printf("Adicionou o %d\n", 3);
	listaAddCab(teste, 3, vazio);
	printf("Adicionou o %d\n", 10);
	listaAddCab(teste, 10, vazio);
	printf("Adicionou o %d\n", 8);
	listaAddCab(teste, 8, vazio);

	listaPrint(teste);
	printf("Organizando...\n");
	listaSort(teste);
	printf("Organizado!\n");
	listaPrint(teste);

	listaFree(teste);

	return 0;
}
*/