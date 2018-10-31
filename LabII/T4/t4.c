#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TAM 100
#define N 10

struct Fila{
     int data[N]; 
     int tamanho;
     int inicio;
};

typedef struct Fila Fila;

Fila* criarFila();
void enqueue(Fila* f, int elemento);
bool cheia(Fila* f);
bool vazia(Fila* f);
int dequeue(Fila* f);
int frente(Fila* f);

void erro(char msg[]){
     printf(msg);
     getchar();
     exit(0);     
}

Fila* criarFila(){
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

void print1(Fila* f){
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
}

int dequeue(Fila* f){ 
    if (vazia(f))
        erro("Erro: Tentando remover da fila vazia...\n");
    int temp = f->data[f->inicio];
    printf("Removendo %d\n", temp);
    f->inicio = (f->inicio + 1) % N;
    f->tamanho--;
    return temp;    
}

int frente(Fila* f){ 
    if (vazia(f))
        erro("Erro: Tentando obter a frente da fila vazia...\n");
    return f->data[f->inicio];
}

struct no{
    int val;
    struct no *proximo;
};

struct l_descr{
    struct no *inicio;
    int cont;
    struct no *fim;
};

void inicializaLista(struct l_descr *lista) {
	lista->inicio = NULL;
	lista->cont=0;
	lista->fim = NULL;
}

void insereListaAdj(struct l_descr *lista, int val) {
    if (lista->inicio == NULL) {
        lista->inicio = malloc(sizeof(struct no));
        lista->inicio->val = val;
        lista->inicio->proximo = NULL;
        lista->cont++;
        lista->fim = lista->inicio;
    }else{
        struct no *aux = malloc(sizeof(struct no));
        aux->val = val;
        aux->proximo = NULL;
        lista->fim->proximo = aux;
        lista->fim = aux;
        lista->cont++;
    }
}

struct grafo{
    struct l_descr *vetor_adj;
    int *visitados;
    int tamanho;
};

struct grafo *criarGrafo(int tamanho){
    struct grafo *g = malloc(sizeof(struct grafo));
    g->tamanho = tamanho;
    g->vetor_adj = malloc(tamanho*sizeof(struct l_descr));
    g->visitados = malloc(tamanho*sizeof(int)); 
    for(int i=0;i<tamanho;i++) 
    	inicializaLista(&g->vetor_adj[i]);
    return g;
}

void imprimirGrafo(struct grafo *g){
    struct no *aux;
    for (int i=0; i<g->tamanho; i++){
		aux = g->vetor_adj[i].inicio;
		printf("adjacentes do %d: ", i);
		while(aux != NULL) {
			printf("%d ", aux->val);
			aux = aux->proximo;
		}
    printf("\n"); 
    }
}

void inserirAresta(struct grafo *g, int val, int val2){
    if (g == NULL){
    	printf("Grafo vazio.");
    }else {
        insereListaAdj(&g->vetor_adj[val], val2);
    } 
}

void visitarSubGrafoEmProfundidade(struct grafo *g, int vertice){
    printf("CINZA: Visitando o vertice %d em pre-ordem\n", vertice);
    g->visitados[vertice] = 1;
    struct no *aux = g->vetor_adj[vertice].inicio;
    while(aux!=NULL){
        if (!g->visitados[aux->val])
            visitarSubGrafoEmProfundidade(g, aux->val);
        aux = aux->proximo;
    }
    printf("PRETO: Visitando o vertice %d em pos-ordem\n", vertice);
}

void visitarEmProfundidade(struct grafo *g, int no_inicial){
   for (int i = no_inicial; i < g->tamanho; i++)
       g->visitados[i] = false;
   for (int i = no_inicial; i < g->tamanho; i++)
       if (!g->visitados[i])
          visitarSubGrafoEmProfundidade(g, i);
}     

void visitarSubGrafoEmLargura(struct grafo *g, int vertice){
    g->visitados[vertice] = true;
    Fila* f = criarFila();
    enqueue(f, vertice);
    printf("Largura - CINZA: Visitando o vertice %d em pre-ordem\n", vertice);
    while (!vazia(f)){
        int u = dequeue(f); 
        struct no *aux = g->vetor_adj[u].inicio;
        while(aux!=NULL){
            if (!g->visitados[aux->val]){
                g->visitados[aux->val] = true;
                printf("Largura - CINZA: Visitando o vertice %d em pre-ordem\n", aux->val);
                enqueue(f, aux->val);
            }
            aux = aux->proximo;
        }
      printf("Largura - PRETO: Visitando o vertice %d em pos-ordem\n", u);
    }
    free(f);
}

void visitarEmLargura(struct grafo *g, int no_inicial){
   for (int i = no_inicial; i < g->tamanho; i++)
       g->visitados[i] = false;
   for (int i = no_inicial; i < g->tamanho; i++)
       if (!g->visitados[i])
          visitarSubGrafoEmLargura(g, i);
} 

void exclui_inicio_lista(struct l_descr *lista) {
    struct no *aux = lista->inicio;
    lista->inicio = lista->inicio->proximo;
    lista->cont--;
    free(aux);
}

void desalocaLista(struct l_descr *lista) {
    int i, cont = lista->cont;
    for (i=0;i<cont;i++)
        exclui_inicio_lista(lista);
}

void desalocaGrafo(struct grafo *g) {
    int i;
    for (i=0;i<g->tamanho;i++)
        desalocaLista(&g->vetor_adj[i]);
    free(g->vetor_adj);  
    free(g->visitados);
    free(g);
}

int main() {
    int tam, i, val, opcao;

    printf("informe o tamanho do grafo\n");
    scanf("%d", &tam);

    struct grafo *g = criarGrafo(tam);

    for(i=0;i<tam;i++){
        printf("informe os adjacentes do vertice %d (digite -1 para sair)\n", i);
        scanf("%d", &val);
        while(val != -1) {
            inserirAresta(g, i, val);
            scanf("%d", &val);
        }
    }

    printf("informe um no a ser percorrido\n");
    scanf("%d", &val);

    printf("digite 1 se deseja percorrer por profundidade ou 2 por largura\n");
    scanf("%d", &opcao);
    while(opcao < 1 || opcao > 2) {
        printf("opcao invalida. informe novamente.\n");
        scanf("%d", &opcao);
    }

    if(opcao == 1) 
        visitarEmProfundidade(g, val);
    else
        visitarEmLargura(g, val);

    desalocaGrafo(g);

    return 0;
}