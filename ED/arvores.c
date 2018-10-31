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

arvore *desaloca(arvore *a) {
	if (a != NULL){
		desaloca(a->esq);
		desaloca(a->dir);
		free(a);
	}
	return NULL;	
}

int existe_valor(int valor, arvore *a) {
	if (!esta_vazia(a)) {
		if (a->valor == valor) {
			return 1;
		}
		if (existe_valor(valor, a->esq)) {
			return 1;
		}
		return existe_valor(valor, a->dir);
	}
	return 0;
}

int existe_valor2(int valor, arvore *a) {
	if (esta_vazia(a)) {
		return 0;
	}else{
		return valor==a->valor||existe_valor2(valor, a->esq)||existe_valor2(valor, a->dir);
	}
}

int conta_folhas(arvore *a) {
	if (esta_vazia(a) == 0){
		return 1+conta_folhas(a->esq)+conta_folhas(a->dir);
	}else{
		return 0;
	}
}

int sao_iguais(arvore *a, arvore *b) {
	return ((esta_vazia(a) && esta_vazia(b)) || (!esta_vazia(a) && !esta_vazia(b) && a->valor == b->valor && sao_iguais(a->esq, b->esq) && sao_iguais(a->dir, b->dir)));
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

int main() {
	arvore *raiz = cria_arvore(30, cria_vazia(), cria_vazia());
	raiz->esq = cria_arvore(9, 
					cria_arvore(4, cria_vazia(), cria_vazia()),
					cria_arvore(15, cria_vazia(), cria_vazia())
					);
	raiz->dir = cria_arvore(40,
					cria_arvore(31, cria_vazia(), cria_vazia()),
					cria_vazia()
					);
	// raiz = insere_ordenado(3, raiz);

	arvore *raizb = cria_arvore(30, cria_vazia(), cria_vazia());
	raizb->esq = cria_arvore(9, 
					cria_arvore(4, cria_vazia(), cria_vazia()),
					cria_arvore(15, cria_vazia(), cria_vazia())
					);
	raizb->dir = cria_arvore(40,
					cria_arvore(31, cria_vazia(), cria_vazia()),
					cria_vazia()
					);

	imprime(raiz);
	// raiz = desaloca(raiz);
	// imprime(raiz);
	// printf("existe = %d\n", existe_valor2(7, raiz));
	printf("quantidade de nos = %d\n", conta_folhas(raiz));
	printf("iguais = %d\n", sao_iguais(raiz, raizb));


}
