#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void le_dimensao(int *linhas, int *colunas) {
	printf("Informe o numero de linhas e colunas da matriz: \n");
	scanf("%d %d", linhas, colunas);
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
			if (m[i][j] == 1) {
				printf("[&] ");
			} else {
				printf("[%d] ", m[i][j]);
			}
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

int validade_direcao_navio1(int direcao, int l, int c, int **m, int linhas, int colunas) {
	int validade=0;

	if(m[l][c] == 0) {
		if (direcao == 1){
			if(l-1 < 1){
				validade = 0;
			} else {
				if (m[l-1][c] == 0) {
					validade = 1;
				}else{
					validade = 0;
				}
			}
		}else if (direcao == 2) {
			if (c-1 < 1) {
				validade = 0;
			}else{
				if (m[l][c-1] == 0) {
					validade = 1;
				}else{
					validade = 0;
				}
			}
		} else if (direcao == 3) {
			if (l+1 > linhas) {
				validade = 0;
			}else{
				if (m[l+1][c] == 0) {
					validade = 1;
				}else{
					validade = 0;
				}
			}
		} else {
			if (c+1 > colunas) {
				validade = 0;
			}else {
				if (m[l][c+1] == 0) {
					validade = 1;
				}else{
					validade = 0;
				}
			}
		}
	} else {
		validade = 0;
	}
	
	return validade;
}

