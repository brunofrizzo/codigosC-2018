#include <stdio.h>
#include <stdlib.h>

int *aloca_vetor(int col) {
	int *v = malloc(col*sizeof(int));
	return v;
}

void le_vetor(int *vet, int col) {
	int i;
	for (i=0;i<col;i++){
		printf("informe vetor[%d]:\n", i);
		scanf("%d", &vet[i]);
	}
}

void imprime_vetor(int *vet, int col) {
	int i;
	for (i=0;i<col;i++){
		printf("vetor[%d]: %d\n", i, vet[i]);
	}
}

int **aloca_matriz(int lin, int col) {
	int i;
	int **m = malloc(lin*sizeof(int *));

	for (i=0; i<lin; i++) {
		m[i] = malloc(col*sizeof(int));
	}

	return m;
}

void le_matriz(int **mat, int lin, int col) {
	int i, j;

	for(i=0; i<lin; i++) {
		for (j=0; j<col; j++) {
			printf("informe matriz[%d][%d]:\n", i, j);
			scanf("%d", &mat[i][j]);
		}
	}
}

void imprime_matriz(int **mat, int lin, int col) {
	int i, j;
	for (i=0;i<lin;i++){
		for (j=0; j<col; j++) {
			printf("matriz[%d][%d]: %d\n", i, j, mat[i][j]);
		} 
	}
}

int ***aloca_cubo(int lin, int col, int prof) {
	int i,j;
	int ***cubo=malloc(prof*sizeof(int **));
	
	for(i=0;i<prof;i++){
		cubo[i]=malloc(lin*sizeof(int *));
		for(j=0;j<lin;j++){
		    cubo[i][j]=malloc(col*sizeof(int));
		}
	}

	return cubo;	
}

void le_cubo(int ***cubo, int prof, int lin, int col) {
	int i,j,k;

	for(i=0;i<prof;i++){
		for(j=0;j<lin;j++){
			for(k=0;k<col;k++){
				printf("informe o valor de mat[%d][%d][%d]: ", i,j,k);
				scanf("%d", &cubo[i][j][k]);
			}
		}
	}
}

void imprime_cubo(int ***cubo, int prof, int lin, int col) {
	int i, j, k;

	for(i=0;i<prof;i++){
		for(j=0;j<lin;j++){
			for(k=0;k<col;k++){
				printf("%d\t", cubo[i][j][k]);
			}
		    printf("\n");
		}
	    printf("\n");
	}
	printf("\n");
}

void *cria_estrutura(int prof, int lin, int col){
	while (prof < 0 || lin < 0 || col <= 0) {
		printf("dados invalidos. informe novamente profundidade, linhas e colunas\n");
		scanf("%d %d %d", &prof, &lin, &col);
	}

	if (col > 0 && lin == 0 && prof == 0) {
		int *vet = aloca_vetor(lin);
		return vet;
	} else if (col > 0 && lin > 0 && prof==0) {
		int **mat = aloca_matriz(lin, col);
		return mat;
	}else if (col > 0 && lin > 0 && prof > 0) {
		if (prof == 1) {
			int **mat = aloca_matriz(lin, col);
			return mat;
		}else{
			int ***cubo = aloca_cubo(prof, lin, col);
			return cubo;
		}
	} 

}

void le_estrutura(void *estr, int prof, int lin, int col) {
	if (col > 0 && lin == 0 && prof == 0) {
		le_vetor(estr, lin);
	} else if (col > 0 && lin > 0 && prof==0) {
		le_matriz(estr, lin, col);
	}else if (col > 0 && lin > 0 && prof > 0) {
		if (prof == 1) {
			le_matriz(estr, lin, col);
		}else{
			le_cubo(estr, prof, lin, col);
		}
	} 
}

void imprime_estrutura(void *estr, int prof, int lin, int col) {
	if (col > 0 && lin == 0 && prof == 0) {
		imprime_vetor(estr, lin);
	} else if (col > 0 && lin > 0 && prof==0) {
		imprime_matriz(estr, lin, col);
	}else if (col > 0 && lin > 0 && prof > 0) {
		if (prof == 1) {
			imprime_matriz(estr, lin, col);
		}else{
			imprime_cubo(estr, prof, lin, col);
		}
	} 
}

int main() {

	int lin, col, prof;

	// printf("informe o numero de linhas do vetor: \n");
	// scanf("%d", &lin);
	// int *vetor = aloca_vetor(lin);
	// le_vetor(vetor, lin);
	// imprime_vetor(vetor, lin);

	// printf("informe o numero de linhas e colunas da matriz: \n");
	// scanf("%d %d", &lin, &col);
	// int **matriz = aloca_matriz(lin, col);
	// le_matriz(matriz, lin, col);
	// imprime_matriz(matriz, lin, col);

	// printf("informe a profundidade, o numero de linhas e o numero de colunas do cubo: \n");
	// scanf("%d %d %d", &prof, &lin, &col);
	// int***cubo = aloca_cubo(prof, lin, col);
	// le_cubo(cubo, prof, lin, col);
	// imprime_cubo(cubo, prof, lin, col);

	printf("informe a profundidade, o numero de linhas e o numero de colunas da estrutura: \n");
	scanf("%d %d %d", &prof, &lin, &col);

	void *estrutura = cria_estrutura(prof, lin, col);
	le_estrutura(estrutura, prof, lin, col);
	imprime_estrutura(estrutura, prof, lin, col);

}