#include <stdio.h>
#include <stdlib.h>

struct grafo {
	int num_arestas;
	int num_vertices;
	int **m;
};

int **criaMatriz(int tam) {
	int i, j;
	int **m = malloc(tam*sizeof(int *));
	for(i=0;i<tam;i++) {
		m[i] = malloc(tam*(sizeof(int)));
		for(j=0;j<tam;j++) {
			m[i][j] = 0;
		}
	}
	return m;
}

void criaGrafo(struct grafo *g, int tam) {
	g->num_arestas=0;
	g->num_vertices=0;
	g->m = criaMatriz(tam);
}

void insere_vertice(struct grafo *g) {
	g->num_vertices++;
}

void insere_aresta(struct grafo *g, int v1, int v2) {
	if (g->m[v1][v2] == 0) {
		g->num_arestas++;
		g->m[v1][v2] = 1;
	} 
}

void remove_aresta(struct grafo *g, int v1, int v2){
	if (g->m[v1][v2] == 1) {
		g->m[v1][v2] = 0;
		g->num_arestas--;
	}
 }

void mostra_grafo(struct grafo *g) {
	int i,j;
	printf("Lista de vertices: \n");
	for (i=0;i < g->num_vertices;i++) 
		printf("%d ", i);
	printf("\n");
	printf("Lista de arestas: \n");
	for (i=0;i < g->num_vertices;i++) {
		for (j=0;j < g->num_vertices;j++) {
			if (g->m[i][j] == 1) 
				printf("%d - %d\n", i, j);
		}
	}
}

int main () {
	struct grafo grafo;
	criaGrafo(&grafo, 5);
	insere_vertice(&grafo);
	insere_vertice(&grafo);
	insere_vertice(&grafo);
	insere_vertice(&grafo);
	insere_vertice(&grafo);
	insere_aresta(&grafo, 0, 1);
	insere_aresta(&grafo, 0, 2);	
	insere_aresta(&grafo, 1, 3);	
	insere_aresta(&grafo, 1, 2);	
	insere_aresta(&grafo, 2, 3);	
	remove_aresta(&grafo, 0, 2);
	mostra_grafo(&grafo);
	// printf("vertices: %d\n", grafo.num_vertices);
	// printf("arestas: %d\n", grafo.num_arestas);

}