int validade_direcao_navio2(int direcao, int l, int c, int **m, int linhas, int colunas) {
	int validade=0;

	if(m[l][c] == 0) {
		if (direcao == 1){
			if (l-2 < 1) {
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
			if (c-2 < 1) {
				validade = 0;
			}else{
				if (m[l][c-1] == 0) {
					if (m[l][c-2] == 0) {
						validade = 1;
					}else{
						validade = 0;
					}
				}else{
					validade = 0;
				}
			}
		} else if (direcao == 3) {
			if (l+2 > linhas) {
				validade = 0;
			}else{
				if (m[l+1][c] == 0) {
					if (m[l+2][c] == 0) {
						validade = 1;
					}else{
						validade = 0;
					}
				}else{
					validade = 0;
				}
			}
		} else {
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
		} 
	} else{
		validade = 0;
	}

	return validade;
}

int validade_direcao_navio3(int direcao, int l, int c, int **m, int linhas, int colunas) {
	int validade=0;

	if (m[l][c] == 0) {
		if (direcao == 1){
			if (l-3 < 1) {
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
		} else if (direcao == 2) {
			if (c-3 < 1) {
				validade = 0;
			}else{
				if (m[l][c-1] == 0) {
					if (m[l][c-2] == 0) {
						if (m[l][c-3] == 0) {
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
		} else if (direcao == 3) {
			if (l+3 > linhas) {
				validade = 0;
			}else{
				if (m[l+1][c] == 0) {
					if (m[l+2][c] == 0) {
						if (m[l+3][c] == 0) {
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
		}
	}else{
		validade = 0;
	}
	
	return validade;
}

int validade_direcao_navio4(int direcao, int l, int c, int **m, int linhas, int colunas) {
	int validade=0;

	if (m[l][c] == 0) {
		if (direcao == 1){
			if (l-4 < 1) {
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
			if (c-4 < 1) {
				validade = 0;
			}else{
				if (m[l][c-1] == 0) {
					if (m[l][c-2] == 0) {
						if (m[l][c-3] == 0) {
							if (m[l][c-4] == 0) {
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
		} else if (direcao == 3) {
			if (l+4 > linhas) {
				validade = 0;
			}else{
				if (m[l+1][c] == 0) {
					if (m[l+2][c] == 0) {
						if (m[l+3][c] == 0) {
							if (m[l+4][c] == 0) {
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
		}
	}else{
		validade = 0;
	}
	
	return validade;
}

void insere_navio(int tipo_navio, int linhas, int colunas, int **m) {

	int i, l, c, direcao, validade = 0;

	switch (tipo_navio) {

		case 1:
			l = num_rand(linhas)-1;
			c = num_rand(colunas)-1;
			direcao = num_rand(4);

			//Verifica se ponto aleatorio nao esta ocupado por um navio
			validade = validade_direcao_navio1(direcao, l, c, m, linhas-1, colunas-1);
			while(validade == 0) { 
				l = num_rand(linhas)-1;
				c = num_rand(colunas)-1;
				direcao = num_rand(4);
				validade = validade_direcao_navio1(direcao, l, c, m, linhas-1, colunas-1);
			}

			printf("Navio 1. Ponto: %d - %d. Direcao: %d. Validade = %d\n", l+1, c+1, direcao, validade);

			if (direcao == 1) {
				m[l-1][c] = 1;
			}else if (direcao == 2) {
				m[l][c-1] = 1;
			} else if (direcao == 3) {
				m[l+1][c] = 1;
			}else{
				m[l][c+1] = 1;
			}
			m[l][c] = 1;
		break;

		case 2:
			l = num_rand(linhas)-1;
			c = num_rand(colunas)-1;
			direcao = num_rand(4);

			//Verifica se ponto aleatorio nao esta ocupado por um navio
			validade = validade_direcao_navio2(direcao, l, c, m, linhas-1, colunas-1);
			while(validade == 0) { 
				l = num_rand(linhas)-1;
				c = num_rand(colunas)-1;
				direcao = num_rand(4);
				validade = validade_direcao_navio2(direcao, l, c, m, linhas-1, colunas-1);
			} 

			printf("Navio 2. Ponto: %d - %d. Direcao: %d. Validade = %d\n", l+1, c+1, direcao, validade);

			if (direcao == 1) {
				m[l-1][c] = 1;
				m[l-2][c] = 1;
			}else if (direcao == 2) {
				m[l][c-1] = 1;
				m[l][c-2] = 1;
			} else if (direcao == 3) {
				m[l+1][c] = 1;
				m[l+2][c] = 1;
			}else{
				m[l][c+1] = 1;
				m[l][c+2] = 1;
			}
			m[l][c] = 1;
		break;

		case 3:
			l = num_rand(linhas)-1;
			c = num_rand(colunas)-1;
			direcao = num_rand(4);

			//Verifica se ponto aleatorio nao esta ocupado por um navio
			validade = validade_direcao_navio3(direcao, l, c, m, linhas-1, colunas-1);
			while(validade == 0) { 
				l = num_rand(linhas)-1;
				c = num_rand(colunas)-1;
				direcao = num_rand(4);
				validade = validade_direcao_navio3(direcao, l, c, m, linhas-1, colunas-1);
			}

			printf("Navio 3. Ponto: %d - %d. Direcao: %d. Validade = %d\n", l+1, c+1, direcao, validade);


			if (direcao == 1) {
				m[l-1][c] = 1;
				m[l-2][c] = 1;
				m[l-3][c] = 1;
			}else if (direcao == 2) {
				m[l][c-1] = 1;
				m[l][c-2] = 1;
				m[l][c-3] = 1;
			} else if (direcao == 3) {
				m[l+1][c] = 1;
				m[l+2][c] = 1;
				m[l+3][c] = 1;
			}else{
				m[l][c+1] = 1;
				m[l][c+2] = 1;
				m[l][c+3] = 1;
			}
			m[l][c] = 1;
		break;

		case 4:
			l = num_rand(linhas)-1;
			c = num_rand(colunas)-1;
			direcao = num_rand(4);

			//Verifica se ponto aleatorio nao esta ocupado por um navio
			validade = validade_direcao_navio4(direcao, l, c, m, linhas-1, colunas-1);
			while(validade == 0) { 
				l = num_rand(linhas)-1;
				c = num_rand(colunas)-1;
				direcao = num_rand(4);
				validade = validade_direcao_navio4(direcao, l, c, m, linhas-1, colunas-1);
			}

			printf("Navio 4. Ponto: %d - %d. Direcao: %d. Validade = %d\n", l+1, c+1, direcao, validade);

			if (direcao == 1) {
				m[l-1][c] = 1;
				m[l-2][c] = 1;
				m[l-3][c] = 1;
				m[l-4][c] = 1;
			}else if (direcao == 2) {
				m[l][c-1] = 1;
				m[l][c-2] = 1;
				m[l][c-3] = 1;
				m[l][c-4] = 1;
			} else if (direcao == 3) {
				m[l+1][c] = 1;
				m[l+2][c] = 1;
				m[l+3][c] = 1;
				m[l+4][c] = 1;
			}else{
				m[l][c+1] = 1;
				m[l][c+2] = 1;
				m[l][c+3] = 1;
				m[l][c+4] = 1;
			}
			m[l][c] = 1;
		break;

		default:
			printf("erro\n");
			
	} //end switch
}

int main () {
	
	int opcao, linhas_m1, colunas_m1, i, vet_navios[4];

	printf("Digite 1 se deseja jogar sozinho ou 2 se deseja jogar com o computador: \n");
	scanf("%d", &opcao);

	if (opcao == 1) {

	srand(time(NULL));
	le_dimensao(&linhas_m1, &colunas_m1);
	// printf("n linhas = %d\n", linhas_m1);
	// printf("n colunas = %d\n", colunas_m1);
	// printf("numero l gerado = %d\n", num_rand(linhas_m1));
	// printf("numero c gerado = %d\n", num_rand(colunas_m1));


		int **matriz = cria_matriz(linhas_m1, colunas_m1);

		// imprime_matriz(matriz, linhas_m1, colunas_m1);

		le_quant_navios(vet_navios);

		if (verifica_validade_navios(vet_navios, linhas_m1, colunas_m1) == 1) {

			for (i=0; i<vet_navios[0]; i++){
				insere_navio(1, linhas_m1, colunas_m1, matriz);
			}
			for (i=0; i<vet_navios[1]; i++){
				insere_navio(2, linhas_m1, colunas_m1, matriz);
			}
			for (i=0; i<vet_navios[2]; i++){
				insere_navio(3, linhas_m1, colunas_m1, matriz);
			}
			for (i=0; i<vet_navios[3]; i++){
				insere_navio(4, linhas_m1, colunas_m1, matriz);
			}

			imprime_matriz(matriz, linhas_m1, colunas_m1);

		} else {
			printf("Numero de navios informados inválido.\n");
		}

	} else if (opcao == 0) {



	} else {
		printf("Opção inválida.\n");
	}

	return 0;
}