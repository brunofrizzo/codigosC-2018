#include <stdio.h>
#include <stdlib.h>

struct l_descr{
	struct no *inicio;
	int cont;
	struct no *fim;
};

struct l_descr_circular{
	struct no *inicio;
	int cont;
};

typedef struct l_descr_circular descr_circular;

struct no{
	int valor;
	struct no *proximo;
	struct no *anterior;
};

void inicializa_lista(struct l_descr *lista) {
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->cont = 0;
}

int esta_vazia(struct l_descr *lista) {
    if (lista->inicio == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void imprime_lista(struct l_descr *lista) {
	struct no *aux = lista->inicio;
    while(aux !=  NULL) {
        printf("->%d\n", aux->valor);
        aux = aux->proximo;
    }	
}

int sao_iguais(struct l_descr *lista1, struct l_descr *lista2) {
	int cont=0;
	if (lista1->cont != lista2->cont) {
		return 0;
	} else {
		if (esta_vazia(lista1) == 1 && esta_vazia(lista2) == 1) {
			return 1;
		} else if (esta_vazia(lista1) != esta_vazia(lista2)){
			return 0;
		}else{
			if (lista1->inicio->valor != lista2->inicio->valor) {
				return 0;
			}else if(lista1->fim->valor != lista2->fim->valor) {
				return 0;
			} else {
				struct no *aux = lista1->inicio;
				struct no *aux2 = lista2->inicio;
				while(aux != NULL && aux2 != NULL) {
					if (aux->valor == aux2->valor) {
						aux = aux->proximo;
						aux2 = aux2->proximo;
						cont++;
					} else{
						break;
					}
				}

				if (cont == lista1->cont) {
					return 1;
				}else{
					return 0;
				}
			}

		}
		
	}
}

void insere_inicio(struct l_descr *lista, int val) {
    if (esta_vazia(lista) == 1) {
        lista->inicio = malloc(sizeof(struct no));
        lista->inicio->valor = val;
        lista->inicio->proximo = NULL;
        lista->inicio->anterior = NULL;
        lista->cont++;
        lista->fim = lista->inicio;
    }else{
        struct no *aux = malloc(sizeof(struct no));
        aux->valor = val;
        aux->proximo = lista->inicio;
        aux->anterior = NULL;
        lista->inicio->anterior = aux;
        lista->inicio = aux;
        lista->cont++;
    }
}

void insere_ordenado(struct l_descr *lista, int val){
	struct no *novo = malloc(sizeof(struct no));
	if(lista->inicio->valor >= val){
		novo->proximo = lista->inicio;
		novo->valor = val;
		lista->inicio->anterior = novo;
		lista->inicio = novo;
		lista->cont++;
		novo->anterior = NULL;
	}else if(lista->fim->valor < val){
		novo->valor = val;
		novo->proximo = NULL;
		novo->anterior = lista->fim;
		lista->fim->proximo = novo;
		lista->fim = novo;
		lista->cont++;
	}else{
		struct no *aux = lista->inicio;
		struct no *novo = malloc(sizeof(struct no));
		while(aux->valor < val){
	  		aux = aux->proximo;
		}
		novo->valor = val;
		novo->anterior = aux->anterior;
		aux->anterior->proximo = novo;
		novo->proximo = aux;
		aux->anterior = novo;
		lista->cont++;
	}
}

int remove_valor(struct l_descr *lista, int val){
	if(lista->inicio == NULL){
		return 0;
	}

	if(lista->cont != 1){
		if(lista->inicio->valor == val){
			lista->inicio = lista->inicio->proximo;
			free(lista->inicio->anterior);
		  	lista->inicio->anterior = NULL;
			lista->cont--;
			return 1;
		}else if(lista->fim->valor == val){
		 	lista->fim = lista->fim->anterior;
		 	free(lista->fim->proximo);
		 	lista->fim->proximo = NULL;
		 	lista->cont--;
		  	return 1;
		}else{
			struct no *aux = lista->inicio;

			while(aux->valor != val){
			    if(aux->proximo == NULL){
			      return 0;
			  	}
			    aux = aux->proximo;
			}
			aux->anterior->proximo = aux->proximo;
			aux->proximo->anterior = aux->anterior;
			free(aux);
			lista->cont--;
			return 1;
		}
	}else{
		if(lista->inicio->valor == val){
		  	free(lista->inicio);
		  	lista->inicio =  NULL;
		  	lista->fim = NULL;
		  	lista->cont = 0;
		  	return 1;
		}
	}
}

void copiar(struct l_descr *lista1, struct l_descr *lista2) {
	struct no *aux = lista1->inicio;
	struct no *aux2 = malloc(sizeof(struct no));

	if (aux != NULL) {
		lista2->inicio = aux2;
		lista2->fim = aux2;
		lista2->cont++;
	}

	while(aux != NULL) {
		if (lista1->cont == 1){
			aux2->valor = aux->valor;
			aux2->proximo = NULL;
			aux2->anterior = NULL;
		} else {
			if (aux->proximo == NULL) {
				aux2->valor = aux->valor;
				lista2->fim = aux2;
				aux2->proximo = NULL;
				lista2->cont++;
				aux = aux->proximo;
			} else{
				aux2->valor = aux->valor;
				aux2->proximo = malloc(sizeof(struct no));
				aux2->proximo->anterior = aux2;
				aux2 = aux2->proximo;
				aux = aux->proximo;
				lista2->cont++;
			}
		}
	}
}

int valor_na_lista(struct l_descr *lista, int val) {
	struct no *aux = lista->inicio;

	if (lista->inicio != NULL) {
		while(aux != NULL) {
			if (aux->valor == val)
				return 1;
			aux = aux->proximo;
		}	
	}
	
	return 0;
}

void diferenca_ordenada(struct l_descr *l, struct l_descr *lista1, struct l_descr *lista2) {
	struct no *aux = lista1->inicio;
	struct no *aux2 = lista2->inicio;

	if (esta_vazia(lista2) == 1) {
			copiar(lista1, l);
	}else {
		while (aux != NULL && aux2 != NULL) {
			if (aux->valor < aux2->valor) {				
				if (l->inicio == NULL) {					
					insere_inicio(l, aux->valor);
					aux = aux->proximo;
				}else{
					if (valor_na_lista(l, aux->valor) == 0){
						insere_ordenado(l, aux->valor);
					}
					aux = aux->proximo;
				}
			}else if (aux->valor == aux2->valor){
				aux = aux->proximo;
			} else {
				if (aux2->proximo == NULL) {
					if (valor_na_lista(l, aux->valor) == 0){
						insere_ordenado(l, aux->valor);
					}
				}
				aux2 = aux2->proximo;
			}
		}
	}
}

void diferenca(struct l_descr *l, struct l_descr *lista1, struct l_descr *lista2) {
	struct no *aux = lista1->inicio;
	struct no *aux2 = lista2->inicio;

	if (esta_vazia(lista2) == 1) {
			copiar(lista1, l);
			printf("Lista vazia\n");
	}else {
		while (aux != NULL) {
			if (valor_na_lista(lista2, aux->valor) == 0) {
				insere_inicio(l, aux->valor);
			}
			aux = aux->proximo;
		}
	}
}

int comuns(struct l_descr *lista1, struct l_descr *lista2) {
	struct no *aux = lista1->inicio;
	struct no *aux2 = lista2->inicio;
	struct l_descr l;
	inicializa_lista(&l);

	if (esta_vazia(lista2) == 1 || esta_vazia(lista1) == 1) {
			return 0;
	}else {
		while (aux != NULL) {
			if (valor_na_lista(lista2, aux->valor) == 1 && valor_na_lista(&l, aux->valor) == 0){
				insere_inicio(&l, aux->valor);
			}
			aux = aux->proximo;
		}
	}
	return l.cont;
}

void destroi(struct l_descr *l){
	struct no *aux = l->inicio;
	struct no *aux2;

	while(aux != NULL){
		aux2 = aux;
		aux = aux->proximo;
		free(aux2);
	}

	l->inicio = NULL;
	l->cont = 0;
	l->fim = NULL;
}

int eh_inversa(struct l_descr *lista1, struct l_descr *lista2) {
	if (lista1->cont > lista2->cont) {
		return -2;
	} else if (lista1->cont < lista2->cont) {
		return -1;
	} else {
		struct no *aux = lista1->inicio;
		struct no *aux2 = lista2->fim;

		while(aux != NULL) {		
			if (aux->valor != aux2->valor) {
				return 0;
			}
			aux = aux->proximo;
			aux2 = aux2->anterior;
		}
		return 1;
		
	}
}

int remove_primeiro(struct l_descr *lista) {
    if (esta_vazia(lista) == 1) {
        return -1;
    } else {
        struct no *aux = lista->inicio;
        int val;
        val = aux->valor;
        lista->inicio = aux->proximo;
        lista->inicio->anterior = NULL;
        lista->cont--;
        free(aux);
        return val;
    }
}

int remove_ultimo(struct l_descr *lista) {
    struct no *aux;
    aux = lista->inicio;
    int val;

    if (esta_vazia(lista) == 1) {
        return -1;
    } else {
        while(lista->inicio->proximo->proximo != NULL) {
            lista->inicio = lista->inicio->proximo;
        }
        val = lista->fim->valor;
        free(lista->fim);
        lista->inicio->proximo = NULL;
        lista->inicio = aux;
        lista->cont--;
        return val;
    }
}

int remove_indice(struct l_descr *lista, int indice) {
    int i=0, val;
    struct no *aux = lista->inicio;
    struct no *no_anterior = malloc(sizeof(struct no));

    if (esta_vazia(lista)==1) {
        val = -1;
    } else {
        if (indice == 1) {
            val = aux->valor;
            remove_primeiro(lista);
        } else if (indice == lista->cont) {
            remove_ultimo(lista);
            val = lista->fim->valor;
        } else {
            for (i=0; i<indice-1; i++) {
                no_anterior = aux;
                aux = aux->proximo;
            }
            val = aux->valor;
            no_anterior->proximo = aux->proximo;
            aux->proximo->anterior = no_anterior;
            free(aux);
            lista->cont--;
        }
    }
    return val;
}

void remover_nos_impares(struct l_descr *l) {
	int cont=0, cont2=0;
	struct no *aux = l->inicio;

	while(aux != NULL) {
		aux = aux->proximo;
		cont++;
		if (cont%2 != 0) {
			remove_indice(l, cont-cont2);
			cont2++;
			l->cont--;
		}
	}
}

//FUNCOES PARA LISTAS CIRCULARES
void inicializa_lista_circular(descr_circular *lista) {
    lista->inicio = NULL;
    lista->cont = 0;
}

void imprime_lista_circular(descr_circular *lista) {
	struct no *aux = lista->inicio;
	int cont=0;

    while(cont < lista->cont) {
        printf("->%d\n", aux->valor);
        aux = aux->proximo;
        cont++;
    }	
}

int esta_vazia_circular(descr_circular *lista) {
    if (lista->inicio == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void insere_vazia_circular(descr_circular *lista, int val) {
	lista->inicio = malloc(sizeof(struct no));
    lista->inicio->valor = val;
    lista->inicio->proximo = lista->inicio;
    lista->inicio->anterior = lista->inicio;
    lista->cont++;
}

void insere_inicio_circular(descr_circular *lista, int val) {
    if (esta_vazia_circular(lista) == 1) {
        insere_vazia_circular(lista, val);
    }else{
        struct no *aux = malloc(sizeof(struct no));
        aux->valor = val;
        aux->proximo = lista->inicio; 
        aux->anterior = lista->inicio->anterior;
        lista->inicio->anterior = aux;
        lista->inicio = aux;
        lista->cont++;
    }
}

void copia_inv(descr_circular *lista1, descr_circular *lista2) {
	struct no *aux, *aux2, *aux3;
	int cont = 0;

	if (esta_vazia_circular(lista2) == 0) {
		if (esta_vazia_circular(lista1) == 0) {
			aux = lista1->inicio->anterior;
		}else{
			aux = malloc(sizeof(struct no));
		}
		aux2 = lista2->inicio->anterior;

		while (cont < lista2->cont) {
			aux3 = malloc(sizeof(struct no));
			aux3->valor = aux2->valor;
			aux->proximo = aux3;
			aux3->anterior = aux;
			aux3->proximo = lista1->inicio;
			aux = aux3;
			aux2 = aux2->anterior;
			cont++;
			lista1->cont++;
		}
	}

}

void elimina_nos_pares(descr_circular *l) {
	int cont=0, cont2=0, cont_lista = l->cont;
	struct no *aux = l->inicio;

	if (esta_vazia_circular(l) == 1) {
		printf("Lista vazia\n");
	}else{
		while (cont < cont_lista) {
			aux = aux->proximo;
			cont++;
			if (cont%2 == 0) {
				if (aux->proximo == NULL) {
					aux->anterior->proximo = NULL;
				}else{
					aux->proximo->anterior = aux->anterior;
					aux->anterior->proximo = aux->proximo;
				}
				free(aux);
				l->cont--;
			}
		}
	}	
}

void intercala(descr_circular *l1, descr_circular *l2){
	struct no *aux = l1->inicio;
	struct no *aux2 = l2->inicio;

	struct no *aux3;

	int cont = 0, cont_l1 = l1->cont;

	if (esta_vazia_circular(l1) == 1 && esta_vazia_circular(l2) == 1) {
		printf("Listas vazias\n");
	} else if (esta_vazia_circular(l2) == 1){
		return;
	} else{
		if (esta_vazia_circular(l1) == 1) {
			l1->inicio = l2->inicio;
			l1->inicio->anterior = l2->inicio->anterior;
			l1->cont = l2->cont;
			return;
		}

		while (cont < cont_l1) {
			cont++;
			aux3 = aux2->proximo;
			aux2->proximo = aux->proximo; 
			aux->proximo = aux2;
			aux2->anterior = aux;
			aux = aux2->proximo;
			aux2 = aux3;
			l1->cont++;
		}
		aux->proximo = l1->inicio;
		l1->inicio->anterior = aux;

	}

}

int main() {

	// struct l_descr lista1;
	// struct l_descr lista2;
	// struct l_descr listal;

	// inicializa_lista(&lista1);
	// inicializa_lista(&lista2);
	// inicializa_lista(&listal);

    // insere_inicio(&lista1, 20);
    // insere_inicio(&lista1, 30);
    // insere_inicio(&lista1, 13);
    // insere_inicio(&lista1, 10);
    // insere_inicio(&lista1, 4);

    // insere_inicio(&lista2, 20);
    // insere_inicio(&lista2, 30);
    // insere_inicio(&lista2, 13);
    // insere_inicio(&lista2, 10);
    // insere_inicio(&lista2, 4);

    // printf("LISTA 1\n");
    // imprime_lista(&lista1);
    // printf("LISTA 2\n");
    // imprime_lista(&lista2);

    // if (sao_iguais(&lista1, &lista2) == 1) {
    // 	printf("listas iguais\n");
    // }else{
    // 	printf("listas diferentes\n");
    // }


    // copiar(&lista1, &lista2);
    // printf("LISTA 1\n");
    // imprime_lista(&lista1);
    // printf("LISTA 2\n");
    // imprime_lista(&lista2);


    // diferenca_ordenada(&listal, &lista1, &lista2);
    // diferenca(&listal, &lista1, &lista2);
    // printf("LISTA L\n");
    // imprime_lista(&listal);


    // printf("comuns = %d\n", comuns(&lista1, &lista2));


    // destroi(&lista2);
    // printf("LISTA 2\n");
    // imprime_lista(&lista2);


    // printf("inversa = %d\n", eh_inversa(&lista1, &lista2));


    // remover_nos_impares(&lista1);    



 //    descr_circular l_circular1, l_circular2;
	// inicializa_lista_circular(&l_circular1);
	// inicializa_lista_circular(&l_circular2);

	// insere_inicio_circular(&l_circular1, 5);
	// insere_inicio_circular(&l_circular1, 4);
	// insere_inicio_circular(&l_circular1, 3);
	// insere_inicio_circular(&l_circular1, 2);
	// insere_inicio_circular(&l_circular1, 1);

	// insere_inicio_circular(&l_circular2, 6);
	// insere_inicio_circular(&l_circular2, 7);
	// insere_inicio_circular(&l_circular2, 8);
	// insere_inicio_circular(&l_circular2, 9);
	// insere_inicio_circular(&l_circular2, 10);

	// imprime_lista_circular(&l_circular1);
	// printf("--------------\n");
	// imprime_lista_circular(&l_circular2);

	// copia_inv(&l_circular1, &l_circular2);

	// imprime_lista_circular(&l_circular1);
	// printf("-------------\n");
	// elimina_nos_pares(&l_circular1);
	// imprime_lista_circular(&l_circular1);

	// intercala(&l_circular1, &l_circular2);
	// imprime_lista_circular(&l_circular1);

}