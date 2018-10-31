//ALUNOS: BRUNO FRIZZO E FERNANDO GARCIA
//TURMA: SI/2018-1
//DATA: 27/04/2018
//////////////////////////////////////////////

#include <stdio.h>

int pot(int x, int n){
	int i, p=1;
	for(i=0; i<n;i++) {
		p=p*x;
	}
	return p;
}

int main() {

	int i, j, num[4], cod_enviado[7], cod_alterado[7], vetor_paridade[3], num_bit, qtd_bits, cont=0, num_decimal=0, dif=0;
	int matriz_g[7][4], matriz_h[3][7], matriz_resultado[7][4], matriz_resultado_2[3][7];

	for (i = 0; i < 7; ++i)	{
		cod_enviado[i] = 0;
		cod_alterado[i] = 0;
	}

	for (i=0; i < 3; ++i)	{
		vetor_paridade[i] = 0;
	}

	matriz_g[0][0] = 1;
	matriz_g[0][1] = 1;
	matriz_g[0][2] = 0;
	matriz_g[0][3] = 1;

	matriz_g[1][0] = 1;
	matriz_g[1][1] = 0;
	matriz_g[1][2] = 1;
	matriz_g[1][3] = 1;

	matriz_g[2][0] = 1;
	matriz_g[2][1] = 0;
	matriz_g[2][2] = 0;
	matriz_g[2][3] = 0;

	matriz_g[3][0] = 0;
	matriz_g[3][1] = 1;
	matriz_g[3][2] = 1;
	matriz_g[3][3] = 1;

	matriz_g[4][0] = 0;
	matriz_g[4][1] = 1;
	matriz_g[4][2] = 0;
	matriz_g[4][3] = 0;

	matriz_g[5][0] = 0;
	matriz_g[5][1] = 0;
	matriz_g[5][2] = 1;
	matriz_g[5][3] = 0;

	matriz_g[6][0] = 0;
	matriz_g[6][1] = 0;
	matriz_g[6][2] = 0;
	matriz_g[6][3] = 1;

	matriz_h[0][0] = 1;
	matriz_h[0][1] = 0;
	matriz_h[0][2] = 1;
	matriz_h[0][3] = 0;
	matriz_h[0][4] = 1;
	matriz_h[0][5] = 0;
	matriz_h[0][6] = 1;

	matriz_h[1][0] = 0;
	matriz_h[1][1] = 1;
	matriz_h[1][2] = 1;
	matriz_h[1][3] = 0;
	matriz_h[1][4] = 0;
	matriz_h[1][5] = 1;
	matriz_h[1][6] = 1;

	matriz_h[2][0] = 0;
	matriz_h[2][1] = 0;
	matriz_h[2][2] = 0;
	matriz_h[2][3] = 1;
	matriz_h[2][4] = 1;
	matriz_h[2][5] = 1;
	matriz_h[2][6] = 1;

	for (i=0;i<4;i++){
		printf("informe o %d bit:\n", i+1);
		scanf("%d", &num[i]);	
	}

	//gera matriz com os valores da multiplicacao
	for (i=0;i<4;i++){
		for (j=0;j<7;j++){  
			matriz_resultado[j][i] = matriz_g[j][i] * num[i];
		}	
	}	

	//gera os numero de 7 bits codificado
	for(i=0;i<7;i++){
		for(j=0;j<4;j++){
			cod_enviado[i] += matriz_resultado[i][j];  
		}
	}

	printf("Codigo gerado: \n");
	for (j=0;j<7;j++){
		cod_enviado[j] = cod_enviado[j]%2; 
		cod_alterado[j] = cod_enviado[j]; 
		printf("%d ", cod_enviado[j]);
	}	
	printf("\n");

	printf("informe quantos bits quer alterar: \n");
	scanf("%d", &qtd_bits);

	while(qtd_bits > 3 && qtd_bits < 0) {
		printf("informe quantos bits quer alterar: \n");
		scanf("%d", &qtd_bits);
	}

	//altera os bits selecionados
	while(qtd_bits > cont) {
		printf("informe qual bit alterar\n");
		scanf("%d", &num_bit);

		if(cod_enviado[num_bit-1] == 0){
			cod_alterado[num_bit-1] = 1;
		}else{
			cod_alterado[num_bit-1] = 0;
		}
		cont++;
	}

	printf("Codigo alterado: ");
	for (j=0;j<7;j++){
		printf("%d ", cod_alterado[j]);
	}	
	printf("\n");

	//gera uma matriz  com os valores da multiplicacao
	for (i=0;i<7;i++){
		for (j=0;j<3;j++){  
			matriz_resultado_2[j][i] = matriz_h[j][i] * cod_alterado[i];
		}	
	}

	//GERA O VETOR DE PARIDADE
	for(i=0;i<3;i++){
		for(j=0;j<7;j++){
			vetor_paridade[i] += matriz_resultado_2[i][j];  
		}
	}
	for (i=0;i<3;i++){
		vetor_paridade[i] = vetor_paridade[i]%2;  
	}

	//TRANSFORMA OS BITS GERADOS EM DECIMAL
	j=2;
	for (i=2;i>=0;i--){
		if (vetor_paridade[i] == 1){
			num_decimal += pot(2, j);
		}
		j--;
	}	

	if (cod_alterado[num_decimal-1] == 1) {
		cod_alterado[num_decimal-1] = 0;
	}else{
		cod_alterado[num_decimal-1] = 1;
	}

	for(i=0;i<7;i++){
		if (cod_enviado[i] != cod_alterado[i]){
			dif=1;
		}
	}

	if (dif == 0) {
		printf("Conseguiu corrigir.\n");
	}else{
		printf("Não conseguiu corrigir\n");
		printf("Codigo gerado após tentar corrigir:");
		for (j=0;j<7;j++){
			printf("%d ", cod_alterado[j]);
		}	
		printf("\n");
	}

	printf("Codigo gerado inicialmente:");
	for (j=0;j<7;j++){
		printf("%d ", cod_enviado[j]);
	}	
	printf("\n");

}