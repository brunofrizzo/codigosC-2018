#include <stdio.h>
#include <stdlib.h>

struct ponto {
	int x;
	struct ponto *proximo;
};

struct l_descr {
	struct ponto *inicio;
	struct ponto *fim;
	int cont;
};

void inicializa_lista(struct l_descr *lista) {
	lista->fim = NULL;
	lista->inicio = NULL;
	lista->cont = 0;
}

void imprime_lista(struct l_descr *lista) {
	struct ponto *aux = lista->inicio;

	while(aux !=  NULL) {
		printf("a = %d\n", aux->x);
		aux = aux->proximo;
	}
}

void insere_fim_lista(struct l_descr *lista, int valor) {
	struct ponto *aux;

	if (lista->inicio == NULL) {

		lista->inicio = malloc(sizeof(struct ponto));
		aux = lista->inicio;
		aux->x = valor;
		aux->proximo = NULL;
		lista->cont++;
		lista->fim = lista->inicio;

	} else {

		aux = lista->fim;		
		aux->proximo = malloc(sizeof(struct ponto));
		aux = aux->proximo;
		aux->x = valor;
		aux->proximo = NULL;
		lista->fim = aux;
		lista->cont++;
	}	

}

int localiza_valor(struct l_descr *lista, int valor) {
	struct ponto *aux = lista->inicio;
	int cont=0;

	while (aux != NULL) {
		if (aux->x != valor) {
			aux = aux->proximo;
			cont++;
		} else{
			return cont;
		}
	}

	return -1;

	
}

int conta_elementos(struct l_descr *lista) {
	struct ponto *aux = lista->inicio;
	int cont=0;

	while (aux != NULL) {
		aux = aux->proximo;
		cont++;
	}

	return cont;

	
}

int main() {
	//	struct ponto a;
	struct l_descr lista1;	

	inicializa_lista(&lista1);

	// a.x = 10;
	// a.proximo = malloc(sizeof(struct ponto));
	// a.proximo->x = 20;
	// a.proximo->proximo = malloc(sizeof(struct ponto));
	// a.proximo->proximo->x = 30;
	// a.proximo->proximo->proximo = NULL;


	// printf("ponto a0 = %d    |    a1 = %d    |     a3 = %d\n", a.x, a.proximo->x, a.proximo->proximo->x);

	// while(aux !=  NULL) {
	// 	printf("a = %d\n", aux->x);
	// 	aux = aux->proximo;
	// }

	insere_fim_lista(&lista1, 40);
	insere_fim_lista(&lista1, 50);
	insere_fim_lista(&lista1, 60);
	insere_fim_lista(&lista1, 70);

	imprime_lista(&lista1);

	printf("Posicao do valor 40: %d\n", localiza_valor(&lista1, 40));
	printf("Numero de elementos: %d\n", conta_elementos(&lista1));
}