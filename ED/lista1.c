//ENVIAR PARA TROIS@INF.UFSM.BR ATE DIA 26/3

#include <stdio.h>
#include <stdlib.h>

// Descritor da lista
struct l_descr{
	struct no *inicio;
	int cont;
	struct no *fim;
};

// Elementos da lista
struct no{
	int valor;
	struct no *proximo;
};

void inicializa_lista(struct l_descr *lista) {
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->cont = 0;
}

void imprime_lista(struct l_descr *lista) {
    struct no *aux = lista->inicio;
    printf("Lista: \n");
    while(aux !=  NULL) {
        printf("->%d\n", aux->valor);
        aux = aux->proximo;
    }
}

int esta_vazia(struct l_descr *lista) {
    if (lista->inicio == NULL) {
        return 1;
    } else {
        return 0;
    }
}

void insere_inicio(struct l_descr *lista, int val) {
    if (esta_vazia(lista) == 1) {
        lista->inicio = malloc(sizeof(struct no));
        lista->inicio->valor = val;
        lista->inicio->proximo = NULL;
        lista->cont++;
        lista->fim = lista->inicio;
    }else{
        struct no *aux = malloc(sizeof(struct no));
        aux->valor = val;
        aux->proximo = lista->inicio;
        lista->inicio = aux;
        lista->cont++;
    }
}

void insere_fim(struct l_descr *lista, int val) {
    if (esta_vazia(lista) == 1) {
        lista->inicio = malloc(sizeof(struct no));
        lista->inicio->valor = val;
        lista->inicio->proximo = NULL;
        lista->cont++;
        lista->fim = lista->inicio;
    }else{
        struct no *aux = malloc(sizeof(struct no));
        aux->valor = val;
        aux->proximo = NULL;
        lista->fim->proximo = aux;
        lista->fim = aux;
        lista->cont++;
    }
}

void insere_ind(struct l_descr *lista, int val, int indice) {
    struct no *aux = lista->inicio;
    struct no *no_anterior;
    int i=0;

    if (indice == 1) {
        insere_inicio(lista, val);
    } else if (indice > lista->cont) {
        insere_fim(lista, val);
    } else {
        for (i=0; i<indice-1; i++) {
            no_anterior = aux;
            aux = aux->proximo;
        }

        struct no *no_novo = malloc(sizeof(struct no));

        no_novo->valor = val;
        no_novo->proximo = aux;
        no_anterior->proximo = no_novo;
        lista->cont++;
    }
    
}

int insere_ordenado(struct l_descr *lista, int val) {
    int contador=1;

    if (esta_vazia(lista) == 1) {
        insere_inicio(lista, val);
    } else {
        if (lista->inicio->valor > val) {
            insere_inicio(lista, val);
        } else if (lista->fim->valor < val) {
            insere_fim(lista, val);
            contador = lista->cont;
        } else {
            struct no *aux = lista->inicio;
            while (aux != NULL) {
                contador++;
                if (aux->proximo->valor >= val) {
                    struct no *novo = malloc(sizeof(struct no));
                    struct no *anterior = malloc(sizeof(struct no));
                    
                    anterior = aux;
                    aux = aux->proximo;                    
                    novo->valor = val;
                    novo->proximo = aux;
                    anterior->proximo = novo;
                    lista->cont++;
                    break;
                }else {
                    aux = aux->proximo;
                }
            }
        }
    }
    return contador;

}

int remove_primeiro(struct l_descr *lista) {
    if (esta_vazia(lista) == 1) {
        return -1;
    } else {
        struct no *aux = lista->inicio;
        int val;
        val = aux->valor;
        lista->inicio = aux->proximo;
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
            free(aux);
        }
    }
    return val;
}

int busca_indice(struct l_descr *lista, int val) {
    int i, cont=0;
    struct no *aux = lista->inicio;

    if (esta_vazia(lista)==1) {
        return -1;
    } else {
        while(aux != NULL) {
            cont++;
            if (aux->valor == val) {
                return cont;
            } else {
                aux = aux->proximo;  
            } 
        } 
    }
}

int main() {

    struct l_descr lista;
    int retorno;
    
    inicializa_lista(&lista);

    insere_inicio(&lista, 5);
    insere_fim(&lista, 20);
    insere_fim(&lista, 30);
    insere_fim(&lista, 40);
    insere_fim(&lista, 50);

    imprime_lista(&lista);

    // insere_ind(&lista, 35, 5);  

    // printf("Inseriu no indice %d\n", insere_ordenado(&lista, 2));

    // retorno = remove_primeiro(&lista);

    // retorno = remove_ultimo(&lista);

    // retorno = remove_indice(&lista, 3);

    // if (retorno == -1) {
    //     printf("Lista vazia\n");
    // } else {
    //     printf("Número %d removido da lista.\n", retorno);
    // }

    // imprime_lista(&lista);

    // retorno = busca_indice(&lista, 30);

    // if(retorno == 0) {
    //     printf("elemeno nao esta na lista\n");
    // } else if (retorno == -1){
    //     printf("lista vazia.\n");
    // } else {
    //     printf("elemento esta no indice %d\n", retorno);
    // }

    return 0;
}
