#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

void le_dimensao(int *num_linhas, int *num_colunas) {
	printf("Informe o numero de linhas e colunas do tabuleiro: \n");
	scanf("%d %d", num_linhas, num_colunas);
}

int** cria_matriz(int linhas, int colunas) {
	int i,j;

	int **m = (int**)malloc(linhas * sizeof(int*)); //Aloca um Vetor de Ponteiros

	for (i = 0; i < linhas; i++){ //Percorre as linhas do Vetor de Ponteiros
	   m[i] = (int*) malloc(colunas * sizeof(int)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
	   for (j = 0; j < colunas; j++){ //Percorre o Vetor de Inteiros atual.
	        m[i][j] = 0; //Inicializa com 0.
	   }
	}

	return m; //Retorna o Ponteiro para a Matriz Alocada
}

void imprime_matriz(int **m, int l, int c) {
	int i, j;

	printf("\n");
	for (i=0; i < l; i++) {
		for(j=0; j < c; j++) {
			printf("[%d] ", m[i][j]);	
		}
		printf("\n");
	}
	printf("\n");
}

int num_rand(int limite) {
	return (rand() % limite) + 1;
}

void le_quant_navios(int v[]) {
	printf("Informe a quantidade de navios de 2 lugares: \n");
	scanf("%d", &v[0]);

	printf("Informe a quantidade de navios de 3 lugares: \n");
	scanf("%d", &v[1]);

	printf("Informe a quantidade de navios de 4 lugares: \n");
	scanf("%d", &v[2]);

	printf("Informe a quantidade de navios de 5 lugares: \n");
	scanf("%d", &v[3]);
}

int verifica_validade_navios(int v[], int l, int c) {

	int n_total_espacos = l * c;
	int n_espacos_navios;

	n_espacos_navios = (v[0] * 2) + (v[1] * 3) + (v[2] * 4) + (v[3] * 5);

	if (n_espacos_navios > (0.5*n_total_espacos)) {
		return 0;
	} else {
		return 1;
	}

}

int validade_posicao_navio1(int direcao, int l, int c, int **m, int linhas, int colunas) {
	int validade=0;

	if(m[l][c] == 0) {
		if (direcao == 1){
			if(l-1 < 0){
				validade = 0;
			} else {
				if (m[l-1][c] == 0) {
					validade = 1;
				}else{
					validade = 0;
				}
			}
		}else if (direcao == 2) {
			if (c+1 > colunas) {
				validade = 0;
			}else {
				if (m[l][c+1] == 0) {
					validade = 1;
				}else{
					validade = 0;
				}
			}
		} else {
			validade = 0;
		}
	} else {
		validade = 0;
	}
	
	return validade;
}

int validade_posicao_navio2(int direcao, int l, int c, int **m, int linhas, int colunas) {
	int validade=0;

	if(m[l][c] == 0) {
		if (direcao == 1){
			if (l-2 < 0) {
				validade = 0;
			} else {
				if (m[l-1][c] == 0) {
					if (m[l-2][c] == 0) {
						validade = 1;
					}else{
						validade = 0;
					}
				}else{
					validade = 0;
				}
			}
		} else if (direcao == 2) {
			if (c+2 > colunas) {
				validade = 0;
			}else{
				if (m[l][c+1] == 0) {
					if (m[l][c+2] == 0) {
						validade = 1;
					}else{
						validade = 0;
					}
				}else{
					validade = 0;
				}
			}
		} else {
			validade = 0;
		}
	} else{
		validade = 0;
	}

	return validade;
}

int validade_posicao_navio3(int direcao, int l, int c, int **m, int linhas, int colunas) {
	int validade=0;

	if (m[l][c] == 0) {
		if (direcao == 1){
			if (l-3 < 0) {
				validade = 0;
			}else{
				if (m[l-1][c] == 0) {
					if (m[l-2][c] == 0) {
						if (m[l-3][c] == 0) {
							validade = 1;
						} else {
							validade = 0;
						}
					}else{
						validade = 0;
					}
				}else{
					validade = 0;
				}
			}
		} else if (direcao == 2){
			if (c+3 > colunas) {
				validade = 0;
			} else{
				if (m[l][c+1] == 0) {
					if (m[l][c+2] == 0) {
						if (m[l][c+3] == 0) {
							validade = 1;
						} else {
							validade = 0;
						}
					}else{
						validade = 0;
					}
				}else{
					validade = 0;
				}	
			}
		} else {
			validade = 0;
		}
	}else{
		validade = 0;
	}
	
	return validade;
}

int validade_posicao_navio4(int direcao, int l, int c, int **m, int linhas, int colunas) {
	int validade=0;

	if (m[l][c] == 0) {
		if (direcao == 1){
			if (l-4 < 0) {
				validade = 0;
			}else{
				if (m[l-1][c] == 0) {
					if (m[l-2][c] == 0) {
						if (m[l-3][c] == 0) {
							if (m[l-4][c] == 0) {
								validade = 1;
							}else{
								validade = 0;
							}
						} else {
							validade = 0;
						}
					}else{
						validade = 0;
					}
				}else{
					validade = 0;
				}
			}
		} else if (direcao == 2) {
			if (c+4 > colunas) {
				validade = 0;
			}else{
				if (m[l][c+1] == 0) {
					if (m[l][c+2] == 0) {
						if (m[l][c+3] == 0) {
							if (m[l][c+4] == 0) {
								validade = 1;
							}else{
								validade = 0;
							}
						} else {
							validade = 0;
						}
					}else{
						validade = 0;
					}
				}else{
					validade = 0;
				}
			}
		} else {
			validade = 0;
		}
	}else{
		validade = 0;
	}
	
	return validade;
}

void insere_navio_random(int tipo_navio, int linhas, int colunas, int **m, int num_navio) {

	int l, c, direcao, validade = 0;

	switch (tipo_navio) {

		case 1:
			l = num_rand(linhas)-1;
			c = num_rand(colunas)-1;
			direcao = num_rand(2);

			//Verifica se o ponto gerado nao esta ocupado por um navio e se o navio cabe na direcao gerada
			validade = validade_posicao_navio1(direcao, l, c, m, linhas-1, colunas-1);
			while(validade == 0) { 
				l = num_rand(linhas)-1;
				c = num_rand(colunas)-1;
				direcao = num_rand(2);
				validade = validade_posicao_navio1(direcao, l, c, m, linhas-1, colunas-1);
			}

			//Coloca o navio no tabuleiro de acordo com a direcao gerada
			if (direcao == 1) {
				m[l-1][c] = num_navio;
			}else{
				m[l][c+1] = num_navio;
			}
			m[l][c] = num_navio;
		break;

		case 2:
			l = num_rand(linhas)-1;
			c = num_rand(colunas)-1;
			direcao = num_rand(2);

			//Verifica se o ponto gerado nao esta ocupado por um navio e se o navio cabe na direcao gerada
			validade = validade_posicao_navio2(direcao, l, c, m, linhas-1, colunas-1);
			while(validade == 0) { 
				l = num_rand(linhas)-1;
				c = num_rand(colunas)-1;
				direcao = num_rand(2);
				validade = validade_posicao_navio2(direcao, l, c, m, linhas-1, colunas-1);
			} 

			//Coloca o navio no tabuleiro de acordo com a direcao gerada
			if (direcao == 1) {
				m[l-1][c] = num_navio;
				m[l-2][c] = num_navio;
			}else{
				m[l][c+1] = num_navio;
				m[l][c+2] = num_navio;
			}
			m[l][c] = num_navio;
		break;

		case 3:
			l = num_rand(linhas)-1;
			c = num_rand(colunas)-1;
			direcao = num_rand(2);

			//Verifica se o ponto gerado nao esta ocupado por um navio e se o navio cabe na direcao gerada
			validade = validade_posicao_navio3(direcao, l, c, m, linhas-1, colunas-1);
			while(validade == 0) { 
				l = num_rand(linhas)-1;
				c = num_rand(colunas)-1;
				direcao = num_rand(2);
				validade = validade_posicao_navio3(direcao, l, c, m, linhas-1, colunas-1);
			}

			//Coloca o navio no tabuleiro de acordo com a direcao gerada
			if (direcao == 1) {
				m[l-1][c] = num_navio;
				m[l-2][c] = num_navio;
				m[l-3][c] = num_navio;
			}else{
				m[l][c+1] = num_navio;
				m[l][c+2] = num_navio;
				m[l][c+3] = num_navio;
			}
			m[l][c] = num_navio;
		break;

		case 4:
			l = num_rand(linhas)-1;
			c = num_rand(colunas)-1;
			direcao = num_rand(2);

			//Verifica se o ponto gerado nao esta ocupado por um navio e se o navio cabe na direcao gerada
			validade = validade_posicao_navio4(direcao, l, c, m, linhas-1, colunas-1);
			while(validade == 0) { 
				l = num_rand(linhas)-1;
				c = num_rand(colunas)-1;
				direcao = num_rand(2);
				validade = validade_posicao_navio4(direcao, l, c, m, linhas-1, colunas-1);
			}

			//Coloca o navio no tabuleiro de acordo com a direcao gerada
			if (direcao == 1) {
				m[l-1][c] = num_navio;
				m[l-2][c] = num_navio;
				m[l-3][c] = num_navio;
				m[l-4][c] = num_navio;
			}else{
				m[l][c+1] = num_navio;
				m[l][c+2] = num_navio;
				m[l][c+3] = num_navio;
				m[l][c+4] = num_navio;
			}
			m[l][c] = num_navio;
		break;

		default:
			printf("erro\n");
			
	} //end switch
}

int verifica_navios_derrubados(int **m, int linha, int coluna) {
	int i, j;

	for (i=0; i<linha; i++) {
		for(j=0; j<coluna; j++){
			if (m[i][j] > 0) {
				return 0;
			}
		}
	}

	return 1;
}

void insere_navio_posicao(int tipo_navio, int l, int c, int **m, int num_navio, int direcao) {
	switch (tipo_navio) {

		case 1:
			//Coloca o navio no tabuleiro de acordo com a direcao gerada
			if (direcao == 1) {
				m[l-1][c] = num_navio;
			}else{
				m[l][c+1] = num_navio;
			}
			m[l][c] = num_navio;
		break;

		case 2:
			//Coloca o navio no tabuleiro de acordo com a direcao gerada
			if (direcao == 1) {
				m[l-1][c] = num_navio;
				m[l-2][c] = num_navio;
			}else{
				m[l][c+1] = num_navio;
				m[l][c+2] = num_navio;
			}
			m[l][c] = num_navio;
		break;

		case 3:
			//Coloca o navio no tabuleiro de acordo com a direcao gerada
			if (direcao == 1) {
				m[l-1][c] = num_navio;
				m[l-2][c] = num_navio;
				m[l-3][c] = num_navio;
			}else{
				m[l][c+1] = num_navio;
				m[l][c+2] = num_navio;
				m[l][c+3] = num_navio;
			}
			m[l][c] = num_navio;
		break;

		case 4:
			//Coloca o navio no tabuleiro de acordo com a direcao gerada
			if (direcao == 1) {
				m[l-1][c] = num_navio;
				m[l-2][c] = num_navio;
				m[l-3][c] = num_navio;
				m[l-4][c] = num_navio;
			}else{
				m[l][c+1] = num_navio;
				m[l][c+2] = num_navio;
				m[l][c+3] = num_navio;
				m[l][c+4] = num_navio;
			}
			m[l][c] = num_navio;
		break;

		default:
			printf("erro\n");
			
	} //end switch
} //end funcao

int tiro_dentro_tabuleiro(int x, int y, int num_linhas, int num_colunas) {
	x = x-1;
	y = y-1;

	if (x < 0 || y < 0 || x >= num_linhas || y >= num_colunas) {
		return 0;
	} else{
		return 1;
	}
}

int verifica_acertou_navio(int x, int y, int **m, int num_linhas, int num_colunas) {
	int num_navio=0, navio_derrubado, i;

	if (m[x-1][y-1] > 0) {
		num_navio = m[x-1][y-1];
		m[x-1][y-1] = 0;
		navio_derrubado = 1;

		for (i=0; i<num_colunas; i++){ //Verifica toda a linha e toda a coluna do ponto, se existe ainda parte do navio
			if (m[x-1][i] == num_navio) {
				navio_derrubado = 0;
			}
		}
		for (i=0; i<num_linhas; i++){
			if (m[i][y-1] == num_navio) {
				navio_derrubado = 0;
			}
		}

		if (navio_derrubado == 1) {
			return 2;
		}

		return num_navio;

	} else{
		return 0;
	}
}

bool jogo_acabou(int **m1, int **m2, int num_linhas, int num_colunas) {
	if ((verifica_navios_derrubados(m1, num_linhas, num_colunas) == 1) || (verifica_navios_derrubados(m2, num_linhas, num_colunas) == 1)) {
		return true;
	}else{
		return false;
	}
}

bool validade_direcao_chutada(int direcao, int x, int y, int num_linhas, int num_colunas) {
		if (direcao==1){
			if(tiro_dentro_tabuleiro(x-1, y, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1){ //Verifica se o ponto chutado pelo computador esta dentro do tabuleiro
				x = x-1;
				return true;
			}else{
				return false;
			}
		}else if (direcao==2){
			if (tiro_dentro_tabuleiro(x, y-1, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1){
				y = y-1;
				return true;
			}else{
				return false;
			}
		} else if (direcao==3){
			if (tiro_dentro_tabuleiro(x+1, y, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1){
				x = x+1;
				return true;
			}else{
				return false;
			}
		} else{
			if (tiro_dentro_tabuleiro(x, y+1, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1){
				y = y+1;
				return true;
			}else{
				return false;
			}
		}
}

int main () {
	
	int opcao, num_linhas_tabuleiro, num_colunas_tabuleiro, i, vet_navios[4], x, y, cont_navios=0, num_navio=0, navio_derrubado=0, direcao=0, navio_inserido=0, validade_tiro=0,
		ultimo_x_chutado, ultimo_y_chutado, validade_direcao, num_ultimo_navio_acertado=0;
	bool game_over = false, acertou_ultima=false, mesma_linha, mesma_coluna;
	srand(time(NULL));

	printf("Digite 1 se deseja jogar sozinho ou 2 se deseja jogar com o computador: \n");
	scanf("%d", &opcao);

	if (opcao == 1) {
		le_dimensao(&num_linhas_tabuleiro, &num_colunas_tabuleiro);
		int **matriz = cria_matriz(num_linhas_tabuleiro, num_colunas_tabuleiro);
		le_quant_navios(vet_navios);

		if (verifica_validade_navios(vet_navios, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1) { //Verifica se os navios ocupam menos de 50% do tabuleiro

			for (i=0; i<vet_navios[0]; i++){
				cont_navios++;
				insere_navio_random(1, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz, cont_navios);
			}
			for (i=0; i<vet_navios[1]; i++){
				cont_navios++;
				insere_navio_random(2, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz, cont_navios);
			}
			for (i=0; i<vet_navios[2]; i++){
				cont_navios++;
				insere_navio_random(3, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz, cont_navios);
			}
			for (i=0; i<vet_navios[3]; i++){
				cont_navios++;
				insere_navio_random(4, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz, cont_navios);
			}

			imprime_matriz(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro);

			while(verifica_navios_derrubados(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro) == 0) {
				printf("informe um ponto(linha-coluna): \n");
				scanf("%d %d", &x, &y);

				// if (matriz[x-1][y-1] > 0) {
				// 	printf("Acertou em um navio!\n");
				// 	num_navio = matriz[x-1][y-1];
				// 	matriz[x-1][y-1] = 0;
				// 	navio_derrubado = 1;

				// 	for (i=0; i<num_colunas_tabuleiro; i++){ //Verifica toda a linha e toda a coluna do ponto, se existe ainda parte do navio
				// 		if (matriz[x-1][i] == num_navio) {
				// 			navio_derrubado = 0;
				// 		}
				// 	}
				// 	for (i=0;i<num_linhas_tabuleiro;i++){
				// 		if (matriz[i][y-1] == num_navio) {
				// 			navio_derrubado = 0;
				// 		}
				// 	}

				// 	if (navio_derrubado == 1) {
				// 		printf("Derrubou um navio!!!!\n");
				// 	}
				// } else{
				// 	printf("Acertou na água!\n");
				// }

				validade_tiro = verifica_acertou_navio(x, y, matriz, num_linhas_tabuleiro, num_colunas_tabuleiro);
				if (validade_tiro == 0) {
					printf("Acertou na água.\n\n");
				} else if (validade_tiro == 2) {
					printf("Derrubou um navio!!!!!\n\n");
				} else {
					printf("Acertou em um navio de numero = %d.\n\n", validade_tiro);
				}

				imprime_matriz(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro);
			}


		} else {
			printf("Numero de navios informados inválido.\n");
		}

	} else if (opcao == 2) {

		cont_navios=0;
		le_dimensao(&num_linhas_tabuleiro, &num_colunas_tabuleiro); 
		int **matriz1 = cria_matriz(num_linhas_tabuleiro, num_colunas_tabuleiro);
		int **matriz2 = cria_matriz(num_linhas_tabuleiro, num_colunas_tabuleiro);
		le_quant_navios(vet_navios);

		if (verifica_validade_navios(vet_navios, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1) { //Verifica se os navios ocupam menos de 50% do tabuleiro

			for (i=0; i<vet_navios[0]; i++){
				cont_navios++;
				insere_navio_random(1, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz2, cont_navios);
			}
			for (i=0; i<vet_navios[1]; i++){
				cont_navios++;
				insere_navio_random(2, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz2, cont_navios);
			}
			for (i=0; i<vet_navios[2]; i++){
				cont_navios++;
				insere_navio_random(3, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz2, cont_navios);
			}
			for (i=0; i<vet_navios[3]; i++){
				cont_navios++;
				insere_navio_random(4, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz2, cont_navios);
			}

			cont_navios=0;

			for (i=0; i<vet_navios[0]; i++){
				cont_navios++;
				insere_navio_random(1, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz1, cont_navios);
			}
			for (i=0; i<vet_navios[1]; i++){
				cont_navios++;
				insere_navio_random(2, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz1, cont_navios);
			}
			for (i=0; i<vet_navios[2]; i++){
				cont_navios++;
				insere_navio_random(3, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz1, cont_navios);
			}
			for (i=0; i<vet_navios[3]; i++){
				cont_navios++;
				insere_navio_random(4, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz1, cont_navios);
			}

			printf("MATRIZ DO USUÁRIO\n");
			imprime_matriz(matriz1, num_linhas_tabuleiro, num_colunas_tabuleiro);
			printf("\n-----------------------------------------\nMATRIZ DO COMPUTADOR\n");
			imprime_matriz(matriz2, num_linhas_tabuleiro, num_colunas_tabuleiro);

			while(true) {
				validade_tiro=0;
				acertou_ultima=0;

				printf("VEZ DO USUÁRIO\n\nInforme um ponto(linha-coluna): \n");
				scanf("%d %d", &x, &y);

				while (tiro_dentro_tabuleiro(x-1, y-1, num_linhas_tabuleiro, num_colunas_tabuleiro) == 0) {
					printf("Ṕonto inválido. Informe novamente um ponto(linha-coluna): \n");	
					scanf("%d %d", &x, &y);				
				}

				validade_tiro = verifica_acertou_navio(x, y, matriz2, num_linhas_tabuleiro, num_colunas_tabuleiro);
				if (validade_tiro == 0) {
					printf("Acertou na água.\n\n");
				} else if (validade_tiro == 2) {
					printf("Derrubou um navio!!!!!\n\n");
				} else {
					printf("Acertou em um navio.\n\n");
				}
				
				// printf("MATRIZ DO COMPUTADOR\n");
				// imprime_matriz(matriz2, num_linhas_tabuleiro, num_colunas_tabuleiro);

				printf("VEZ DO COMPUTADOR\n\n");

				// if (!acertou_ultima){
				if (num_ultimo_navio_acertado == 0) {
					x = num_rand(10);
					y = num_rand(10);
					validade_tiro = verifica_acertou_navio(x, y, matriz1, num_linhas_tabuleiro, num_colunas_tabuleiro);
					if (validade_tiro==0) {
						printf("Computador errou\n\n");
						// ultimo_x_chutado = x;
						// ultimo_y_chutado = y;
					}else{
						printf("Computador acertou no navio numero %d\n", validade_tiro);
						// acertou_ultima = true;
						num_ultimo_navio_acertado = validade_tiro;
					}
				} else{
					printf("ACERTOU A ULTIMA\n");
					validade_tiro=0;
					validade_direcao=0;

					while(validade_direcao == 0) {

						direcao = num_rand(4);
						printf("direcao = %d\n", direcao);

						if (validade_direcao_chutada(direcao, x-1, y-1, num_linhas_tabuleiro, num_colunas_tabuleiro)) {
							validade_direcao = 1;
						} else{
							validade_direcao = 0;
						}

						// if (direcao==1){
						// 	if(tiro_dentro_tabuleiro(x-1, y, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1){ //Verifica se o ponto chutado pelo computador esta dentro do tabuleiro
						// 		x = x-1;
						// 		// validade_tiro = verifica_acertou_navio(x, y, matriz1, num_linhas_tabuleiro, num_colunas_tabuleiro); //Verifica se acertou em um navio e se o destruiu
						// 		// if (validade_tiro==0) {
						// 		// 	printf("Computador errou\n");
						// 		// } else if (validade_tiro==2){
						// 		// 	printf("Computador destruiu um navio\n");
						// 		// 	acertou_ultima = false;
						// 		// 	validade_direcao = 1;
						// 		// 	num_ultimo_navio_acertado = 0;
						// 		// }else{
						// 		// 	printf("Computador acertou\n\n");
						// 		// 	acertou_ultima = true;
						// 		// 	mesma_linha = true;
						// 		// 	num_ultimo_navio_acertado = validade_tiro;
						// 		// 	validade_direcao = 1;
						// 		// }
						// 		validade_direcao = 1;
						// 	}else{
						// 		validade_direcao = 0;
						// 	}
						// }else if (direcao==2){
						// 	if (tiro_dentro_tabuleiro(x, y-1, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1){
						// 		y = y-1;
						// 		// validade_tiro = verifica_acertou_navio(x, y, matriz1, num_linhas_tabuleiro, num_colunas_tabuleiro); //Verifica se acertou em um navio e se o destruiu
						// 		// if (validade_tiro==0) {
						// 		// 	printf("Computador errou\n");
						// 		// 	validade_direcao = 0;
						// 		// } else if (validade_tiro==2){
						// 		// 	printf("Computador destruiu um navio\n");
						// 		// 	acertou_ultima = false;
						// 		// 	validade_direcao=1;
						// 		// 	num_ultimo_navio_acertado = 0;
						// 		// }else{
						// 		// 	printf("Computador acertou\n\n");
						// 		// 	acertou_ultima = true;
						// 		// 	mesma_coluna = true;
						// 		// 	num_ultimo_navio_acertado = validade_tiro;
						// 		// 	validade_direcao=1;
						// 		// }
						// 		validade_direcao = 1;
						// 	}else{
						// 		validade_direcao=0;
						// 	}
						// } else if (direcao==3){
						// 	if (tiro_dentro_tabuleiro(x+1, y, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1){
						// 		x = x+1;
						// 		// validade_tiro = verifica_acertou_navio(x, y, matriz1, num_linhas_tabuleiro, num_colunas_tabuleiro); //Verifica se acertou em um navio e se o destruiu
						// 		// if (validade_tiro==0) {
						// 		// 	printf("Computador errou\n");
						// 		// 	validade_direcao = 0;
						// 		// } else if (validade_tiro==2){
						// 		// 	printf("Computador destruiu um navio\n");
						// 		// 	acertou_ultima = false;
						// 		// 	validade_direcao=1;
						// 		// 	num_ultimo_navio_acertado = 0;
						// 		// }else{
						// 		// 	printf("Computador acertou\n\n");
						// 		// 	acertou_ultima = true;
						// 		// 	mesma_linha = true;
						// 		// 	num_ultimo_navio_acertado = validade_tiro;
						// 		// 	validade_direcao=1;
						// 		// }
						// 		validade_direcao = 1;
						// 	}else{
						// 		validade_direcao=0;
						// 	}
						// } else{
						// 	if (tiro_dentro_tabuleiro(x, y+1, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1){
						// 		y = y+1;
						// 		// validade_tiro = verifica_acertou_navio(x, y, matriz1, num_linhas_tabuleiro, num_colunas_tabuleiro); //Verifica se acertou em um navio e se o destruiu
						// 		// if (validade_tiro==0) {
						// 		// 	printf("Computador errou\n");
						// 		// 	validade_direcao = 0;
						// 		// } else if (validade_tiro==2){
						// 		// 	printf("Computador destruiu um navio\n");
						// 		// 	acertou_ultima = false;
						// 		// 	validade_direcao = 1;
						// 		// 	num_ultimo_navio_acertado = 0;
						// 		// }else{
						// 		// 	printf("Computador acertou\n\n");
						// 		// 	acertou_ultima = true;
						// 		// 	mesma_coluna = true;
						// 		// 	num_ultimo_navio_acertado = validade_tiro;
						// 		// 	validade_direcao = 1;
						// 		// }
						// 		validade_direcao = 1;
						// 	}else{
						// 		validade_direcao=0;
						// 	}
						// }

					} //end while
					
					// if (verifica_acertou_navio(x, y, matriz1, num_linhas_tabuleiro, num_colunas_tabuleiro)==1) {
					// 	printf("Computador acertou\n\n");
					// 	acertou_ultima = true;
					// 	// ultimo_x_chutado = x;
					// 	// ultimo_y_chutado = y;
					// }

				}

				printf("MATRIZ DO USUÁRIO\n");
				imprime_matriz(matriz1, num_linhas_tabuleiro, num_colunas_tabuleiro);

				if (jogo_acabou(matriz1, matriz2, num_linhas_tabuleiro, num_colunas_tabuleiro)) {
					break;
				} 

				printf("------------FIM DA RODADA--------------\n");
			} //end while

		}

	} else {
		printf("Opção inválida.\n");
	}

	return 0;
}