#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

struct arvore {
	char chave[256];
	char valor[256];
	struct arvore *esq;
	struct arvore *dir;
}; 

struct arvore *criaArvore(char chave[], char valor[], struct arvore *sae, struct arvore *sad) {
	struct arvore *a = malloc(sizeof(struct arvore));
	strcpy(a->chave, chave);
	strcpy(a->valor, valor);
	a->esq = sae;
	a->dir = sad;
	return a;
}

void imprime(struct arvore *a) {
	if (a != NULL) {
		imprime(a->esq);
		printf("chave = %s\n", a->chave);
		imprime(a->dir);
	}
}

struct arvore *desaloca(struct arvore *a) {
	if (a != NULL){
		desaloca(a->esq);
		desaloca(a->dir);
		free(a);
	}
	return NULL;	
}

int existeValor(char chave[], struct arvore *a) {
	if (a == NULL) {
		return 0;
	}else{
		if (strcmp(a->chave, chave) == 0) {
			printf("Chave: %s\n", a->chave);
			printf("Valor: %s\n", a->valor);
			return 1;
		}else{
			return existeValor(chave, a->dir)||existeValor(chave, a->esq);
		}
	
	}
}

int existeValorSemPrintfi(char chave[], struct arvore *a) {
	if (a == NULL) {
		return 0;
	}else{
		if (strcmp(a->chave, chave) == 0) {
			return 1;
		}else{
			return existeValorSemPrintfi(chave, a->dir)||existeValorSemPrintfi(chave, a->esq);
		}
	
	}
}

struct arvore *insereOrdenado(char chave[], char valor[], struct arvore *a) {
	if (a == NULL) {
		a = criaArvore(chave, valor, NULL, NULL);
	}else{
		if (strcmp(chave, a->chave) < 0) {
			a->esq = insereOrdenado(chave, valor, a->esq);
		} else {
			a->dir = insereOrdenado(chave, valor, a->dir);
		}	
	}
	return a;
}

struct arvore *removeElemento(char chave[], struct arvore *a) {
	if (a == NULL) {
		return NULL;
	}else{
		if (strcmp(chave, a->chave) < 0) {
			removeElemento(chave, a->esq);
		}else if (strcmp(chave, a->chave) > 0) {
			a->dir = removeElemento(chave, a->dir);
		}else{
			if (a->esq == NULL && a->dir == NULL) {
				free(a);
				a = NULL;
			} else if(a->dir == NULL) {
				struct arvore *aux = a;
				a = a->esq;
				free(aux);
			}else if(a->esq == NULL) {
				struct arvore *aux = a;
				a = a->dir;
				free(aux);
			}else{
				struct arvore *aux = a->esq;
				while (aux->dir != NULL) {
					aux = aux->dir;
				}
				strcpy(a->chave, aux->chave);
				strcpy(aux->chave, chave);
				a->esq = removeElemento(chave, a->esq);
			}
		}
		return a;
	}
}

int chave_ja_cadastrada(struct arvore *a, char chave[]) {
	if (a == NULL) {
		return 0;
	}else{
		if (strcmp(a->chave, chave) == 0) {
			return 1;
		}else{
			return existeValor(chave, a->dir)||existeValor(chave, a->esq);
		}
	}
}

void retira_espaco(char *string) {
	int len = strlen(string);
	if (string[len-1] == '\n') 
		string[--len] = 0;
}

struct arvore *incluirChaveValor(struct arvore *a) {
	char chave[256], valor[256];
	setbuf(stdin, NULL);
	printf("Informe a chave: \n");
	fgets(chave, 255, stdin);
	retira_espaco(chave);
	setbuf(stdin, NULL);
	printf("Informe o valor: \n");
	fgets(valor, 255, stdin);
	retira_espaco(valor);
	a = insereOrdenado(chave, valor, a);
	printf("Chave-valor inserido com sucesso!\n");
	return a;
}

struct arvore *excluirChave(struct arvore *a) {
	char chave[256];
	setbuf(stdin, NULL);
	printf("Informe a chave a ser excluída: \n");
	fgets(chave, 255, stdin);
	retira_espaco(chave);
	while(chave_ja_cadastrada(a, chave) == 0) {
		setbuf(stdin, NULL);
		printf("Chave não cadastrada. Informe novamente: \n");
		fgets(chave, 255, stdin);
		retira_espaco(chave);
	}
	a = removeElemento(chave, a);
	printf("Chave removida com sucesso!\n");	
	return a;
}

