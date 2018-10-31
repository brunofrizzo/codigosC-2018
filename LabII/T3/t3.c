#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct carro{
	char placa[15];
	char marca[50];
	int ano;
};

struct no_carro{	
	struct carro *carro;
	struct no_carro *proximo;
};

struct l_carro_descr{
	struct no_carro *inicio;
	int cont;
	struct no_carro *fim;
}; 

struct arvore{
	struct carro *carro;
	struct arvore *esq;
	struct arvore *dir;
}; 

void inicializa_lista_carros(struct l_carro_descr *lista) {
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->cont = 0;
}

void insere_vazia_lista_carros(struct l_carro_descr *lista, struct carro *carro) {
    lista->inicio = malloc(sizeof(struct no_carro));
    lista->inicio->carro = carro;
    lista->inicio->proximo = NULL;
    lista->cont++;
    lista->fim = lista->inicio;
}

void insere_inicio_lista_carros(struct l_carro_descr *lista, struct carro *carro) {
    if (lista->inicio == NULL) {
        insere_vazia_lista_carros(lista, carro);
    }else{
        struct no_carro *aux = malloc(sizeof(struct no_carro));
        aux->carro = carro;
        aux->proximo = lista->inicio;
        lista->inicio = aux;
        lista->cont++;
    }
}

void insere_fim_lista_carros(struct l_carro_descr *lista, struct carro *carro) {
    if (lista->inicio == NULL) {
        insere_vazia_lista_carros(lista, carro);
    }else{
        struct no_carro *aux = malloc(sizeof(struct no_carro));
        aux->carro = carro;
        aux->proximo = NULL;
        lista->fim->proximo = aux;
        lista->fim = aux;
        lista->cont++;
    }
}

