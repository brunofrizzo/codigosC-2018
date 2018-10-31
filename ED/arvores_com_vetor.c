#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define TAM 1000 
#define vazio -999

struct no {
	int valor;
	struct no *esq;
	struct no *dir;
}; 

typedef struct no arvore;

void inicializa_vetor(int vet[]) {
	for(int i=0;i<TAM;i++){
		vet[i] = vazio;
	}
}

void impressao(int vet[]) {
	for(int i=0;i<10;i++) 
		printf("->%d\n", vet[i]);
}

void insere_ordenado(int vet[], int valor, int i) {
	if (vet[i] == vazio) 
		vet[i] = valor;
	else if(valor < vet[i])
		insere_ordenado(vet, valor, (i*2)+1);
	else
		insere_ordenado(vet, valor, (i*2)+2);
}

int remover(int vet[], int val) {
	int i;
	for (i=0;i<TAM;i++){
		if (vet[i] == val) {
			vet[i] = vazio;
			return i;
		}
	}
	return -1;
}

int busca(int vet[], int val) {
	for (int i=0;i<TAM;i++){
		if (vet[i] == val) {
			return i;
		}
	}
}

int main() {

	int vetor[TAM];

	inicializa_vetor(vetor);
	insere_ordenado(vetor, 6, 0);
	insere_ordenado(vetor, 15, 0);
	insere_ordenado(vetor, 4, 0);
	insere_ordenado(vetor, 10, 0);
	insere_ordenado(vetor, 3, 0);
	insere_ordenado(vetor, 5, 0);
	insere_ordenado(vetor, 17, 0);				
	printf("removido indice %d\n", remover(vetor, 17));
	printf("valor 4 no indice %d\n", busca(vetor, 4)); 
	impressao(vetor);
	return 0;

}