#include <stdio.h>
#include <stdlib.h>

int **aloca_matriz(int lin, int col){
	int i;
	int **m = malloc(lin*sizeof(int *));
	for(i=0;i<lin;i++) 
		m[i]=malloc(col*sizeof(int));
	return m;
}

void mostra_matriz(int **m, int lin, int col){
	int i,j;
	for (i=0;i<lin;i++){
		for(j=0;j<col;j++){
			printf("%i\t",m[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

int conta_nao_nulos(int **matriz, int lin, int col){
    int cnt=0, i,j;
    for (i=0;i<lin;i++)
		for(j=0;j<col;j++)
			if (matriz[i][j] != 0)
				cnt++;
	return cnt;
}

int **conv_matriz_n2sp(int **matriz, int lin, int col) {
	int nao_nulos = conta_nao_nulos(matriz, lin, col);
	int i, j, ultima_col_inserida;
	int **m = aloca_matriz(3, nao_nulos+1);

	m[0][0] = lin;
	m[1][0] = col;
	m[2][0] = nao_nulos;

	ultima_col_inserida = 0;

	for(i=0;i<lin;i++) {
		for(j=0;j<col;j++){
			if (matriz[i][j] != 0) {
				m[0][ultima_col_inserida+1] = i;
				m[1][ultima_col_inserida+1] = j; 
				m[2][ultima_col_inserida+1] = matriz[i][j];
				ultima_col_inserida++;
			} 
		}
	}

	return m;
}

int **conv_matriz_sp2n(int **matriz_esparsa, int num, int lin, int col) {
	int i, j, linha, coluna, valor;
	int **m = aloca_matriz(lin, col);

	for (i = 0; i < lin; i++){
		for(j=0;j<col;j++){
			m[i][j] = 0;
		}
	}
	
	for(i=1;i<num+1;i++){
		linha = matriz_esparsa[0][i];
		coluna = matriz_esparsa[1][i];
		valor = matriz_esparsa[2][i];
		m[linha][coluna] = valor;
	}

	return m;

}

int main() {

	int **m1 = aloca_matriz(4, 4);
	int i, nao_nulos;

	m1[2][1] = 2;
	m1[3][0] = 5;

	// printf("matriz 1\n");
	// mostra_matriz(m1, 4, 4);

	int **triplet = conv_matriz_n2sp(m1, 4, 4);

	nao_nulos = conta_nao_nulos(m1, 4, 4);
	printf("matriz 2\n");
	mostra_matriz(triplet, 3, nao_nulos+1);

	///////////////////////////////////////////////
	int **triplet2 = aloca_matriz(3, 3);
	triplet2[0][0] = 4;
	triplet2[1][0] = 4;
	triplet2[2][0] = 2;

	triplet2[0][1] = 0;
	triplet2[1][1] = 2;
	triplet2[2][1] = 8;

	triplet2[0][2] = 2;
	triplet2[1][2] = 0;
	triplet2[2][2] = 10;

	// int **m4 = conv_matriz_sp2n(triplet2, triplet2[2][0], triplet2[0][0], triplet2[1][0]);

	// mostra_matriz(m4, 3, 3);

}