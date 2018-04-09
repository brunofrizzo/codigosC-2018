#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

struct navio_descr {
	int linha;
	int coluna;
	int num;
};

typedef struct navio_descr navio_descr;

void le_dimensao(int *num_linhas, int *num_colunas) {
	printf("Informe o numero de linhas e colunas do tabuleiro: \n");
	scanf("%d %d", num_linhas, num_colunas);
}

int** cria_matriz(int linhas, int colunas) {
	int i,j;

	int **m = (int**)malloc(linhas * sizeof(int*));

	for (i = 0; i < linhas; i++){ 
	   m[i] = (int*) malloc(colunas * sizeof(int)); 
	   for (j = 0; j < colunas; j++){
	        m[i][j] = 0; 
	   }
	}

	return m; 
}

void imprime_matriz(int **m, int l, int c) {
	int i, j;

	printf("\n");
	for (i=0; i<c; i++) {
		if (i==0) {
			printf("  %d     ", i+1);
		}else if(i>8) {
			printf("%d    ", i+1);
		}else{
			printf("%d     ", i+1);
		}
	}
	printf("\n");
	for (i=0; i < l; i++) {
		for(j=0; j < c; j++) {
			if (m[i][j] >= 10 || m[i][j] < 0) {
				printf("[%d ] ", m[i][j]);	
			}else{
				printf("[ %d ] ", m[i][j]);	
			}
		}
		printf("%d ", i+1);
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

bool posicoes_ao_redor_livre(int l, int c, int **m, int num_linhas_tabuleiro, int num_colunas_tabuleiro, int direcao, int tipo_navio) {
	int i;

	if (direcao == 1) {
		if ((l-tipo_navio-1 >= 0) && (l+1 <= num_linhas_tabuleiro)) { //Navio no meio do tabuleiro
			if (m[l-tipo_navio-1][c] == 0 && m[l+1][c] == 0) { //Verifica as extremidades
				for (i=0; i<tipo_navio+1; i++) {
					if (c-1 >= 0) {
						if (m[l-i][c-1] != 0) {
							return false;
						}	
					}
					if (c+1 <= num_colunas_tabuleiro) {
						if (m[l-i][c+1] != 0) {
							return false;
						}		
					}
				}
			}else{
				return false;
			}		
		} else if ((l-tipo_navio-1 >= 0) && (l == num_linhas_tabuleiro)) { //Navio enconstando em baixo
			if (m[l-tipo_navio-1][c] == 0) { //Verifica a extremidade
				for (i=0; i<tipo_navio+1; i++) {
					if (c-1 >= 0) {
						if (m[l-i][c-1] != 0) {
							return false;
						}	
					}
					if (c+1 <= num_colunas_tabuleiro) {
						if (m[l-i][c+1] != 0) {
							return false;
						}		
					}
				}
			}else{
				return false;
			}
		} else if ((l-tipo_navio == 0) && (l+1 <= num_linhas_tabuleiro)) { //Navio encostando em cima
			if (m[l+1][c] == 0) { //Verifica a extremidade
				for (i=0; i<tipo_navio+1; i++) {
					if (c-1 >= 0) {
						if (m[l-i][c-1] != 0) {
							return false;
						}	
					}
					if (c+1 <= num_colunas_tabuleiro) {
						if (m[l-i][c+1] != 0) {
							return false;
						}		
					}
				}
			}else{
				return false;
			}
		}else{
			return false;
		}
	}else{ //direcao == 2
		if ((c-1 >= 0) && (c+tipo_navio+1 <= num_colunas_tabuleiro)) { //Navio no meio do tabuleiro
			if (m[l][c-1] == 0 && m[l][c+tipo_navio+1] == 0) { //Verifica as extremidades
				for (i=0; i<tipo_navio+1; i++) {
					if (l-1 >= 0) {
						if (m[l-1][c+i] != 0) {
							return false;
						}		
					}
					if (l+1 <= num_linhas_tabuleiro) {
						if (m[l+1][c+i] != 0) {
							return false;
						}	
					}
				}
			}else{
				return false;
			}
		}else if ((c == 0) && (c+tipo_navio+1 <= num_colunas_tabuleiro)) { //Navio encostando na esquerda
			if (m[l][c+tipo_navio+1] == 0) { //Verifica a extremidada
				for (i=0; i<tipo_navio+1; i++) {
					if (l-1 >= 0) {
						if (m[l-1][c+i] != 0) {
							return false;
						}		
					}
					if (l+1 <= num_linhas_tabuleiro) {
						if (m[l+1][c+i] != 0) {
							return false;
						}	
					}
				}
			}else{
				return false;
			}
		}else if ((c-1 >= 0) && (c+tipo_navio == num_colunas_tabuleiro)) { //Navio encostando na direita
			if (m[l][c-1] == 0) { //Verifica a extremidada
				for (i=0; i<tipo_navio+1; i++) {
					if (l-1 >= 0) {
						if (m[l-1][c+i] != 0) {
							return false;
						}		
					}
					if (l+1 <= num_linhas_tabuleiro) {
						if (m[l+1][c+i] != 0) {
							return false;
						}	
					}
				}
			}else{
				return false;
			}
		}else{
			return false;
		}
	}	

	return true;
	
}

//Verifica se navio pode ser colocado na posicao de acordo com a direcao chutada
int verifica_validade_posicao_navio(int tipo_navio, int num_linhas_tabuleiro, int num_colunas_tabuleiro, int **m, int direcao, int l, int c){
	int i;
	if (posicoes_ao_redor_livre(l, c, m, num_linhas_tabuleiro, num_colunas_tabuleiro, direcao, tipo_navio)) {
		if (direcao == 1) {
			if (l-tipo_navio < 0) {
				return 0;
			}else{
				for (i=0; i<tipo_navio+1; i++) {
					if (m[l-i][c] != 0) {
						return 0;
					}
				}
			}
		}else{ 
			if (c+tipo_navio > num_linhas_tabuleiro) {
				return 0;
			}else{
				for (i=0; i<tipo_navio+1; i++) {
					if (m[l][c+i] != 0) {
						return 0;
					}
				}
			}
		}
	}else{
		return 0;
	}

	return 1;
}

//Insere um navio em uma posição aleatoria
void insere_navio_random(int tipo_navio, int linhas, int colunas, int **m, int num_navio) {

	int l, c, direcao, validade = 0;

	switch (tipo_navio) {

		case 1:
			l = num_rand(linhas)-1;
			c = num_rand(colunas)-1;
			direcao = num_rand(2);

			//Verifica se o ponto gerado nao esta ocupado por um navio e se o navio cabe na direcao gerada
			validade = verifica_validade_posicao_navio(tipo_navio, linhas-1, colunas-1, m, direcao, l, c);
			while(validade == 0) { 
				l = num_rand(linhas)-1;
				c = num_rand(colunas)-1;
				direcao = num_rand(2);
				validade = verifica_validade_posicao_navio(tipo_navio, linhas-1, colunas-1, m, direcao, l, c);
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
			validade = verifica_validade_posicao_navio(tipo_navio, linhas-1, colunas-1, m, direcao, l, c);
			while(validade == 0) { 
				l = num_rand(linhas)-1;
				c = num_rand(colunas)-1;
				direcao = num_rand(2);
				validade = verifica_validade_posicao_navio(tipo_navio, linhas-1, colunas-1, m, direcao, l, c);
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
			validade = verifica_validade_posicao_navio(tipo_navio, linhas-1, colunas-1, m, direcao, l, c);
			while(validade == 0) { 
				l = num_rand(linhas)-1;
				c = num_rand(colunas)-1;
				direcao = num_rand(2);
				validade = verifica_validade_posicao_navio(tipo_navio, linhas-1, colunas-1, m, direcao, l, c);
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
			validade = verifica_validade_posicao_navio(tipo_navio, linhas-1, colunas-1, m, direcao, l, c);
			while(validade == 0) { 
				l = num_rand(linhas)-1;
				c = num_rand(colunas)-1;
				direcao = num_rand(2);
				validade = verifica_validade_posicao_navio(tipo_navio, linhas-1, colunas-1, m, direcao, l, c);
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

//Verifica se todos navios foram derrubados
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

//Verifica se tiro foi dentro do tabuleiro
int tiro_dentro_tabuleiro(int x, int y, int num_linhas, int num_colunas) {

	if (x < 1 || y < 1 || x > num_linhas || y > num_colunas) {
		return 0;
	} else{
		return 1;
	}
}

//Verifica se o tiro acertou algum navio, seta a posicao do tabuleiro como -1 e retorna o numero do navio atingido
int verifica_acertou_navio(int x, int y, int **m, int num_linhas, int num_colunas) {
	//Retorno
	//0 se nao acertou navio
	//-1 se derrubou um navio
	//-2 se acertou em lugar onde havia um navio
	//>0 se acertou algum navio
	//Matriz
	//Se acertou um navio, seta posição como -1
	//Se acertou na água, seta como -2
	int num_navio=0, navio_derrubado, i;

	if (m[x-1][y-1] > 0) {
		num_navio = m[x-1][y-1];
		m[x-1][y-1] = -1;
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
			return -1;
		}

		return num_navio;

	} else if(m[x-1][y-1] == -1){
		return -2;
	} else{
		m[x-1][y-1] = -2;
		return 0;
	}
}

int jogo_acabou(int **m1, int **m2, int num_linhas, int num_colunas) {
	if (verifica_navios_derrubados(m1, num_linhas, num_colunas) == 1) {
		return 1;
	}else if (verifica_navios_derrubados(m2, num_linhas, num_colunas) == 1){
		return 2;
	} else{
		return 0;
	}
}

bool validade_direcao_chutada(int direcao, int x, int y, int num_linhas_tabuleiro, int num_colunas_tabuleiro, int **m) {
		if (direcao==1){
			if(tiro_dentro_tabuleiro(x, y+1, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1){ //Verifica se o ponto chutado pelo computador esta dentro do tabuleiro
				if (m[x-1][y] >= 0) {
					return true;
				} else {
					return false;
				} 
			}else{
				return false;
			}
		}else if (direcao==2){
			if (tiro_dentro_tabuleiro(x+1, y, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1){
				if (m[x][y-1] >= 0) {
					return true;
				} else {
					return false;
				} 
			}else{
				return false;
			}
		} else if (direcao==3){
			if (tiro_dentro_tabuleiro(x+2, y+1, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1){
				if (m[x+1][y] >= 0) {
					return true;
				} else {
					return false;
				} 
			}else{
				return false;
			}
		} else{
			if (tiro_dentro_tabuleiro(x+1, y+2, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1){
				if (m[x][y+1] >= 0) {
					return true;
				} else {
					return false;
				} 
			}else{
				return false;
			}
		}
}

bool ja_atirou_na_posicao(int x, int y, int **m, int num_linhas_tabuleiro, int num_colunas_tabuleiro) {
	if (tiro_dentro_tabuleiro(x, y, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1) {
		if (m[x-1][y-1] == -2 || m[x-1][y-1] == -1) {
			return true;
		}else{
			return false;
		}		
	}
}

void resetar_jogada_computador(bool *mesma_linha, bool *mesma_coluna, bool *acertou_direcao, bool *inverter_sentido) {
	*mesma_linha = false;
	*mesma_coluna = false;
	*acertou_direcao = false;
	*inverter_sentido = false;
}

void jogada_computador(int **matriz, int num_linhas_tabuleiro, int num_colunas_tabuleiro, int *linha_random, int *coluna_random, int *validade_tiro,
	int *ultima_linha_chutada, int *ultima_coluna_chutada, navio_descr *navio_acertado, bool *posicao_ja_chutada, bool *acertou_direcao, int *direcao,
		bool *mesma_linha, bool *mesma_coluna, bool *inverter_sentido) {

	if (*acertou_direcao == true) {
		if (*mesma_linha == true) {
			if (*inverter_sentido == true) {
				if(*ultima_coluna_chutada < (navio_acertado->coluna+1)) {
					//Ultimo chute foi para esquerda
					if (tiro_dentro_tabuleiro(navio_acertado->linha+1, navio_acertado->coluna+2, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1) {
						*validade_tiro = verifica_acertou_navio(navio_acertado->linha+1, navio_acertado->coluna+2, matriz, num_linhas_tabuleiro,
							num_colunas_tabuleiro);
						*ultima_coluna_chutada = navio_acertado->coluna+2;

						if (*validade_tiro == 0) {
							printf("Computador acertou na agua\n");
							*inverter_sentido = false;
							*mesma_linha = false;
							*mesma_coluna = true;
							*ultima_coluna_chutada = navio_acertado->coluna;
							*acertou_direcao = false;
						} else if(*validade_tiro == -1) {
							printf("Computador derrubou um navio.\n");
							navio_acertado->num = 0;
							resetar_jogada_computador(mesma_linha, mesma_coluna, acertou_direcao, inverter_sentido);
						}else if (*validade_tiro == -2) {
							*inverter_sentido = false;
							jogada_computador(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro, linha_random, coluna_random, validade_tiro, 
							ultima_linha_chutada, ultima_coluna_chutada, navio_acertado, posicao_ja_chutada, acertou_direcao, direcao, mesma_linha,
							mesma_coluna, inverter_sentido);
						}else{
							printf("Computador acertou\n");	
							navio_acertado->num = *validade_tiro;
							*inverter_sentido = false;
						}

					}else{
						*ultima_coluna_chutada = navio_acertado->coluna;
						*acertou_direcao = false;
					}
				} else if(*ultima_coluna_chutada > (navio_acertado->coluna+1)) {
					//Ultimo chute foi para direita
					if (tiro_dentro_tabuleiro(navio_acertado->linha+1, navio_acertado->coluna, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1) {
						*validade_tiro = verifica_acertou_navio(navio_acertado->linha+1, navio_acertado->coluna, matriz, num_linhas_tabuleiro,
							num_colunas_tabuleiro);
						*ultima_coluna_chutada = navio_acertado->coluna;

						if (*validade_tiro == 0) {
							printf("Computador acertou na agua\n");
							*inverter_sentido = false;
							*mesma_linha = false;
							*mesma_coluna = true;
							*ultima_coluna_chutada = navio_acertado->coluna;
							*acertou_direcao = false;
						} else if(*validade_tiro == -1) {
							printf("Computador derrubou um navio.\n");
							navio_acertado->num = 0;
							resetar_jogada_computador(mesma_linha, mesma_coluna, acertou_direcao, inverter_sentido);
						}else if (*validade_tiro == -2) {
							*inverter_sentido = false;
							jogada_computador(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro, linha_random, coluna_random, validade_tiro, 
							ultima_linha_chutada, ultima_coluna_chutada, navio_acertado, posicao_ja_chutada, acertou_direcao, direcao, mesma_linha,
							mesma_coluna, inverter_sentido);
						}else{
							printf("Computador acertou\n");
							navio_acertado->num = *validade_tiro;
							*inverter_sentido = false;
						}

					}else{
						*ultima_coluna_chutada = navio_acertado->coluna;
						*acertou_direcao = false;		
					}
				}			
			} else{ //inverter_sentido = false
				if (*ultima_coluna_chutada < (navio_acertado->coluna+1)) {
					//Computador começou chutando para esquerda
					if (tiro_dentro_tabuleiro(*ultima_linha_chutada, *ultima_coluna_chutada-1, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1) {
						if (ja_atirou_na_posicao(*ultima_linha_chutada, *ultima_coluna_chutada-1, matriz, num_linhas_tabuleiro, num_colunas_tabuleiro)) {
							printf("ja atirou na posicao\n");
							*ultima_coluna_chutada = *ultima_coluna_chutada - 1;

							jogada_computador(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro, linha_random, coluna_random, validade_tiro, 
							ultima_linha_chutada, ultima_coluna_chutada, navio_acertado, posicao_ja_chutada, acertou_direcao, direcao, mesma_linha,
							mesma_coluna, inverter_sentido);
						}else{
							*validade_tiro = verifica_acertou_navio(*ultima_linha_chutada, *ultima_coluna_chutada-1, matriz, num_linhas_tabuleiro,
								num_colunas_tabuleiro);
							*ultima_coluna_chutada = *ultima_coluna_chutada - 1;

							if (*validade_tiro == 0) {
								printf("Computador acertou na agua\n");
								*inverter_sentido = true;
							} else if(*validade_tiro == -1) {
								printf("Computador derrubou um navio.\n");
								navio_acertado->num = 0;
								resetar_jogada_computador(mesma_linha, mesma_coluna, acertou_direcao, inverter_sentido);
							}else if (*validade_tiro == -2) {
								*inverter_sentido = false;
								jogada_computador(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro, linha_random, coluna_random, validade_tiro, 
								ultima_linha_chutada, ultima_coluna_chutada, navio_acertado, posicao_ja_chutada, acertou_direcao, direcao, mesma_linha,
								mesma_coluna, inverter_sentido);
							}else{
								printf("Computador acertou\n");
								navio_acertado->num = *validade_tiro;
							}
						}
					}else{
						*inverter_sentido = true;
						jogada_computador(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro, linha_random, coluna_random, validade_tiro, 
						ultima_linha_chutada, ultima_coluna_chutada, navio_acertado, posicao_ja_chutada, acertou_direcao, direcao, mesma_linha,
						mesma_coluna, inverter_sentido);
					}
				} else if(*ultima_coluna_chutada > (navio_acertado->coluna+1)){
					//Computador começou chutando pra direita
					if (tiro_dentro_tabuleiro(*ultima_linha_chutada, *ultima_coluna_chutada+1, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1) {
						if (ja_atirou_na_posicao(*ultima_linha_chutada, *ultima_coluna_chutada+1, matriz, num_linhas_tabuleiro, num_colunas_tabuleiro)) {
							*ultima_coluna_chutada = *ultima_coluna_chutada + 1;

							jogada_computador(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro, linha_random, coluna_random, validade_tiro, 
							ultima_linha_chutada, ultima_coluna_chutada, navio_acertado, posicao_ja_chutada, acertou_direcao, direcao, mesma_linha,
							mesma_coluna, inverter_sentido);
						}else{
							*validade_tiro = verifica_acertou_navio(*ultima_linha_chutada, *ultima_coluna_chutada+1, matriz, num_linhas_tabuleiro,
								num_colunas_tabuleiro);
							*ultima_coluna_chutada = *ultima_coluna_chutada + 1;

							if (*validade_tiro == 0) {
								printf("Computador acertou na agua\n");
								*inverter_sentido = true;
							} else if(*validade_tiro == -1) {
								printf("Computador derrubou um navio.\n");
								navio_acertado->num = 0;
								resetar_jogada_computador(mesma_linha, mesma_coluna, acertou_direcao, inverter_sentido);
							}else if (*validade_tiro == -2) {
								*inverter_sentido = false;
								jogada_computador(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro, linha_random, coluna_random, validade_tiro, 
								ultima_linha_chutada, ultima_coluna_chutada, navio_acertado, posicao_ja_chutada, acertou_direcao, direcao, mesma_linha,
								mesma_coluna, inverter_sentido);
							}else{
								printf("Computador acertou\n");	
								navio_acertado->num = *validade_tiro;
							}

						}
					}else{
						*inverter_sentido = true;
						jogada_computador(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro, linha_random, coluna_random, validade_tiro, 
						ultima_linha_chutada, ultima_coluna_chutada, navio_acertado, posicao_ja_chutada, acertou_direcao, direcao, mesma_linha,
						mesma_coluna, inverter_sentido);
					}

				}
			}//end if inverter sentido
		}else if (*mesma_coluna == true) {
			if (*inverter_sentido == true) {
				if(*ultima_linha_chutada < (navio_acertado->linha+1)) {
					//Ultimo chute foi para cima
					if (tiro_dentro_tabuleiro(navio_acertado->linha+2, navio_acertado->coluna+1, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1) {
						*validade_tiro = verifica_acertou_navio(navio_acertado->linha+2, navio_acertado->coluna+1, matriz, num_linhas_tabuleiro,
							num_colunas_tabuleiro);
						*ultima_linha_chutada = navio_acertado->linha+2;

						if (*validade_tiro == 0) {
							printf("Computador acertou na agua\n");
							*inverter_sentido = false;
							*mesma_linha = true;
							*mesma_coluna = false;
							*ultima_linha_chutada = navio_acertado->linha;
							*acertou_direcao = false;
						} else if(*validade_tiro == -1) {
							printf("Computador derrubou um navio!!!\n");
							navio_acertado->num = 0;
							resetar_jogada_computador(mesma_linha, mesma_coluna, acertou_direcao, inverter_sentido);
						} else if (*validade_tiro == -2) {
							*inverter_sentido = false;
							jogada_computador(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro, linha_random, coluna_random, validade_tiro, 
							ultima_linha_chutada, ultima_coluna_chutada, navio_acertado, posicao_ja_chutada, acertou_direcao, direcao, mesma_linha,
							mesma_coluna, inverter_sentido);
						} else{
							printf("Computador acertou\n");	
							navio_acertado->num = *validade_tiro;
							*inverter_sentido = false;
						}
					}else{
						*ultima_linha_chutada = navio_acertado->linha;	
						*acertou_direcao = false;
					}
				} else if (*ultima_linha_chutada > (navio_acertado->linha+1)) {
					//Ultimo chute foi para baixo
					if (tiro_dentro_tabuleiro(navio_acertado->linha, navio_acertado->coluna+1, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1) {
						*validade_tiro = verifica_acertou_navio(navio_acertado->linha, navio_acertado->coluna+1, matriz, num_linhas_tabuleiro,
							num_colunas_tabuleiro);
						*ultima_linha_chutada = navio_acertado->linha;

						if (*validade_tiro == 0) {
							printf("Computador acertou na agua\n");
							*inverter_sentido = false;
							*mesma_linha = true;
							*mesma_coluna = false;
							*ultima_linha_chutada = navio_acertado->linha;
							*acertou_direcao = false;
						} else if(*validade_tiro == -1) {
							printf("Computador derrubou um navio!!!\n");
							navio_acertado->num = 0;
							resetar_jogada_computador(mesma_linha, mesma_coluna, acertou_direcao, inverter_sentido);
						} else if (*validade_tiro == -2) {
							printf("Acertou em um lugar onde havia navio\n");
							*inverter_sentido = false;
							jogada_computador(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro, linha_random, coluna_random, validade_tiro, 
							ultima_linha_chutada, ultima_coluna_chutada, navio_acertado, posicao_ja_chutada, acertou_direcao, direcao, mesma_linha,
							mesma_coluna, inverter_sentido);
						} else{
							printf("Computador acertou\n");
							navio_acertado->num = *validade_tiro;
							*inverter_sentido = false;
						}
					}else{
						*ultima_linha_chutada = navio_acertado->linha;
						*acertou_direcao = false;
					}
				}	
			} else{
				if (*ultima_linha_chutada < (navio_acertado->linha+1)) {
					//Computador começou chutando pra cima
					if (tiro_dentro_tabuleiro(*ultima_linha_chutada-1, *ultima_coluna_chutada, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1) {
						if (ja_atirou_na_posicao(*ultima_linha_chutada-1, *ultima_coluna_chutada, matriz, num_linhas_tabuleiro, num_colunas_tabuleiro)) {
							*ultima_linha_chutada = *ultima_linha_chutada - 1;

							jogada_computador(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro, linha_random, coluna_random, validade_tiro, 
							ultima_linha_chutada, ultima_coluna_chutada, navio_acertado, posicao_ja_chutada, acertou_direcao, direcao, mesma_linha,
							mesma_coluna, inverter_sentido);
						}else{
							*validade_tiro = verifica_acertou_navio(*ultima_linha_chutada-1, *ultima_coluna_chutada, matriz, num_linhas_tabuleiro,
								num_colunas_tabuleiro);
							*ultima_linha_chutada = *ultima_linha_chutada - 1;

							if (*validade_tiro == 0) {
								printf("Computador acertou na agua\n");
								*inverter_sentido = true;
							} else if(*validade_tiro == -1) {
								printf("Computador derrubou um navio.\n");
								navio_acertado->num = 0;
								resetar_jogada_computador(mesma_linha, mesma_coluna, acertou_direcao, inverter_sentido);
							} else if (*validade_tiro == -2) {
								*inverter_sentido = false;
								jogada_computador(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro, linha_random, coluna_random, validade_tiro, 
								ultima_linha_chutada, ultima_coluna_chutada, navio_acertado, posicao_ja_chutada, acertou_direcao, direcao, mesma_linha,
								mesma_coluna, inverter_sentido);
							} else{
								printf("Computador acertou\n");
								navio_acertado->num = *validade_tiro;
							}	
						}
				
					}else{
						*inverter_sentido = true;
						jogada_computador(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro, linha_random, coluna_random, validade_tiro, 
						ultima_linha_chutada, ultima_coluna_chutada, navio_acertado, posicao_ja_chutada, acertou_direcao, direcao, mesma_linha,
						mesma_coluna, inverter_sentido);
					}
				} else if(*ultima_linha_chutada > (navio_acertado->linha+1)){
					//Computador começou chutando pra baixo
					if (tiro_dentro_tabuleiro(*ultima_linha_chutada+1, *ultima_coluna_chutada, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1) {
						if (ja_atirou_na_posicao(*ultima_linha_chutada+1, *ultima_coluna_chutada, matriz, num_linhas_tabuleiro, num_colunas_tabuleiro)) {
							*ultima_linha_chutada = *ultima_linha_chutada + 1;

							jogada_computador(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro, linha_random, coluna_random, validade_tiro, 
							ultima_linha_chutada, ultima_coluna_chutada, navio_acertado, posicao_ja_chutada, acertou_direcao, direcao, mesma_linha,
							mesma_coluna, inverter_sentido);

						} else{
							*validade_tiro = verifica_acertou_navio(*ultima_linha_chutada+1, *ultima_coluna_chutada, matriz, num_linhas_tabuleiro,
								num_colunas_tabuleiro);
							*ultima_linha_chutada = *ultima_linha_chutada + 1;

							if (*validade_tiro == 0) {
								printf("Computador acertou na agua\n");
								*inverter_sentido = true;
							} else if(*validade_tiro == -1) {
								printf("Computador derrubou um navio.\n");
								navio_acertado->num = 0;
								resetar_jogada_computador(mesma_linha, mesma_coluna, acertou_direcao, inverter_sentido);
							}else if (*validade_tiro == -2) {
								*inverter_sentido = false;
								jogada_computador(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro, linha_random, coluna_random, validade_tiro, 
								ultima_linha_chutada, ultima_coluna_chutada, navio_acertado, posicao_ja_chutada, acertou_direcao, direcao, mesma_linha,
								mesma_coluna, inverter_sentido);
							}else{
								printf("Computador acertou\n");	
								navio_acertado->num = *validade_tiro;
							}
						}
					}else{
						*inverter_sentido = true;
						jogada_computador(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro, linha_random, coluna_random, validade_tiro, 
						ultima_linha_chutada, ultima_coluna_chutada, navio_acertado, posicao_ja_chutada, acertou_direcao, direcao, mesma_linha,
						mesma_coluna, inverter_sentido);
					}
				}
			} //end if inverter sentido
		} //end if mesma coluna
	}else{
		*posicao_ja_chutada = true;
		while (*posicao_ja_chutada) {
			*linha_random = num_rand(10);
			*coluna_random = num_rand(10);
			*posicao_ja_chutada = ja_atirou_na_posicao(*linha_random, *coluna_random, matriz, num_linhas_tabuleiro, num_colunas_tabuleiro);	
		}
		*ultima_linha_chutada = *linha_random;
		*ultima_coluna_chutada = *coluna_random;
		*validade_tiro = verifica_acertou_navio(*linha_random, *coluna_random, matriz, num_linhas_tabuleiro, num_colunas_tabuleiro);
		if (*validade_tiro==0) {
			printf("Computador errou\n\n");
		}else if(*validade_tiro==-1){
			printf("Computador derrubou um navio.\n\n");
			navio_acertado->num = 0;
		}else{
			printf("Computador acertou\n\n");
				navio_acertado->num = *validade_tiro; 
				navio_acertado->linha = *linha_random-1;
				navio_acertado->coluna = *coluna_random-1;
		}
	}

}

void sorteia_direcao(int *direcao, int **matriz, int num_linhas_tabuleiro, int num_colunas_tabuleiro, int linha_random, int coluna_random) {

	*direcao = num_rand(4);

	while(!validade_direcao_chutada(*direcao, linha_random-1, coluna_random-1, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz)) {
		*direcao = num_rand(4);
	}
}

void atira_direcao_chutada(int **matriz, int num_linhas_tabuleiro, int num_colunas_tabuleiro, int linha_random, int coluna_random,
 	int *validade_tiro, navio_descr *navio_acertado, bool *acertou_direcao, bool *mesma_coluna, bool *mesma_linha,
 	 	int *ultima_linha_chutada, int *ultima_coluna_chutada, bool *inverter_sentido) {

	*validade_tiro = verifica_acertou_navio(linha_random, coluna_random, matriz, num_linhas_tabuleiro, num_colunas_tabuleiro);
	if (*validade_tiro > 0) {
		printf("Computador acertou\n\n");
		*acertou_direcao = true;
	}else if(*validade_tiro == -1){
		printf("Computador derrubou um navio\n\n");
		resetar_jogada_computador(mesma_linha, mesma_coluna, acertou_direcao, inverter_sentido);
		navio_acertado->num = 0;
	}else{
		printf("Computador errou\n\n");
	}
}

void jogada_computador_com_direcao_chutada(int **matriz, int num_linhas_tabuleiro, int num_colunas_tabuleiro, int linha_random, int coluna_random,
 	int *validade_tiro, int direcao, navio_descr *navio_acertado, bool *acertou_direcao, bool *mesma_coluna, bool *mesma_linha,
 	 	int *ultima_linha_chutada, int *ultima_coluna_chutada, bool *inverter_sentido) {

	if (direcao==1){
		atira_direcao_chutada(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro, linha_random-1, coluna_random, validade_tiro, navio_acertado,
			acertou_direcao, mesma_linha, mesma_coluna, ultima_linha_chutada, ultima_coluna_chutada, inverter_sentido);
		*mesma_coluna = true;
		*mesma_linha = false;
		*ultima_linha_chutada = linha_random-1;
		*ultima_coluna_chutada = coluna_random;	
	}else if(direcao==2){
		atira_direcao_chutada(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro, linha_random, coluna_random-1, validade_tiro, navio_acertado,
			acertou_direcao, mesma_linha, mesma_coluna, ultima_linha_chutada, ultima_coluna_chutada, inverter_sentido);
		*mesma_linha = true;
		*mesma_coluna = false;	
		*ultima_linha_chutada = linha_random;
		*ultima_coluna_chutada = coluna_random-1;	
	}else if(direcao==3){
		atira_direcao_chutada(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro, linha_random+1, coluna_random, validade_tiro, navio_acertado,
			acertou_direcao, mesma_linha, mesma_coluna, ultima_linha_chutada, ultima_coluna_chutada, inverter_sentido);
		*mesma_coluna = true;
		*mesma_linha = false;
		*ultima_linha_chutada = linha_random+1;
		*ultima_coluna_chutada = coluna_random;	
	}else{
		atira_direcao_chutada(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro, linha_random, coluna_random+1, validade_tiro, navio_acertado,
			acertou_direcao, mesma_linha, mesma_coluna, ultima_linha_chutada, ultima_coluna_chutada, inverter_sentido);
		*mesma_linha = true;
		*mesma_coluna = false;
		*ultima_linha_chutada = linha_random;
		*ultima_coluna_chutada = coluna_random+1;	
	}
}

int main () {
	
	int opcao, num_linhas_tabuleiro, num_colunas_tabuleiro, i, vet_navios[4], x, y, linha_random, coluna_random, cont_navios=0, num_navio=0, navio_derrubado=0,
	 	direcao=0, navio_inserido=0, validade_tiro=0, ultima_linha_chutada=0, ultima_coluna_chutada=0, validade_direcao;
	bool game_over = false, mesma_linha=false, mesma_coluna=false, acertou_direcao=false, inverter_sentido, posicao_ja_chutada;
	navio_descr navio_acertado;
	navio_acertado.num = 0;

	srand(time(NULL));

	printf("Digite 1 se deseja jogar sozinho ou 2 se deseja jogar com o computador: \n");
	scanf("%d", &opcao);

	if (opcao == 1) {
		le_dimensao(&num_linhas_tabuleiro, &num_colunas_tabuleiro);
		int **matriz = cria_matriz(num_linhas_tabuleiro, num_colunas_tabuleiro);
		le_quant_navios(vet_navios);

		if (verifica_validade_navios(vet_navios, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1) { //Verifica se os navios ocupam menos de 50% do tabuleiro

			for (i=0; i<vet_navios[3]; i++){
				cont_navios++;
				insere_navio_random(4, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz, cont_navios);
			}
			for (i=0; i<vet_navios[2]; i++){
				cont_navios++;
				insere_navio_random(3, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz, cont_navios);
			}
			for (i=0; i<vet_navios[1]; i++){
				cont_navios++;
				insere_navio_random(2, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz, cont_navios);
			}
			for (i=0; i<vet_navios[0]; i++){
				cont_navios++;
				insere_navio_random(1, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz, cont_navios);
			}	

			while(verifica_navios_derrubados(matriz, num_linhas_tabuleiro, num_colunas_tabuleiro) == 0) {
				printf("\nInforme um ponto(linha-coluna): \n");
				scanf("%d %d", &x, &y);

				while (tiro_dentro_tabuleiro(x, y, num_linhas_tabuleiro, num_colunas_tabuleiro) == 0 || ja_atirou_na_posicao(x, y, matriz,
				num_linhas_tabuleiro, num_colunas_tabuleiro)) {
					printf("\nṔonto inválido. Informe novamente um ponto(linha-coluna): \n");	
					scanf("%d %d", &x, &y);				
				}

				validade_tiro = verifica_acertou_navio(x, y, matriz, num_linhas_tabuleiro, num_colunas_tabuleiro);
				if (validade_tiro == 0) {
					printf("Acertou na água.\n");
				} else if (validade_tiro == -1) {
					printf("Derrubou um navio!!!!!\n");
				} else {
					printf("Acertou em um navio.\n");
				}

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

			//INSERE NAVIOS NA MATRIZ DO COMPUTADOR
			for (i=0; i<vet_navios[3]; i++){
				cont_navios++;
				insere_navio_random(4, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz2, cont_navios);
			}
			for (i=0; i<vet_navios[2]; i++){
				cont_navios++;
				insere_navio_random(3, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz2, cont_navios);
			}
			for (i=0; i<vet_navios[1]; i++){
				cont_navios++;
				insere_navio_random(2, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz2, cont_navios);
			}
			for (i=0; i<vet_navios[0]; i++){
				cont_navios++;
				insere_navio_random(1, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz2, cont_navios);
			}

			//INSERE NAVIOS NA MATRIZ NO JOGADOR
			cont_navios=0;

			for (i=0; i<vet_navios[3]; i++){
				cont_navios++;
				insere_navio_random(4, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz1, cont_navios);
			}
			for (i=0; i<vet_navios[2]; i++){
				cont_navios++;
				insere_navio_random(3, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz1, cont_navios);
			}
			for (i=0; i<vet_navios[1]; i++){
				cont_navios++;
				insere_navio_random(2, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz1, cont_navios);
			}
			for (i=0; i<vet_navios[0]; i++){
				cont_navios++;
				insere_navio_random(1, num_linhas_tabuleiro, num_colunas_tabuleiro, matriz1, cont_navios);
			}

			printf("\nINICIO DO JOGO\n");
			time_t inicio = time(NULL);
			while(true) {
				validade_tiro=0;
				
				printf("\nVEZ DO USUÁRIO\nInforme um ponto(linha-coluna): \n");
				scanf("%d %d", &x, &y);

				while (tiro_dentro_tabuleiro(x, y, num_linhas_tabuleiro, num_colunas_tabuleiro) == 0 || ja_atirou_na_posicao(x, y, matriz2,
				num_linhas_tabuleiro, num_colunas_tabuleiro)) {
					printf("Ṕonto inválido. Informe novamente um ponto(linha-coluna): \n");	
					scanf("%d %d", &x, &y);				
				}

				validade_tiro = verifica_acertou_navio(x, y, matriz2, num_linhas_tabuleiro, num_colunas_tabuleiro);
				if (validade_tiro == 0) {
					printf("Acertou na água.\n");
				} else if (validade_tiro == -1) {
					printf("Derrubou um navio!!!!!\n");
				} else {
					printf("Acertou em um navio.\n");
				}

				printf("\nVEZ DO COMPUTADOR\n");

				if (navio_acertado.num == 0) {
					jogada_computador(matriz1, num_linhas_tabuleiro, num_colunas_tabuleiro, &linha_random, &coluna_random, &validade_tiro, &ultima_linha_chutada,
						&ultima_coluna_chutada, &navio_acertado, &posicao_ja_chutada, &acertou_direcao, &direcao, &mesma_linha, &mesma_coluna, &inverter_sentido);
				} else{
					validade_tiro=0;
					validade_direcao=0;

					//linha_random = ultima linha chutado pelo computador
					//coluna_random = ultima coluna chutada pelo computador

					if (acertou_direcao) {
						jogada_computador(matriz1, num_linhas_tabuleiro, num_colunas_tabuleiro, &linha_random, &coluna_random, &validade_tiro,
							&ultima_linha_chutada, &ultima_coluna_chutada, &navio_acertado, &posicao_ja_chutada, &acertou_direcao, &direcao,
								&mesma_linha, &mesma_coluna, &inverter_sentido);
	
					}else{ 
						sorteia_direcao(&direcao, matriz1, num_linhas_tabuleiro, num_colunas_tabuleiro, linha_random, coluna_random);
						jogada_computador_com_direcao_chutada(matriz1, num_linhas_tabuleiro, num_colunas_tabuleiro, linha_random, coluna_random, &validade_tiro,
							direcao, &navio_acertado, &acertou_direcao, &mesma_coluna, &mesma_linha, &ultima_linha_chutada, &ultima_coluna_chutada,
							&inverter_sentido);
					}				

				}

				if (jogo_acabou(matriz1, matriz2, num_linhas_tabuleiro, num_colunas_tabuleiro) == 1) {
					printf("Computador destruiu todos os navios\n");
					break;
				} else if (jogo_acabou(matriz1, matriz2, num_linhas_tabuleiro, num_colunas_tabuleiro) == 2) {
					printf("Voce destruiu todos os navios.\n");
					break;
				} 

				printf("------------FIM DA RODADA--------------\n");
			} //end while

			time_t fim = time(NULL);
			long int tempo = fim - inicio;
			printf("\nFIM DO JOGO\n");
			printf("\nTEMPO DECORRIDO: %ld SEGUNDOS.\n", tempo);

		} else{
			printf("Numero de navios inválidos.\n");
		}

	} else {
		printf("Opção inválida.\n");
	}

	return 0;
}