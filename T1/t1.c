#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void le_dimensao(int *num_linhas, int *num_colunas) {
	printf("Informe o numero de linhas e colunas da matriz: \n");
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

	for (i=0; i < l; i++) {
		for(j=0; j < c; j++) {
			printf("[%d] ", m[i][j]);	
			if (j == c - 1)
				printf("\n");
		}
	}
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

int verifica_navios_derrubados(int **m, int l, int c) {
	int i, j, validade = 1;

	for (i=0; i<l; i++) {
		for(j=0; j<c; j++){
			if (m[i][j] > 0) {
				validade = 0;
			}
		}
	}

	return validade;
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

int main () {
	
	int opcao, num_linhas_tabuleiro, num_colunas_tabuleiro, i, vet_navios[4], x, y, cont_navios=0, num_navio=0, navio_derrubado=0, direcao=0, navio_inserido=0;
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

				if (matriz[x-1][y-1] > 0) {
					printf("Acertou em um navio!\n");
					num_navio = matriz[x-1][y-1];
					matriz[x-1][y-1] = 0;
					navio_derrubado = 1;

					for (i=0; i<num_colunas_tabuleiro; i++){ //Verifica toda a linha e toda a coluna do ponto, se existe ainda parte do navio
						if (matriz[x-1][i] == num_navio) {
							navio_derrubado = 0;
						}
						if (matriz[i][y-1] == num_navio) {
							navio_derrubado = 0;
						}
					}

					if (navio_derrubado == 1) {
						printf("Derrubou um navio!!!!\n");
					}
				} else{
					printf("Acertou na água!\n");
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

			printf("MATRIZ DO USUÁRIO\n");
			imprime_matriz(matriz1, num_linhas_tabuleiro, num_colunas_tabuleiro);
			printf("-----------------------------------------\nMATRIZ DO COMPUTADOR\n");
			imprime_matriz(matriz2, num_linhas_tabuleiro, num_colunas_tabuleiro);

			cont_navios=0;

			for (i=0; i<vet_navios[0]; i++){
				navio_inserido = 0;
				while(navio_inserido == 0) {
					printf("Informe um ponto(linha-coluna) e uma direcao(1 para vertical e 2 para horizontal) para inserir um navio de DOIS lugares: \n");
					scanf("%d %d %d", &x, &y, &direcao);
					if (x > num_linhas_tabuleiro || y > num_colunas_tabuleiro || x < 1 || y < 1) {
						navio_inserido = 0;
						printf("Posicão ou direção inválida.\n");
					} else {
						if (validade_posicao_navio1(direcao, x-1, y-1, matriz1, num_linhas_tabuleiro-1, num_colunas_tabuleiro-1) == 1) {
							cont_navios++;
							insere_navio_posicao(1, x-1, y-1, matriz1, cont_navios, direcao);
							imprime_matriz(matriz1, num_linhas_tabuleiro, num_colunas_tabuleiro);
							navio_inserido = 1;
						} else {
							printf("Posicão ou direção inválida.\n");
							navio_inserido = 0;
						}
					}
				}
			}
			for (i=0; i<vet_navios[1]; i++){
				navio_inserido = 0;
				while(navio_inserido == 0) {
					printf("Informe um ponto(linha-coluna) e uma direcao(1 para vertical e 2 para horizontal) para inserir um navio de TRÊS lugares: \n");
					scanf("%d %d %d", &x, &y, &direcao);
					if (x > num_linhas_tabuleiro || y > num_colunas_tabuleiro || x < 1 || y < 1) {
						navio_inserido = 0;
						printf("Posicão ou direção inválida.\n");
					} else {
						if (validade_posicao_navio2(direcao, x-1, y-1, matriz1, num_linhas_tabuleiro-1, num_colunas_tabuleiro-1) == 1) {
							cont_navios++;
							insere_navio_posicao(2, x-1, y-1, matriz1, cont_navios, direcao);
							imprime_matriz(matriz1, num_linhas_tabuleiro, num_colunas_tabuleiro);
							navio_inserido = 1;
						} else {
							printf("Posicão ou direção inválida.\n");
							navio_inserido = 0;
						}
					}
				}
			}
			for (i=0; i<vet_navios[2]; i++){
				navio_inserido = 0;
				while(navio_inserido == 0) {
					printf("Informe um ponto(linha-coluna) e uma direcao(1 para vertical e 2 para horizontal) para inserir um navio de QUATRO lugares: \n");
					scanf("%d %d %d", &x, &y, &direcao);
					if (x > num_linhas_tabuleiro || y > num_colunas_tabuleiro || x < 1 || y < 1) {
						navio_inserido = 0;
						printf("Posicão ou direção inválida.\n");
					} else {
						if (validade_posicao_navio3(direcao, x-1, y-1, matriz1, num_linhas_tabuleiro-1, num_colunas_tabuleiro-1) == 1) {
							cont_navios++;
							insere_navio_posicao(3, x-1, y-1, matriz1, cont_navios, direcao);
							imprime_matriz(matriz1, num_linhas_tabuleiro, num_colunas_tabuleiro);
							navio_inserido = 1;
						} else {
							printf("Posicão ou direção inválida.\n");
							navio_inserido = 0;
						}
					}
				}
			}
			for (i=0; i<vet_navios[3]; i++){
				navio_inserido = 0;
				while(navio_inserido == 0) {
					printf("Informe um ponto(linha-coluna) e uma direcao(1 para vertical e 2 para horizontal) para inserir um navio de CINCO lugares: \n");
					scanf("%d %d %d", &x, &y, &direcao);
					if (x > num_linhas_tabuleiro || y > num_colunas_tabuleiro || x < 1 || y < 1) {
						navio_inserido = 0;
						printf("Posicão ou direção inválida.\n");
					} else {
						if (validade_posicao_navio4(direcao, x-1, y-1, matriz1, num_linhas_tabuleiro-1, num_colunas_tabuleiro-1) == 1) {
							cont_navios++;
							insere_navio_posicao(4, x-1, y-1, matriz1, cont_navios, direcao);
							imprime_matriz(matriz1, num_linhas_tabuleiro, num_colunas_tabuleiro);
							navio_inserido = 1;
						} else {
							printf("Posicão ou direção inválida.\n");
							navio_inserido = 0;
						}
					}
				}
			}


		}


	} else {
		printf("Opção inválida.\n");
	}

	return 0;
}