int contaElementos(struct arvore *a) {
	if (a != NULL){
		return 1+contaElementos(a->esq)+contaElementos(a->dir);
	}else{
		return 0;
	}
}

void buscaChave(struct arvore *a) {
	char chave[256];
	setbuf(stdin, NULL);
	printf("Informe uma chave: \n");
	fgets(chave, 255, stdin);
	retira_espaco(chave);
	existeValor(chave, a);
}

void calculaTempo(struct timespec *ts1, struct timespec *ts2){
    if (ts2->tv_nsec < ts1->tv_nsec) {
        ts2->tv_nsec += 1000000000;
        ts2->tv_sec--;
    }
    printf("%ld.%09ld\n", (long)(ts2->tv_sec - ts1->tv_sec), ts2->tv_nsec - ts1->tv_nsec);
}

int menu_inicial() {
	int op;
	printf("------------------MENU----------------\n");
	printf("1-Incluir chave-valor\n");
	printf("2-Excluir chave\n");
	printf("3-Imprimir quantidade de pares chave-valor armazenadas\n");
	printf("4-Buscar chave\n");
	printf("0-Sair\n");
	scanf("%d", &op);
	while(op < 0 || op > 5) {
		printf("Opção inválida. Informe novamente: \n");
		scanf("%d", &op);
	}
	return op;
}

void imprime_mais_a_direita_possivel(struct arvore *a) {
	// struct arvore *arv = a;
	while (a->dir != NULL) {
		a = a->dir;
	}
	printf("Chave: %s | Valor: %s\n", a->chave, a->valor);
}

void imprime_mais_a_esquerda_possivel(struct arvore *a) {
	// struct arvore *arv = a;
	while (a->esq != NULL) {
		a = a->esq;
	}
	printf("Chave: %s | Valor: %s\n", a->chave, a->valor);
}

int main() {
    struct timespec ini, fim;
    clock_gettime(CLOCK_REALTIME, &ini); 
	struct arvore *dicionario = NULL;
	int i, num;
	char x[256];

	// for(i=1;i<5001;i++) {
	// 	sprintf(x, "%d", i);
	// 	dicionario = insereOrdenado(x, x, dicionario);
	// }
	// printf("Primeiro elemento a ser inserido:\n");
	// printf("chave: %s | valor: %s\n", dicionario->chave, dicionario->valor);
	// printf("Ultimo elemento a ser inserido: \n");
	// imprime_mais_a_direita_possivel(dicionario);
	// clock_gettime(CLOCK_REALTIME, &fim);
	// printf("TEMPO: ");
 //    calculaTempo(&ini, &fim);





 //    clock_gettime(CLOCK_REALTIME, &ini); 
	// for(i=5000;i>0;i--) {
	// 	sprintf(x, "%d", i);
	// 	dicionario = insereOrdenado(x, x, dicionario);
	// }
	// printf("Primeiro elemento a ser inserido:\n");
	// imprime_mais_a_esquerda_possivel(dicionario);
	// printf("Ultimo elemento a ser inserido: \n");
	// printf("chave: %s | valor: %s\n", dicionario->chave, dicionario->valor);
	// clock_gettime(CLOCK_REALTIME, &fim);
	// printf("TEMPO: ");
 //    calculaTempo(&ini, &fim);




    for(i=0;i<50;i++) {
		num = rand()%500000;
		sprintf(x, "%d", num);
		while(chave_ja_cadastrada(dicionario, x) == 1) {
			num = rand()%500000;
			sprintf(x, "%d", num);
		}
		dicionario = insereOrdenado(x, x, dicionario);
	}
	printf("Primeiro elemento a ser inserido:\n");
	imprime_mais_a_direita_possivel(dicionario);
	printf("Ultimo elemento a ser inserido: \n");
	printf("chave: %s | valor: %s\n", dicionario->chave, dicionario->valor);
	clock_gettime(CLOCK_REALTIME, &fim);
	printf("TEMPO: ");
    calculaTempo(&ini, &fim);


    

	// int opcao;

	// opcao = menu_inicial();
	// while (opcao != 0) {
	// 	if (opcao == 1) {
	// 		dicionario = incluirChaveValor(dicionario);
	// 	}else if (opcao == 2) {
	// 		dicionario = excluirChave(dicionario);
	// 	}else if (opcao == 3) {
	// 		printf("->%d\n", contaElementos(dicionario));
	// 	}else if (opcao == 4) {
	// 		buscaChave(dicionario);
	// 	}else if(opcao == 5) {
	// 		imprime(dicionario);
	// 	}
	// 	opcao = menu_inicial();
	// }
    
}