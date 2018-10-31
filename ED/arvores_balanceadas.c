#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

struct no {
	int valor;
	int altura;
	struct no *esq;
	struct no *dir;
}; 

typedef struct no arvore;

bool esta_vazia(arvore *a) {
	return a==NULL;
}

void imprime(arvore *a) {
	if (!esta_vazia(a)) {
		printf("valor = %d\n", a->valor);
		imprime(a->esq);
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

//funcao recursiva
int calcula_altura(arvore *a) {
	if (!esta_vazia(a)) {
		if (calcula_altura(a->dir) > calcula_altura(a->esq)) {
			return calcula_altura(a->dir)+1;
		}else{
			return calcula_altura(a->esq)+1;
		}
	}else{
		return -1;
	}
}

int alt_no(arvore *a) {
	if (a == NULL) {
		return -1;
	}else{
		return a->altura;
	}
}

int maior(int a, int b) {
	if (a>b) 
		return a;
	else
		return b;
}

int calcula_altura_sem_recursao(arvore *a) {
	return maior(alt_no(a->esq), alt_no(a->dir))+1;
}

int calcula_fb(arvore *a){
	return alt_no(a->esq) - alt_no(a->dir);
}

void rotacao_ll(arvore **a) {
	arvore *b;
	b = (*a)->esq;
	(*a)->esq = b->dir;
	b->dir = (*a);
	(*a)->altura = calcula_altura(*a);
	b->altura = calcula_altura(b);
	(*a) = b;
} 

void rotacao_rr(arvore **a) {
	arvore *b;
	b = (*a)->dir;
	(*a)->dir = b->esq;
	b->esq = (*a);
	(*a)->altura = calcula_altura(*a);
	b->altura = calcula_altura(b);
	(*a) = b;
}

void rotacao_lr(arvore **a){
	rotacao_rr(&((*a)->esq));
	rotacao_ll(a);
}

void rotacao_rl(arvore **a) {
	rotacao_ll(&((*a)->dir));
	rotacao_rr(a);
}

void rebalanceia(arvore **a) {
	int fb = calcula_fb(*a);

	if (fb>=2) { //esquerda desbalanceada
		if (calcula_fb((*a)->esq) > 0) {
			rotacao_ll(a);
		}else{
			rotacao_lr(a);
		}
	}else if (fb<=-2){
		if (calcula_fb((*a)->dir) < 0) {
			rotacao_rr(a);
		}else{
			rotacao_rl(a);
		}
	}
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
	a->altura = calcula_altura(a);
	rebalanceia(&a);
	return a;
}

arvore *remove_elemento(int val, arvore *a) {
	if (esta_vazia(a)) {
		return NULL;
	}else{
		if (val < a->valor) {
			a->esq = remove_elemento(val, a->esq);
		}else if (val > a->valor) {
			a->dir = remove_elemento(val, a->dir);
		}else{
			if (esta_vazia(a->esq) && esta_vazia(a->dir)) {
				free(a);
				a = NULL;
			} else if(esta_vazia(a->dir)) {
				arvore *aux = a;
				a = a->esq;
				free(aux);
			}else if(esta_vazia(a->esq)) {
				arvore *aux = a;
				a = a->dir;
				free(aux);
			}else{
				arvore *aux = a->esq;
				while (aux->dir != NULL) {
					aux = aux->dir;
				}
				a->valor = aux->valor;
				aux->valor = val;
				a->esq = remove_elemento(val, a->esq);
			}
		}
		a->altura = calcula_altura(a);
		return a;		
	}
}

arvore *desaloca(arvore *a) {
	if (a != NULL){
		desaloca(a->esq);
		desaloca(a->dir);
		free(a);
	}
	return NULL;	
}

int main() {
	arvore *a = cria_vazia();

	a = insere_ordenado(10, a);
	a = insere_ordenado(5, a);
	a = insere_ordenado(40, a);
	a = insere_ordenado(45, a);
	a = insere_ordenado(50, a);
	a = insere_ordenado(70, a);
	// a = remove_ elemento(40, a);

	imprime(a);

	printf("altura = %d\n", calcula_altura(a));
}