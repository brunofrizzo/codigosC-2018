#include <stdio.h>
#include <stdlib.h>

struct no {
	int valor;
	struct no *esq;
	struct no *dir;
}; 

typedef struct no arvore;

int esta_vazia(arvore *a) {
	return a==NULL;
}

void imprime(arvore *a) {
	if (!esta_vazia(a)) {
		imprime(a->esq);
		printf("valor = %d\n", a->valor);
		imprime(a->dir);
	}
}

arvore *cria_vazia() {
	return NULL;
}

arvore *cria_arvore(int valor, arvore *sae, arvore *sad) {
	arvore *a = malloc(sizeof(arvore));
	a->valor = valor;
	a->esq = sae;
	a->dir = sad;
	return a;
}

arvore *insere_ordenado(int valor, arvore *a) {
	if (esta_vazia(a) == 1) {
		a = cria_arvore(valor, cria_vazia(), cria_vazia());
	}else{
		if (valor < a->valor) {
			a->esq = insere_ordenado(valor, a->esq);
		} else {
			a->dir = insere_ordenado(valor, a->dir);
		}	
	}
	return a;
}

// arvore *busca_elemento(int valor, arvore *a) {
// 	if (esta_vazia(a) == 1) {
// 		return NULL;
// 	}else if(valor < a->valor) {
// 		a = busca_elemento(valor, a->esq);
// 	}else if(valor > a->valor){
// 		a = busca_elemento(valor, a->dir);
// 	}
// 	return a;
// }

arvore *procura_maior_valor(arvore *a) {
	while (esta_vazia(a->dir) == 0) {
		a = a->dir;
	}
	return a;
}

// arvore *remove_elemento(int valor, arvore *a) {
// 	if (esta_vazia(a) == 1) {
// 		return NULL;
// 	}else{
// 		if (valor < a->valor) {
// 			remove_elemento(valor, a->esq);
// 		}else if (valor > a->valor) {
			
// 		}


// 		// arvore *aux = busca_elemento(valor, a);
// 		// if (esta_vazia(aux->esq) == 0 && esta_vazia(aux->dir) == 0) {
// 		// 	printf("1\n");
// 		// 	arvore *maior_no = procura_maior_valor(a->esq);
// 		// 	a->valor = maior_no->valor;
// 		// 	remove_elemento(maior_no->valor, maior_no);
// 		// }else if(esta_vazia(aux->esq) == 1 && esta_vazia(aux->dir) == 0){
// 		// 	printf("2\n");
// 		// 	a->valor = aux->dir->valor;
// 		// 	remove_elemento(aux->dir->valor, aux->dir);
// 		// }else if(esta_vazia(aux->esq) == 0 && esta_vazia(aux->dir) == 1){
// 		// 	printf("3\n");
// 		// 	a->valor = aux->esq->valor;
// 		// 	remove_elemento(aux->esq->valor, aux->dir);
// 		// }else{
// 		// 	printf("4\n");
// 		// 	free(aux);
// 		// }
// 	}
// }

int main() {
	arvore *arvore;

	arvore = insere_ordenado(10, arvore);
	arvore = insere_ordenado(2, arvore);
	arvore = insere_ordenado(7, arvore);
	arvore = insere_ordenado(18, arvore);

	imprime(arvore);

	remove_elemento(7, arvore);

	imprime(arvore);
	
}