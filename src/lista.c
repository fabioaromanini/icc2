#include <lista.h>

Lista *lista() {
	Lista *novo = (Lista *) malloc(sizeof(Lista));
	novo->comeco = NULL;
	novo->tam = 0;

	return novo;
}

void listaAdd(Lista *lista, int valor, int peso) {
	
	// Cria o novo elemento
	No *novo = (No *) malloc(sizeof(No));
	novo->prox = NULL;
	novo->valor = valor;
	novo->peso = peso;

	if(lista->comeco == NULL) {
		lista->comeco = novo;
	} else {
		No *aux = lista->comeco;
		
		while(aux->prox) aux = aux->prox;

		aux->prox = novo;
	}

	(lista->tam)++;
}

void listaAddCab(Lista *lista, int valor, int peso) {
	No *novo = (No *) malloc(sizeof(No));
	novo->valor = valor;
	novo->peso = peso;

	lista->tam++;
	novo->prox = lista->comeco;
	lista->comeco = novo;
	
}

void listaAddOrd(Lista *lista, int valor, int peso) {
	
	// Cria o novo elemento
	No *novo = (No *) malloc(sizeof(No));
	novo->prox = NULL;
	novo->valor = valor;
	novo->peso = peso;

	if(lista->comeco == NULL) {
		lista->comeco = novo;
		return;
	}

	lista->tam++;
	No *aux = lista->comeco;

	if(aux->valor > valor) {
		novo->prox = aux;
		lista->comeco = novo;
	} else if(aux->prox == NULL) {
		aux->prox = novo;
	} else {
		while(aux->prox && aux->prox->valor <= valor)
			aux = aux->prox;

		if(lista->comeco == aux) {
			lista->comeco = novo;
			novo->prox = aux;
		} else if(aux->prox == NULL) {
			aux->prox = novo;
		} else {
			novo->prox = aux->prox;
			aux->prox = novo;
		}
	}
}

No *listaSrc(Lista *lista, int valor) {
	No *aux = lista->comeco;
	while(aux) {
		if(aux->valor == valor) return aux;
		aux = aux->prox;
	}

	return NULL;
}

void listaRm(Lista *lista, int valor) {
	No *aux = lista->comeco;

	if(aux == NULL) return;

	if(aux->valor == valor) {
		if(aux->prox == NULL) {
			lista->comeco = NULL;
		} 
		else 
			lista->comeco = aux->prox;
		
		free(aux);
		(lista->tam)--;
	} else {
		No *prox = aux->prox;
		while(prox) {
			if(prox->valor == valor) {
				aux->prox = prox->prox;
				free(prox);
				(lista->tam)--;
				break;
			}

			aux = prox;
			prox = prox->prox;
		}

	}
}

void listaPrint(Lista *lista) {
	No *aux = lista->comeco;

	while(aux) {
		printf(" %d", aux->valor);
		aux = aux->prox;
	}

	printf("\n");
}

void listaPrintPeso(Lista *lista) {
	No *aux = lista->comeco;

	while(aux) {
		printf("Valor: %d\tPeso: %d\n", aux->valor, aux->peso);
		aux = aux->prox;
	}
}

void listaFree(Lista *lista) {
	if(lista) {
		No *aux = lista->comeco;
		
		while(aux != NULL) {
			No *aux2 = aux->prox;
			free(aux);
			aux = aux2;
		}

		free(lista);
	}
}

void listaSort(Lista *lista) {
	int *elementos = (int *) malloc(sizeof(int) * lista->tam);
	int *pesos = (int *) malloc(sizeof(int) * lista->tam);


	No *aux = lista->comeco;
	int pos = 0;
	while(aux) {
		elementos[pos] = aux->valor;
		pesos[pos] = aux->peso;
		pos++;
		aux = aux->prox;
	}


	for(int i = 1; i < lista->tam; i++) {
		int j = i - 1;

		while(j >= 0 && elementos[j] > elementos[i]) {
			int aux = elementos[j];
			elementos[j] = elementos[i];
			elementos[i] = aux;

			aux = pesos[j];
			pesos[j] = pesos[i];
			pesos[i] = aux;
			j--;
			i--;
		}
	}

	aux = lista->comeco;
	for(int i = 0; i < lista->tam; i++) {
		aux->valor = elementos[i];
		aux->peso = pesos[i];
		aux = aux->prox;
	}

	free(pesos);
	free(elementos);
}