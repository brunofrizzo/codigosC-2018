#include <stdio.h>
#include <stdlib.h>

struct no {
	int val;
	struct no *proximo;
};

struct lista{
	struct no *inicio;
	int cont;
	struct no *fim;
};

void inicializa(struct lista *l) {
	l->inicio = NULL;
	l->cont = 0;
	l->fim = NULL;
}

void insere_vazia(struct lista *lista, int val) {
	lista->inicio = malloc(sizeof(struct no));
    lista->inicio->val = val;
    lista->inicio->proximo = NULL;
    lista->cont++;
    lista->fim = lista->inicio;
}

void insere_inicio(struct lista *lista, int val) {
    if (lista->inicio == NULL) {
        insere_vazia(lista, val);
    }else{
        struct no *aux = malloc(sizeof(struct no));
        aux->val = val;
        aux->proximo = lista->inicio;
        lista->inicio = aux;
        lista->cont++;
    }
}

int retorna_k_maior(struct lista *l, int k) {
	int i, maior=0, maior_lista;
	struct no *aux;

	if (k == 0 || l->cont==0) {
		return 0;
	} 
	if (k > l->cont) {
		k = l->cont;
	}

	for (i=0;i<k;i++) {
		aux = l->inicio;
		maior_lista = 0;
		while (aux!=NULL){
			if (aux->val > maior_lista) {
				if (maior != 0) { 
					if (aux->val < maior) {
						maior_lista = aux->val;
					}
				} else{
					maior_lista = aux->val;	
				}
			}
			aux = aux->proximo;
		}

		if (maior_lista!=0)
			maior = maior_lista;

	}
	return maior;
}

int main () {

	struct lista l;
	inicializa(&l);

	insere_inicio(&l, 7);
	insere_inicio(&l, 20);
	insere_inicio(&l, 13);
	insere_inicio(&l, 24);
	insere_inicio(&l, 4);
	insere_inicio(&l, 4);
	
	printf("->%d\n", retorna_k_maior(&l, 2));

}