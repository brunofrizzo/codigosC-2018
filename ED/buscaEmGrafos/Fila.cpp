#include "stdio.h"
#include "stdlib.h"
#include "malloc.h"
#include "Fila.h"

void erro(char msg[]){
     printf(msg);
     getchar();
     exit(0);     
}

Fila* criar(){
    Fila* f = (Fila*) malloc(sizeof(Fila));
    f->tamanho = 0;
    f->inicio = 0;
    return f;
}

bool cheia(Fila* f){ return f->tamanho == N;}
bool vazia(Fila* f){ return f->tamanho == 0;}

void print(Fila* f, int i) {
	printf("Elemento na pos %d , valor: %d\n", i, f->data[i]);
}

void print(Fila* f){
		printf("***********************************************\n");
		int fim = (f->inicio + f->tamanho) % N;
		printf("Fila=[inicio=%d, fim=%d]\n",f->inicio, fim);
		if (fim >= f->inicio)
			for (int i = f->inicio; i < fim; i++)
				print(f, i);
		else {
			for (int i = f->inicio; i < N; i++)
				print(f, i);
			for (int i = 0; i < fim; i++)
				print(f, i);
		}
		printf(" ");     
}

void enqueue(Fila* f, int elemento){
     printf("Inserindo %d\n", elemento);
     if (cheia(f))
        erro("Fila Cheia\n");
     int fim = (f->inicio + f->tamanho) % N;
     f->data[fim] = elemento;
     f->tamanho++;
    // print(f);
}

int dequeue(Fila* f){ 
		if (vazia(f))
			erro("Erro: Tentando remover da fila vazia...\n");
		int temp = f->data[f->inicio];
		printf("Removendo %d\n", temp);
		f->inicio = (f->inicio + 1) % N;
		f->tamanho--;
	//	print(f);
		return temp;    
}

int frente(Fila* f){ 
		if (vazia(f))
			erro("Erro: Tentando obter a frente da fila vazia...\n");
		return f->data[f->inicio];
}