void insere_ordenado_lista_carros(struct l_carro_descr *lista, struct carro *carro) {
    if (lista->inicio == NULL) {
        insere_inicio_lista_carros(lista, carro);
    } else {
        if (strcmp(lista->inicio->carro->placa, carro->placa) > 0) {
            insere_inicio_lista_carros(lista, carro);
        } else if (strcmp(lista->fim->carro->placa, carro->placa) < 0) {
            insere_fim_lista_carros(lista, carro);
        } else {
            struct no_carro *aux = lista->inicio;
            while (aux != NULL) {
                if (aux->proximo != NULL && strcmp(aux->proximo->carro->placa, carro->placa) >= 0) {
                    struct no_carro *novo = malloc(sizeof(struct no_carro));
                    struct no_carro *anterior = malloc(sizeof(struct no_carro));
                    
                    anterior = aux;
                    aux = aux->proximo;   
                    novo->carro = carro;
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
}

void exclui_inicio_lista_carros(struct l_carro_descr *lista, struct no_carro *aux) {
	lista->inicio = aux->proximo;
	lista->cont--;
	free(aux);
}

void exclui_fim_lista_carros(struct l_carro_descr *lista, struct no_carro *aux, struct no_carro *anterior) {
	lista->fim = anterior;
	anterior->proximo = NULL;
	lista->cont--;
	free(aux);
}

void exclui_lista_carros(struct l_carro_descr *lista, char placa[]) {
	struct no_carro *aux = lista->inicio;
	struct no_carro *anterior = NULL;

	while(aux != NULL){
		if (strcmp(aux->carro->placa, placa) == 0) {
			if (anterior == NULL) {
				exclui_inicio_lista_carros(lista, aux);
			}else if(aux->proximo == NULL) {
				exclui_fim_lista_carros(lista, aux, anterior);
			}else{
				anterior->proximo = aux->proximo;
				lista->cont--;
				free(aux);
			}
			break;
		}
		anterior = aux;
		aux = aux->proximo;
	}
}

struct carro *busca_carro_lista(struct l_carro_descr *lista, char placa[]) {
	struct no_carro *aux = lista->inicio;

	while(aux != NULL){
		if (strcmp(aux->carro->placa, placa) == 0) {
			return aux->carro;
		}
		aux = aux->proximo;
	}
	return NULL;
}

void imprime_lista_carros(struct l_carro_descr *lista) {
   struct no_carro *aux = lista->inicio;
    printf("Carros: \n");
    while(aux !=  NULL) {
        printf("->Placa: %s | Marca: %s | Ano: %d\n", aux->carro->placa, aux->carro->marca, aux->carro->ano);
        aux = aux->proximo;
    }
}

void retira_espaco(char *string) {
	int len = strlen(string);
	if (string[len-1] == '\n') 
		string[--len] = 0;
}

bool placa_ja_cadastrada(char placa[], struct l_carro_descr *lista) {
	struct no_carro *aux = lista->inicio;

	while(aux != NULL){
		if (strcmp(aux->carro->placa, placa) == 0) {
			return true;
		}
		aux = aux->proximo;
	}
	return false;
}

void libera_lista(struct l_carro_descr *lista) {
	int cont = lista->cont, i;
	for (i=0;i<cont;i++){
		exclui_inicio_lista_carros(lista, lista->inicio);
	}
}

bool esta_vazia(struct arvore *a) {
	return a==NULL;
}

void imprime_arvore_placa(struct arvore *a) {
	if (!esta_vazia(a)) {
		imprime_arvore_placa(a->esq);
		printf("->%s\n", a->carro->placa);
		imprime_arvore_placa(a->dir);
	}
}

void imprime_arvore_marca(struct arvore *a) {
	if (!esta_vazia(a)) {
		imprime_arvore_marca(a->esq);
		printf("->%s | %s | %d\n", a->carro->placa, a->carro->marca, a->carro->ano);
		imprime_arvore_marca(a->dir);
	}
}

void imprime_arvore_ano(struct arvore *a) {
	if (!esta_vazia(a)) {
		imprime_arvore_ano(a->esq);
		printf("->%s | %s | %d\n", a->carro->placa, a->carro->marca, a->carro->ano);
		imprime_arvore_ano(a->dir);
	}
}

struct arvore *cria_vazia() {
	return NULL;
}

struct arvore *cria_arvore(struct carro *carro) {
	struct arvore *a = malloc(sizeof(struct arvore));
	a->carro = carro;
	a->esq = NULL;
	a->dir = NULL;
	return a;
}

struct arvore *insere_arvore_placa(struct arvore *a, struct carro *carro) {
	if (a == NULL){
		a = cria_arvore(carro);
	}else if (strcmp(carro->placa, a->carro->placa) < 0) {
		a->esq = insere_arvore_placa(a->esq, carro);
	}else{
		a->dir = insere_arvore_placa(a->dir, carro);
	}
	return a;
}

struct arvore *insere_arvore_marca(struct arvore *a, struct carro *carro) {
	if (a == NULL){
		a = cria_arvore(carro);
	}else if (strcmp(carro->marca, a->carro->marca) < 0) {
		a->esq = insere_arvore_marca(a->esq, carro);
	}else{
		a->dir = insere_arvore_marca(a->dir, carro);
	}
	return a;
}

struct arvore *insere_arvore_ano(struct arvore *a, struct carro *carro) {
	if (a == NULL){
		a = cria_arvore(carro);
	}else if (carro->ano < a->carro->ano) {
		a->esq = insere_arvore_ano(a->esq, carro);
	}else{
		a->dir = insere_arvore_ano(a->dir, carro);
	}
	return a;
}

struct arvore *buscar_carro_arvore(struct arvore *a, char placa[]) {
	if (a == NULL) {
		return NULL;
	}
	if(strcmp(placa, a->carro->placa) < 0) {
		return buscar_carro_arvore(a->esq, placa);
	}
	if(strcmp(placa, a->carro->placa) > 0){
		return buscar_carro_arvore(a->dir, placa);
	}
	return a;
}

struct arvore *remove_arvore_placa(struct carro *carro, struct arvore *a) {
	if (esta_vazia(a)) {
		return NULL;
	}else{
		if (strcmp(carro->placa, a->carro->placa) < 0) {
			a->esq = remove_arvore_placa(carro, a->esq);
		}else if (strcmp(carro->placa, a->carro->placa) > 0) {
			a->dir = remove_arvore_placa(carro, a->dir);
		}else{
			if (esta_vazia(a->esq) && esta_vazia(a->dir)) {
				free(a);
				a = NULL;
			} else if(esta_vazia(a->dir)) {
				struct arvore *aux = a;
				a = a->esq;
				free(aux);
			}else if(esta_vazia(a->esq)) {
				struct arvore *aux = a;
				a = a->dir;
				free(aux);
			}else{
				struct arvore *aux = a->esq;
				while (aux->dir != NULL) {
					aux = aux->dir;
				}
				a->carro = aux->carro;
				aux->carro = carro;
				a->esq = remove_arvore_placa(carro, a->esq);
			}
		}
		return a;		
	}
}

struct arvore *remove_arvore_marca(struct carro *carro, struct arvore *a) {
	if (esta_vazia(a)) {
		return NULL;
	}else{
		if (strcmp(carro->marca, a->carro->marca) < 0) {
			a->esq = remove_arvore_marca(carro, a->esq);
		}else if (strcmp(carro->marca, a->carro->marca) > 0) {
			a->dir = remove_arvore_marca(carro, a->dir);
		}else{
			if (esta_vazia(a->esq) && esta_vazia(a->dir)) {
				free(a);
				a = NULL;
			} else if(esta_vazia(a->dir)) {
				struct arvore *aux = a;
				a = a->esq;
				free(aux);
			}else if(esta_vazia(a->esq)) {
				struct arvore *aux = a;
				a = a->dir;
				free(aux);
			}else{
				struct arvore *aux = a->esq;
				while (aux->dir != NULL) {
					aux = aux->dir;
				}
				a->carro = aux->carro;
				aux->carro = carro;
				a->esq = remove_arvore_marca(carro, a->esq);
			}
		}
		return a;		
	}
}

struct arvore *remove_arvore_ano(struct carro *carro, struct arvore *a) {
	if (esta_vazia(a)) {
		return NULL;
	}else{
		if (carro->ano < a->carro->ano) {
			a->esq = remove_arvore_ano(carro, a->esq);
		}else if (carro->ano > a->carro->ano) {
			a->dir = remove_arvore_ano(carro, a->dir);
		}else{
			if (esta_vazia(a->esq) && esta_vazia(a->dir)) {
				free(a);
				a = NULL;
			} else if(esta_vazia(a->dir)) {
				struct arvore *aux = a;
				a = a->esq;
				free(aux);
			}else if(esta_vazia(a->esq)) {
				struct arvore *aux = a;
				a = a->dir;
				free(aux);
			}else{
				struct arvore *aux = a->esq;
				while (aux->dir != NULL) {
					aux = aux->dir;
				}
				a->carro = aux->carro;
				aux->carro = carro;
				a->esq = remove_arvore_ano(carro, a->esq);
			}
		}
		return a;		
	}
}

struct carro *adicionar_carro(struct l_carro_descr *lista) {
	struct carro *carro = malloc(sizeof(struct carro));

	setbuf(stdin, NULL);
	printf("Placa do carro: \n");
	fgets (carro->placa, 15, stdin);
	retira_espaco(carro->placa);
	while (placa_ja_cadastrada(carro->placa, lista)) {
		setbuf(stdin, NULL);
		printf("Placa ja cadastrada. Informe novamente: \n");
		fgets (carro->placa, 15, stdin);
		retira_espaco(carro->placa);
	}
	setbuf(stdin, NULL);
	printf("Marca:\n");
	fgets (carro->marca, 50, stdin);
	retira_espaco(carro->marca);
	printf("Ano:\n");
	scanf("%d", &carro->ano);

	insere_ordenado_lista_carros(lista, carro);
	printf("Carro adicionado com sucesso!!!\n");
	return carro;
}

struct carro *excluir_carro(struct l_carro_descr *lista) {
	if (lista->inicio == NULL) {
		printf("Nenhum carro cadastrado. Impossível realizar exclusão.\n");
	}else{
		char placa[15];
		struct carro *carro;

		printf("Carro cadastrados\n");
		imprime_lista_carros(lista);
		setbuf(stdin, NULL);
		printf("Informe a placa do carro que você deseja excluir:\n");
		fgets (placa, 15, stdin);
		retira_espaco(placa);
		while (!placa_ja_cadastrada(placa, lista)) {
			setbuf(stdin, NULL);
			printf("Placa não cadastrada. Informe novamente: \n");
			fgets (placa, 15, stdin);
			retira_espaco(placa);
		}

		carro = busca_carro_lista(lista, placa);
		exclui_lista_carros(lista, placa);
		printf("CARRO DE PLACA '%s' REMOVIDO COM SUCESSO.\n", placa);
		return carro;
	}
}

void busca_carro(struct arvore *a) {
	char placa[15];
	setbuf(stdin, NULL);
	printf("Informe a placa do carro que deseja buscar:\n");
	fgets (placa, 15, stdin);
	retira_espaco(placa);
	struct arvore *aux = buscar_carro_arvore(a, placa);
	if (aux == NULL) {
		printf("Carro não encontrado.\n");
	}else{
		printf("Carro encontrado.\n");
		printf("Placa: %s", aux->carro->placa);
		printf(" | Marca: %s", aux->carro->marca);
		printf(" | Ano: %d\n", aux->carro->ano);
	}
}

struct arvore *desaloca_arvore(struct arvore *a) {
	if (a != NULL){
		desaloca_arvore(a->esq);
		desaloca_arvore(a->dir);
		free(a);
	}
	return NULL;	
}

int menu_inicial() {
	int opcao;
	printf("\tMENU\n");
	printf("1-Adicionar carro\n");
	printf("2-Excluir carro\n");
	printf("3-Listar carros\n");
	printf("4-Buscar carros\n");
	printf("0-Sair\n");
	scanf("%d", &opcao);
	while (opcao < 0 || opcao > 4) {
		printf("Opção inválida. Informe novamente.\n");
		scanf("%d", &opcao);
	}
	return opcao;
}

int menu_listar_carros() {
	int opcao;
	printf("ORDENAR\n");
	printf("1-Por placa\n");
	printf("2-Por marca\n");
	printf("3-Por ano\n");
	printf("0-Sair\n");
	scanf("%d", &opcao);
	while (opcao < 0 || opcao > 3) {
		printf("Opção inválida. Informe novamente.\n");
		scanf("%d", &opcao);
	}
	return opcao;
}

int main() {

	int opcao;
	struct l_carro_descr lista_carros;
	struct arvore *arvore_placa = NULL;
	struct arvore *arvore_marca = NULL;
	struct arvore *arvore_ano = NULL;

	inicializa_lista_carros(&lista_carros);

	while (true) {
		opcao = menu_inicial();

		if (opcao == 1){
			struct carro *carro = adicionar_carro(&lista_carros);
			arvore_placa = insere_arvore_placa(arvore_placa, carro);
			arvore_marca = insere_arvore_marca(arvore_marca, carro);
			arvore_ano = insere_arvore_ano(arvore_ano, carro);
		}else if(opcao == 2) {
			struct carro *carro = excluir_carro(&lista_carros);
			arvore_placa = remove_arvore_placa(carro, arvore_placa); 
			arvore_marca = remove_arvore_marca(carro, arvore_marca);
			arvore_ano = remove_arvore_ano(carro, arvore_ano);
		}else if(opcao == 3) {
			
			opcao = menu_listar_carros();
			if (opcao == 1) {
				imprime_lista_carros(&lista_carros);
			}else if(opcao==2){
				imprime_arvore_marca(arvore_marca);
			}else if(opcao==3){
				imprime_arvore_ano(arvore_ano);
			}

		}else if(opcao == 4) {
			busca_carro(arvore_placa);
		}else{
			break;
		}

		printf("Deseja realizar outra operação? (1-Sim/2-Não)\n");
		scanf("%d", &opcao);
		while (opcao < 1 || opcao > 2) {
			printf("Opção inválida. Informe novamente.\n");
			scanf("%d", &opcao);
		}
		if (opcao == 2) 
			break;
	}

	libera_lista(&lista_carros);
	desaloca_arvore(arvore_placa);
	desaloca_arvore(arvore_marca);
	desaloca_arvore(arvore_ano);
}