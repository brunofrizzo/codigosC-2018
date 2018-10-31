#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct aluno {
	long int matricula;
	char nome[100];
	char curso[100];
	struct aluno *proximo;
	struct l_descr_falta *lista_faltas;
};

struct no_aluno {
	struct aluno *aluno;
	struct no_aluno *proximo;
};

struct prof {
	long int siape;
	char nome[100];
	char area_atuacao[100];
	char titulacao[100];
	struct prof *proximo;
};

struct no_prof {
	struct prof *prof;
	struct no_prof *proximo;
};

struct curso{
	char nome[100];
	struct curso *proximo;
};

struct cadeira{
	long int cod;
	char curso[100];
	char nome[70];
	float carga_horaria;
	char pre_requisito[250];
	struct cadeira *proximo;
};

struct aula{
	long int id;
	char data[25];
	char conteudo[250];
	struct aula *proximo;
	struct l_descr_falta *lista_faltas;
};

struct turma{
	long int cod;
	long int cod_cadeira;
	struct l_descr_no_aluno *lista_alunos;
	struct l_descr_aula *lista_aulas;
	struct l_descr_no_prof *lista_profs;
	struct l_descr_avaliacao *lista_avaliacoes;
	struct turma *proximo;
};

struct avaliacao{
	float nota1;
	float nota2;
	struct aluno *aluno;
	struct avaliacao *proximo;
};

struct falta{
	struct aluno *aluno;
	long int cod_cadeira;
	struct falta *proximo;
};

struct l_descr_aluno{
	struct aluno *inicio;
	int cont;
	struct aluno *fim;
};

struct l_descr_no_aluno{
	struct no_aluno *inicio;
	int cont;
	struct no_aluno *fim;
};

struct l_descr_prof{
	struct prof *inicio;
	int cont;
	struct prof *fim;
};

struct l_descr_no_prof{
	struct no_prof *inicio;
	int cont;
	struct no_prof *fim;
};

struct l_descr_curso{
	struct curso *inicio;
	int cont;
	struct curso *fim;
};

struct l_descr_cadeira{
	struct cadeira *inicio;
	int cont;
	struct cadeira *fim;
};

struct l_descr_aula{
	struct aula *inicio;
	int cont;
	int cont_id;
	struct aula *fim;
};

struct l_descr_turma{
	struct turma *inicio;
	int cont;
	int cont_cod;
	struct turma *fim;
};

struct l_descr_avaliacao{
	struct avaliacao *inicio;
	int cont;
	struct avaliacao *fim;
};

struct l_descr_falta{
	struct falta *inicio;
	int cont;
	struct falta *fim;
};

void retira_espaco(char *string) {
	int len = strlen(string);
	if (string[len-1] == '\n') 
		string[--len] = 0;
}

///////////////////////FUNCOES PARA LISTA DE CURSOS///////////////////////
void inicializa_lista_cursos(struct l_descr_curso *lista) {
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->cont = 0;
}

void imprime_lista_cursos(struct l_descr_curso *lista) {
    struct curso *aux = lista->inicio;
    while(aux !=  NULL) {
        printf("->%s\n", aux->nome);
        aux = aux->proximo;
    }
}

void insere_vazia_lista_cursos(struct l_descr_curso *lista, char nome[]) {
	lista->inicio = malloc(sizeof(struct curso));
    strcpy(lista->inicio->nome, nome);
    lista->inicio->proximo = NULL;
    lista->cont++;
    lista->fim = lista->inicio;
}

void insere_inicio_lista_cursos(struct l_descr_curso *lista, char nome[]) {
    if (lista->inicio == NULL) {
        insere_vazia_lista_cursos(lista, nome);
    }else{
        struct curso *aux = malloc(sizeof(struct curso));
        strcpy(aux->nome, nome);
        aux->proximo = lista->inicio;
        lista->inicio = aux;
        lista->cont++;
    }
}

void exclui_inicio_lista_cursos(struct l_descr_curso *lista, struct curso *aux) {
	lista->inicio = aux->proximo;
	lista->cont--;
	free(aux);
}

void exclui_fim_lista_cursos(struct l_descr_curso *lista, struct curso *aux, struct curso *anterior) {
	lista->fim = anterior;
	anterior->proximo = NULL;
	lista->cont--;
	free(aux);
}

void exclui_lista_cursos(struct l_descr_curso *lista, char nome[100]) {
	struct curso *aux = lista->inicio;
	struct curso *anterior = NULL;

	while(aux != NULL){
		if (strcmp(aux->nome, nome) == 0) {
			if (anterior == NULL) {
				exclui_inicio_lista_cursos(lista, aux);
			}else if(aux->proximo == NULL) {
				exclui_fim_lista_cursos(lista, aux, anterior);
			}else{
				anterior->proximo = aux->proximo;
				lista->cont--;
				free(aux);
			}
			break;
		}
		anterior = aux;
		aux = aux->proximo;
	}
}

bool curso_cadastrado(struct l_descr_curso *lista, char nome[]) {
	struct curso *aux = lista->inicio;

	while(aux != NULL){
		if (strcmp(aux->nome,nome) == 0) {
			return true;
		}
		aux = aux->proximo;
	}
	return false;
}

///////////////////////FUNCOES PARA LISTA DE FALTAS///////////////////////
void inicializa_lista_faltas(struct l_descr_falta *lista) {
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->cont = 0;
}

void imprime_lista_faltas(struct l_descr_falta *lista) {
    struct falta *aux = lista->inicio;
    while(aux !=  NULL) {
        printf("->Falta do aluno: %s | Código da cadeira: %ld\n", aux->aluno->nome, aux->cod_cadeira);
        aux = aux->proximo;
    }	
}

void insere_vazia_lista_faltas(struct l_descr_falta *lista, struct falta falta) {
	lista->inicio = malloc(sizeof(struct falta));
	lista->inicio->aluno = falta.aluno;
    lista->inicio->cod_cadeira = falta.cod_cadeira;
	lista->inicio->proximo = NULL;
    lista->fim = lista->inicio;
    lista->cont++;
}

void insere_inicio_lista_faltas(struct l_descr_falta *lista, struct falta falta) {
    if (lista->inicio == NULL) {
    	insere_vazia_lista_faltas(lista, falta);
    }else{
        struct falta *aux = malloc(sizeof(struct falta));
        aux->aluno = falta.aluno;
        aux->cod_cadeira = falta.cod_cadeira;  
        aux->proximo = lista->inicio;
        lista->inicio = aux;
        lista->cont++;
    }
}

void exclui_inicio_lista_faltas(struct l_descr_falta *lista) {
	struct falta *aux = lista->inicio;
	lista->inicio = aux->proximo;
	lista->cont--;
	free(aux);
}

void exclui_fim_lista_faltas(struct l_descr_falta *lista, struct falta *anterior) {
	free(lista->fim);
	anterior->proximo = NULL;
	lista->fim = anterior;
	lista->cont--;
}

void exclui_falta_aluno(struct l_descr_falta *lista, long int mat) {
	struct falta *aux = lista->inicio;
	struct falta *anterior = NULL;

	while (aux != NULL) {
		if (aux->aluno->matricula == mat) {
			if (anterior == NULL) {
				exclui_inicio_lista_faltas(lista);
			}else if (aux->proximo == NULL) {
				exclui_fim_lista_faltas(lista, anterior);
			} else {
				anterior->proximo = aux->proximo;
				lista->cont--;
				free(aux);
			}
			break;
		}
		anterior = aux;
		aux = aux->proximo;
	}
}

///////////////////////FUNCOES PARA LISTA DE ALUNOS///////////////////////
void inicializa_lista_alunos(struct l_descr_aluno *lista) {
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->cont = 0;
}

void imprime_lista_alunos(struct l_descr_aluno *lista) {
    struct aluno *aux = lista->inicio;
    while(aux !=  NULL) {
        printf("->Nome: %s | Matrícula: %ld | Curso: %s\n", aux->nome, aux->matricula, aux->curso);
        aux = aux->proximo;
    }
}

void insere_vazia_lista_alunos(struct l_descr_aluno *lista, struct aluno aluno) {
	lista->inicio = malloc(sizeof(struct aluno));
    lista->inicio->matricula = aluno.matricula;
    strcpy(lista->inicio->nome, aluno.nome);
    strcpy(lista->inicio->curso, aluno.curso);
    lista->inicio->lista_faltas = malloc(sizeof(struct l_descr_falta));
    inicializa_lista_faltas(lista->inicio->lista_faltas);
    lista->inicio->proximo = NULL;
    lista->cont++;
    lista->fim = lista->inicio;
}

void insere_inicio_lista_alunos(struct l_descr_aluno *lista, struct aluno aluno) {
    if (lista->inicio == NULL) {
        insere_vazia_lista_alunos(lista, aluno);
    }else{
        struct aluno *aux = malloc(sizeof(struct aluno));
        aux->matricula = aluno.matricula;
	    strcpy(aux->nome, aluno.nome);
	    strcpy(aux->curso, aluno.curso);
    	aux->lista_faltas = malloc(sizeof(struct l_descr_falta));
	    inicializa_lista_faltas(aux->lista_faltas);
        aux->proximo = lista->inicio;
        lista->inicio = aux;
        lista->cont++;
    }
}

bool matricula_ja_cadastrada(struct l_descr_aluno *lista, long int matricula) {
	struct aluno *aux = lista->inicio;

	while(aux != NULL){
		if (aux->matricula == matricula) {
			return true;
		}
		aux = aux->proximo;
	}
	return false;
}

void exclui_inicio_lista_alunos(struct l_descr_aluno *lista, struct aluno *aux) {
	lista->inicio = aux->proximo;
	lista->cont--;
	free(aux);
}

void exclui_fim_lista_alunos(struct l_descr_aluno *lista, struct aluno *aux, struct aluno *anterior) {
	lista->fim = anterior;
	anterior->proximo = NULL;
	lista->cont--;
	free(aux);
}

void exclui_lista_alunos(struct l_descr_aluno *lista, long int matricula) {
	struct aluno *aux = lista->inicio;
	struct aluno *anterior = NULL;

	while(aux != NULL){
		if (aux->matricula == matricula) {
			if (anterior == NULL) {
				exclui_inicio_lista_alunos(lista, aux);
			}else if(aux->proximo == NULL) {
				exclui_fim_lista_alunos(lista, aux, anterior);
			}else{
				anterior->proximo = aux->proximo;
				lista->cont--;
				free(aux);
			}
			break;
		}
		anterior = aux;
		aux = aux->proximo;
	}
}

struct aluno *busca_aluno_by_matricula(struct l_descr_aluno *lista, long int matricula) {
	struct aluno *aux = lista->inicio;

	while(aux != NULL){
		if (aux->matricula == matricula) {
			return aux;
		}
		aux = aux->proximo;
	}
	return NULL;
}

///////////////////////FUNCOES PARA LISTA DE NO_ALUNOS///////////////////////
void inicializa_lista_no_alunos(struct l_descr_no_aluno *lista) {
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->cont = 0;
}

void imprime_lista_no_alunos(struct l_descr_no_aluno *lista) {
    struct no_aluno *aux = lista->inicio;
    while(aux !=  NULL) {
        printf("->Aluno: %s | Matricula: %ld\n", aux->aluno->nome, aux->aluno->matricula);
        aux = aux->proximo;
    }	
}

void insere_vazia_lista_no_alunos(struct l_descr_no_aluno *lista, struct aluno *aluno) {
	lista->inicio = malloc(sizeof(struct no_aluno));
    lista->cont++;  
	lista->inicio->aluno = aluno;
	lista->inicio->proximo = NULL;
    lista->fim = lista->inicio;
}

void insere_inicio_lista_no_alunos(struct l_descr_no_aluno *lista, struct aluno *aluno) {
    if (lista->inicio == NULL) {
    	insere_vazia_lista_no_alunos(lista, aluno);
    }else{
        struct no_aluno *aux = malloc(sizeof(struct no_aluno));
        lista->cont++;
        aux->aluno = aluno;  
        aux->proximo = lista->inicio;
        lista->inicio = aux;
    }
}

void exclui_inicio_lista_no_alunos(struct l_descr_no_aluno *lista, struct no_aluno *aux) {
	lista->inicio = aux->proximo;
	lista->cont--;
	free(aux);
}

bool aluno_ja_matriculado_turma(struct l_descr_no_aluno *lista, struct aluno *aluno) {
	struct no_aluno *aux = lista->inicio;

	while (aux != NULL) {
		if (aux->aluno == aluno) {
			return true;
		}
		aux = aux->proximo;
	}
	return false;
}

///////////////////////FUNCOES PARA LISTA DE PROFESSORES///////////////////////
void inicializa_lista_profs(struct l_descr_prof *lista) {
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->cont = 0;
}

void imprime_lista_profs(struct l_descr_prof *lista) {
    struct prof *aux = lista->inicio;
    while(aux !=  NULL) {
        printf("->Nome: %s | SIAPE: %ld\n", aux->nome, aux->siape);
        aux = aux->proximo;
    }
}

void insere_vazia_lista_profs(struct l_descr_prof *lista, struct prof prof) {
	lista->inicio = malloc(sizeof(struct prof));
    strcpy(lista->inicio->nome, prof.nome);
    lista->inicio->siape = prof.siape;
    strcpy(lista->inicio->area_atuacao, prof.area_atuacao);
    strcpy(lista->inicio->titulacao, prof.titulacao);    
    lista->inicio->proximo = NULL;
    lista->cont++;
    lista->fim = lista->inicio;
}

void insere_inicio_lista_profs(struct l_descr_prof *lista, struct prof prof) {
    if (lista->inicio == NULL) {
    	insere_vazia_lista_profs(lista, prof);
    }else{
        struct prof *aux = malloc(sizeof(struct prof));
        strcpy(aux->nome, prof.nome); 
        aux->siape = prof.siape;
      	strcpy(aux->area_atuacao, prof.area_atuacao);
    	strcpy(aux->titulacao, prof.titulacao);  
        aux->proximo = lista->inicio;
        lista->inicio = aux;
        lista->cont++;
    }
}

bool prof_ja_cadastrado(struct l_descr_prof *lista, long int siape) {
	struct prof *aux = lista->inicio;

	while(aux != NULL){
		if (aux->siape == siape) {
			return true;
		}
		aux = aux->proximo;
	}
	return false;	
}

void exclui_inicio_lista_profs(struct l_descr_prof *lista, struct prof *aux) {
	lista->inicio = aux->proximo;
	lista->cont--;
	free(aux);
}

void exclui_fim_lista_profs(struct l_descr_prof *lista, struct prof *aux, struct prof *anterior) {
	lista->fim = anterior;
	anterior->proximo = NULL;
	lista->cont--;
	free(aux);
}

void exclui_lista_profs(struct l_descr_prof *lista, long int siape) {
	struct prof *aux = lista->inicio;
	struct prof *anterior = NULL;

	while(aux != NULL){
		if (aux->siape == siape) {
			if (anterior == NULL) {
				exclui_inicio_lista_profs(lista, aux);
			}else if(aux->proximo == NULL){
				exclui_fim_lista_profs(lista, aux, anterior);
			}else{
				anterior->proximo = aux->proximo;
				lista->cont--;
				free(aux);
			}
			break;
		}
		anterior = aux;
		aux = aux->proximo;
	}
}

struct prof *busca_prof_by_siape(struct l_descr_prof *lista, long int siape) {
	struct prof *aux = lista->inicio;

	while(aux != NULL){
		if (aux->siape == siape) {
			return aux;
		}
		aux = aux->proximo;
	}
	return NULL;
}

///////////////////////FUNCOES PARA LISTA DE CADEIRAS///////////////////////
void inicializa_lista_cadeiras(struct l_descr_cadeira *lista) {
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->cont = 0;
}

void imprime_lista_cadeiras(struct l_descr_cadeira *lista) {
    struct cadeira *aux = lista->inicio;
    while(aux !=  NULL) {
        printf("->Nome: %s | Código: %ld\n", aux->nome, aux->cod);
        aux = aux->proximo;
    }	
}

void insere_vazia_lista_cadeiras(struct l_descr_cadeira *lista, struct cadeira cadeira) {
	lista->inicio = malloc(sizeof(struct cadeira));
	lista->inicio->cod = cadeira.cod;
	strcpy(lista->inicio->curso, cadeira.curso);  
	strcpy(lista->inicio->nome, cadeira.nome);  
	strcpy(lista->inicio->pre_requisito, cadeira.pre_requisito);  
	lista->inicio->carga_horaria = cadeira.carga_horaria;
    lista->inicio->proximo = NULL;
    lista->cont++;
    lista->fim = lista->inicio;
}

void insere_inicio_lista_cadeiras(struct l_descr_cadeira *lista, struct cadeira cadeira) {
    if (lista->inicio == NULL) {
    	insere_vazia_lista_cadeiras(lista, cadeira);
    }else{
        struct cadeira *aux = malloc(sizeof(struct cadeira));
        aux->cod = cadeira.cod;
        strcpy(aux->curso, cadeira.curso);  
		strcpy(aux->nome, cadeira.nome);  
		strcpy(aux->pre_requisito, cadeira.pre_requisito);   
		aux->carga_horaria = cadeira.carga_horaria; 
        aux->proximo = lista->inicio;
        lista->inicio = aux;
        lista->cont++;
    }
}

void exclui_inicio_lista_cadeiras(struct l_descr_cadeira *lista, struct cadeira *aux) {
	lista->inicio = aux->proximo;
	lista->cont--;
	free(aux);
}

void exclui_fim_lista_cadeiras(struct l_descr_cadeira *lista, struct cadeira *aux, struct cadeira *anterior) {
	lista->fim = anterior;
	anterior->proximo = NULL;
	lista->cont--;
	free(aux);
}

void exclui_lista_cadeiras(struct l_descr_cadeira *lista, long int cod) {
	struct cadeira *aux = lista->inicio;
	struct cadeira *anterior = NULL;

	while(aux != NULL){
		if (aux->cod == cod) {
			if (anterior == NULL) {
				exclui_inicio_lista_cadeiras(lista, aux);
			}else if(aux->proximo == NULL) {
				exclui_fim_lista_cadeiras(lista, aux, anterior);
			}else{
				anterior->proximo = aux->proximo;
				lista->cont--;
				free(aux);
			}
			break;
		}
		anterior = aux;
		aux = aux->proximo;
	}
}

char *nome_cadeira_por_cod(struct l_descr_cadeira *lista, long int cod) {
	struct cadeira *aux = lista->inicio;

	while(aux != NULL){
		if (aux->cod == cod) {
			return aux->nome;
		}
		aux = aux->proximo;
	}
} 

bool cadeira_ja_cadastrada(struct l_descr_cadeira *lista, long int cod) {
	struct cadeira *aux = lista->inicio;

	while(aux != NULL){
		if (aux->cod == cod) {
			return true;
		}
		aux = aux->proximo;
	}
	return false;	
}

struct cadeira *busca_cadeira_by_cod(long int cod, struct l_descr_cadeira *lista_cadeiras) {
	struct cadeira *aux = lista_cadeiras->inicio;

	while(aux != NULL) {
		if (aux->cod == cod) {
			return aux;
		}
		aux = aux->proximo;
	}
	return NULL;
}

///////////////////////FUNCOES PARA LISTA DE AVALIACOES///////////////////////
void inicializa_lista_avaliacoes(struct l_descr_avaliacao *lista) {
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->cont = 0;
}

void imprime_lista_avaliacoes(struct l_descr_avaliacao *lista) {
    struct avaliacao *aux = lista->inicio;
    while(aux !=  NULL) {
        printf("->Nota 1: %.2f | Nota 2: %.2f | Matrícula do aluno: %ld\n",  aux->nota1, aux->nota2, aux->aluno->matricula);    	
        aux = aux->proximo;
    }	
}

void insere_vazia_lista_avaliacoes(struct l_descr_avaliacao *lista, struct avaliacao avaliacao) {
	lista->inicio = malloc(sizeof(struct avaliacao));
	lista->inicio->nota1 = avaliacao.nota1;
	lista->inicio->nota2 = avaliacao.nota2;    
	lista->inicio->aluno = avaliacao.aluno;
    lista->inicio->proximo = NULL;
    lista->cont++;
    lista->fim = lista->inicio;
}

void insere_inicio_lista_avaliacoes(struct l_descr_avaliacao *lista, struct avaliacao avaliacao) {
    if (lista->inicio == NULL) {
    	insere_vazia_lista_avaliacoes(lista, avaliacao);
    }else{
        struct avaliacao *aux = malloc(sizeof(struct avaliacao));
        aux->nota1 = avaliacao.nota1;
        aux->nota2 = avaliacao.nota2;    
		aux->aluno = avaliacao.aluno;
        aux->proximo = lista->inicio;
        lista->inicio = aux;
        lista->cont++;
    }
}

void exclui_inicio_lista_avaliacoes(struct l_descr_avaliacao *lista, struct avaliacao *aux) {
	lista->inicio = aux->proximo;
	lista->cont--;
	free(aux);
}

void exclui_fim_lista_avaliacoes(struct l_descr_avaliacao *lista, struct avaliacao *aux, struct avaliacao *anterior) {
	lista->fim = anterior;
	anterior->proximo = NULL;
	lista->cont--;
	free(aux);
}

void exclui_lista_avaliacoes(struct l_descr_avaliacao *lista, long int mat) {
	struct avaliacao *aux = lista->inicio;
	struct avaliacao *anterior = NULL;

	while(aux != NULL){
		if (aux->aluno->matricula == mat) {
			if (anterior == NULL) {
				exclui_inicio_lista_avaliacoes(lista, aux);
			}else if(aux->proximo == NULL) {
				exclui_fim_lista_avaliacoes(lista, aux, anterior);
			}else{
				anterior->proximo = aux->proximo;
				lista->cont--;
				free(aux);
			}
			break;
		}
		anterior = aux;
		aux = aux->proximo;
	}
}

bool avaliacao_ja_cadastrada(struct l_descr_avaliacao *lista, long int matricula_aluno) {
	struct avaliacao *aux = lista->inicio;

	while(aux != NULL){
		if (aux->aluno->matricula == matricula_aluno) {
			return true;
		}
		aux = aux->proximo;
	}
	return false;	
}

///////////////////////FUNCOES PARA LISTA DE AULAS///////////////////////
void inicializa_lista_aulas(struct l_descr_aula *lista) {
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->cont = 0;
    lista->cont_id = 0;
}

void imprime_lista_aulas(struct l_descr_aula *lista) {
    struct aula *aux = lista->inicio;
    while(aux !=  NULL) {
        printf("->Aula %ld\n", aux->id);
        printf("\tData: %s\n", aux->data);
        printf("\tFaltas: \n");
        struct falta *aux2 = aux->lista_faltas->inicio;
        if (aux2 == NULL) 
        	printf("\tNenhuma falta registrada nessa aula.\n");
        else {
	        while (aux2 != NULL) {
	        	printf("\t->Falta do aluno de matrícula %ld\n", aux2->aluno->matricula);
	        	aux2 = aux2->proximo;
	        }
	    }
        aux = aux->proximo;
    }	
}

void insere_vazia_lista_aulas(struct l_descr_aula *lista, struct aula aula) {
	lista->inicio = malloc(sizeof(struct aula));
	lista->cont_id++;
    lista->inicio->id = lista->cont_id;
    strcpy(lista->inicio->data, aula.data); 
    strcpy(lista->inicio->conteudo, aula.conteudo); 
	lista->inicio->lista_faltas = malloc(sizeof(struct l_descr_falta));
	inicializa_lista_faltas(lista->inicio->lista_faltas);
	lista->inicio->proximo = NULL;
    lista->fim = lista->inicio;
    lista->cont++;
}

void insere_inicio_lista_aulas(struct l_descr_aula *lista, struct aula aula) {
    if (lista->inicio == NULL) {
    	insere_vazia_lista_aulas(lista, aula);
    }else{
        struct aula *aux = malloc(sizeof(struct aula));
        lista->cont_id++;
        aux->id = lista->cont_id;
        strcpy(aux->data, aula.data);
        strcpy(aux->conteudo, aula.conteudo);
		aux->lista_faltas = malloc(sizeof(struct l_descr_falta));  
        aux->proximo = lista->inicio;
        lista->inicio = aux;
        lista->cont++;
    }
}

void exclui_inicio_lista_aulas(struct l_descr_aula *lista, struct aula *aux) {
	lista->inicio = aux->proximo;
	lista->cont--;
	free(aux);
}

struct aula *busca_aula_by_id(struct l_descr_aula *lista, long int num) {
	struct aula *aux = lista->inicio;

	while(aux != NULL) {
		if (aux->id == num) {
			return aux;
		}
		aux = aux->proximo;
	}
	return false;
}

///////////////////////FUNCOES PARA LISTA DE TURMAS///////////////////////
void inicializa_lista_turmas(struct l_descr_turma *lista) {
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->cont = 0;
    lista->cont_cod = 0;
}

void imprime_lista_turmas(struct l_descr_turma *lista, struct l_descr_cadeira *lista_cadeiras) {
	bool entrou=false;
    struct turma *aux = lista->inicio;
    while(aux !=  NULL) {
        printf("->Turma(código): %ld\n", aux->cod);
		printf("\tCadeira: %s\n", nome_cadeira_por_cod(lista_cadeiras, aux->cod_cadeira));
		printf("\tNumero de alunos: %d\n", aux->lista_alunos->cont);
		printf("\tNúmero de profs: %d\n", aux->lista_profs->cont);
        printf("\tProfessores: ");
        struct no_prof *aux2 = aux->lista_profs->inicio;
        while (aux2 != NULL){
        	printf("%s. ", aux2->prof->nome);
        	aux2 = aux2->proximo;
        }
        printf("\n");
    	printf("\tLista de aulas: \n");
        struct aula *aux3 = aux->lista_aulas->inicio;
        if (aux3 == NULL){
        	printf("\tNenhuma aula registrada.\n");
        }else{	
	        while (aux3 != NULL) {
	        	printf("\t->Aula do dia %s\n", aux3->data);
	        	aux3 = aux3->proximo;
	        }
	    }
        printf("\tLista de faltas: \n");
        aux3 = aux->lista_aulas->inicio;
        while (aux3 != NULL) {
        	struct falta *aux4 = aux3->lista_faltas->inicio;
        	while (aux4 != NULL){
        		entrou = true;
        		printf("\t->Falta do aluno %s\n", aux4->aluno->nome);
        		aux4 = aux4->proximo;
        	}
        	aux3 = aux3->proximo;
        }
        if (!entrou) {
        	printf("\tNenhuma falta registrada.\n");
        }
        aux = aux->proximo;
    }	
}

void insere_vazia_lista_turmas(struct l_descr_turma *lista, struct turma turma) {
	lista->inicio = malloc(sizeof(struct turma));
    lista->cont_cod++; 
	lista->inicio->cod = lista->cont_cod;
	lista->inicio->cod_cadeira = turma.cod_cadeira;
	lista->inicio->lista_alunos = malloc(sizeof(struct l_descr_no_aluno));
	inicializa_lista_no_alunos(lista->inicio->lista_alunos);
    lista->inicio->lista_aulas = malloc(sizeof(struct l_descr_aula));
    inicializa_lista_aulas(lista->inicio->lista_aulas);
    lista->inicio->lista_profs = turma.lista_profs;
    lista->inicio->lista_avaliacoes = malloc(sizeof(struct l_descr_avaliacao));
    inicializa_lista_avaliacoes(lista->inicio->lista_avaliacoes);
    lista->inicio->proximo = NULL;
    lista->fim = lista->inicio;
    lista->cont++; 
}

void insere_inicio_lista_turmas(struct l_descr_turma *lista, struct turma turma) {
    if (lista->inicio == NULL) {
    	insere_vazia_lista_turmas(lista, turma);
    }else{
        struct turma *aux = malloc(sizeof(struct turma));
        lista->cont_cod++;
        aux->cod = lista->cont_cod;  
		aux->cod_cadeira = turma.cod_cadeira;
		aux->lista_alunos = malloc(sizeof(struct l_descr_no_aluno));
		inicializa_lista_no_alunos(aux->lista_alunos);
		aux->lista_aulas = malloc(sizeof(struct l_descr_aula));
		inicializa_lista_aulas(aux->lista_aulas);
		aux->lista_profs = turma.lista_profs;
		aux->lista_avaliacoes = malloc(sizeof(struct l_descr_avaliacao));
		inicializa_lista_avaliacoes(aux->lista_avaliacoes);
        aux->proximo = lista->inicio;
        lista->inicio = aux;
        lista->cont++;
    }
}

void exclui_inicio_lista_turmas(struct l_descr_turma *lista, struct turma *aux) {
	lista->inicio = aux->proximo;
	lista->cont--;
	free(aux);
}

void exclui_fim_lista_turmas(struct l_descr_turma *lista, struct turma *aux, struct turma *anterior) {
	lista->fim = anterior;
	anterior->proximo = NULL;
	lista->cont--;
	free(aux);
}

void exclui_lista_turmas(struct l_descr_turma *lista, long int cod) {
	struct turma *aux = lista->inicio;
	struct turma *anterior = NULL;

	while(aux != NULL){
		if (aux->cod == cod) {
			if (anterior == NULL) {
				exclui_inicio_lista_turmas(lista, aux);
			}else if(aux->proximo == NULL) {
				exclui_fim_lista_turmas(lista, aux, anterior);
			}else{
				anterior->proximo = aux->proximo;
				lista->cont--;
				free(aux);
			}
			break;
		}
		anterior = aux;
		aux = aux->proximo;
	}
}

struct turma *turma_cadastrada(struct l_descr_turma *lista, long int cod) {
	struct turma *aux = lista->inicio;
	while (aux != NULL) {
		if (aux->cod == cod) {
			return aux;
		}
		aux = aux->proximo;
	}
	return NULL;
}

bool turma_ja_cadastrada(struct l_descr_turma *lista, long int cod) {
	struct turma *aux = lista->inicio;
	while(aux != NULL){
		if (aux->cod == cod) {
			return true;
		}
		aux = aux->proximo;
	}
	return false;	
}

long int busca_cod_turma_by_matricula(long int mat, struct l_descr_turma *lista_turmas) {
	struct turma *aux_turma = lista_turmas->inicio;
	struct no_aluno *aux_no_aluno;
	while (aux_turma != NULL) {
		aux_no_aluno = aux_turma->lista_alunos->inicio;
		while (aux_no_aluno != NULL) {
			if (aux_no_aluno->aluno->matricula == mat) {
				return aux_turma->cod;
			}
			aux_no_aluno = aux_no_aluno->proximo;
		}
		aux_turma = aux_turma->proximo;
	}
	return 0;
}

long int busca_cod_turma_by_siape(long int siape, struct l_descr_turma *lista_turmas) {
	struct turma *aux_turma = lista_turmas->inicio;
	while (aux_turma != NULL) {
		struct no_prof *aux_no_prof = aux_turma->lista_profs->inicio;
		while (aux_no_prof != NULL) {
			if (aux_no_prof->prof->siape == siape) {
				return aux_turma->cod;
			}
			aux_no_prof = aux_no_prof->proximo;
		}
		aux_turma = aux_turma->proximo;
	}
	return 0;
}

long int busca_cod_turma_by_cod_cadeira(long int cod, struct l_descr_turma *lista_turmas) {
	struct turma *aux = lista_turmas->inicio;
	while (aux != NULL) {
		if (aux->cod_cadeira == cod) {
			return aux->cod;
		}
		aux = aux->proximo;
	}
	return 0;
}

struct turma *busca_turma_by_cod(struct l_descr_turma *lista, long int cod) {
	struct turma *aux = lista->inicio;
	while(aux != NULL) {
		if (aux->cod == cod) {
			return aux;
		}
		aux = aux->proximo;
	}
	return NULL;
}

void exclui_inicio_aluno_turma(struct turma *turma, struct no_aluno *aux) {
	turma->lista_alunos->inicio = aux->proximo;
	turma->lista_alunos->cont--;
	free(aux);
}

void exclui_fim_aluno_turma(struct turma *turma, struct no_aluno *aux, struct no_aluno *anterior) {
	turma->lista_alunos->fim = anterior;
	anterior->proximo = NULL;
	turma->lista_alunos->cont--;
	free(aux);
}

void exclui_aluno_turma(struct turma *turma, long int matricula) {
	struct no_aluno *aluno_anterior = NULL;
	struct no_aluno *aux2 = turma->lista_alunos->inicio;

	while(aux2 != NULL) {
		if (aux2->aluno->matricula == matricula) {
			if (aluno_anterior == NULL) {
				exclui_inicio_aluno_turma(turma, aux2);
			}else if(aux2->proximo == NULL) {
				exclui_fim_aluno_turma(turma, aux2, aluno_anterior);
			}else{
				aluno_anterior->proximo = aux2->proximo;
				turma->lista_alunos->cont--;
				free(aux2);
			}
			break;
		}
		aluno_anterior = aux2;
		aux2 = aux2->proximo;
	}
}

void exclui_inicio_prof_turma(struct turma *turma, struct no_prof *aux) {
	turma->lista_profs->inicio = aux->proximo;
	turma->lista_profs->cont--;
	free(aux);
}

void exclui_fim_prof_turma(struct turma *turma, struct no_prof *aux, struct no_prof *anterior) {
	turma->lista_profs->fim = anterior;
	anterior->proximo = NULL;
	turma->lista_profs->cont--;
	free(aux);
}

void exclui_prof_turma(struct l_descr_turma *lista_turmas, long int cod_turma, long int siape) {
	struct turma *aux = lista_turmas->inicio;
	struct no_prof *prof_anterior = NULL;

	while (aux != NULL) {
		if (aux->cod == cod_turma) {
			struct no_prof *aux2 = aux->lista_profs->inicio;
			while(aux2 != NULL) {
				if (aux2->prof->siape == siape) {
					if (prof_anterior == NULL) {
						exclui_inicio_prof_turma(aux, aux2);
					}else if(aux2->proximo == NULL) {
						exclui_fim_prof_turma(aux, aux2, prof_anterior);
					}else{
						prof_anterior->proximo = aux2->proximo;
						aux->lista_profs->cont--;
						free(aux2);
					}
					break;
				}
				prof_anterior = aux2;
				aux2 = aux2->proximo;
			}
		}
		aux = aux->proximo;
	}	
}

///////////////////////FUNCOES PARA LISTA DE NO_PROFS///////////////////////
void inicializa_lista_no_profs(struct l_descr_no_prof *lista) {
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->cont = 0;
}

void imprime_lista_no_profs(struct l_descr_no_prof *lista) {
    struct no_prof *aux = lista->inicio;
    while(aux !=  NULL) {
        printf("->Professor: %s | SIAPE: %ld\n", aux->prof->nome, aux->prof->siape);
        aux = aux->proximo;
    }	
}

void insere_vazia_lista_no_profs(struct l_descr_no_prof *lista, struct prof *prof) {
	lista->inicio = malloc(sizeof(struct no_prof));
    lista->cont++;  
	lista->inicio->prof = prof;
	lista->inicio->proximo = NULL;
    lista->fim = lista->inicio;
}

void insere_inicio_lista_no_profs(struct l_descr_no_prof *lista, struct prof *prof) {
    if (lista->inicio == NULL) {
    	insere_vazia_lista_no_profs(lista, prof);
    }else{
        struct no_prof *aux = malloc(sizeof(struct no_prof));
        lista->cont++;
        aux->prof = prof;  
        aux->proximo = lista->inicio;
        lista->inicio = aux;
    }
}

void exclui_inicio_lista_no_profs(struct l_descr_no_prof *lista, struct no_prof *aux) {
	lista->inicio = aux->proximo;
	lista->cont--;
	free(aux);
}

bool prof_ja_vinculado_turma(struct l_descr_no_prof *lista, struct prof *prof) {
	struct no_prof *aux = lista->inicio;

	while (aux != NULL) {
		if (aux->prof == prof) {
			return true;
		}
		aux = aux->proximo;
	}
	return false;
}

void vincula_prof_turma(struct turma *turma, long int siape, struct l_descr_prof *lista_profs) {
	struct prof *prof = busca_prof_by_siape(lista_profs, siape);
	insere_inicio_lista_no_profs(turma->lista_profs, prof);		
	printf("PROFESSOR VINCULADO COM SUCESSO!\n");
}

///////////////////////FUNCOES DE CADASTRO///////////////////////
void cadastro_curso(struct l_descr_curso *lista_cursos) {
	char nome[100];

	printf("---------------CADASTRO DE CURSO---------------\n");
	setbuf(stdin, NULL);
	printf("Nome:\n");
	fgets(nome, 100, stdin);

	retira_espaco(nome);

	while (curso_cadastrado(lista_cursos, nome)) {
		setbuf(stdin, NULL);
		printf("Curso ja cadastrado. Informe novamente: \n");
		fgets(nome, 100, stdin);
		retira_espaco(nome);
	}

	insere_inicio_lista_cursos(lista_cursos, nome);
	printf("CURSO CADASTRADO COM SUCESSO!\n");
	
}

void cadastro_aluno(struct l_descr_aluno *lista_alunos, struct l_descr_curso *lista_cursos) {
	while(lista_cursos->inicio == NULL) {
		printf("Nenhum curso cadastrado. Para prosseguir com o cadastro de aluno, preencha o cadastro de curso.\n");
		cadastro_curso(lista_cursos);
	}

	char nome[100];
	char curso[100];
	long int matricula;
	struct aluno novo_aluno;

	printf("---------------CADASTRO DE ALUNO---------------\n");
	setbuf(stdin, NULL);
	printf("Nome:\n");
	fgets (nome, 100, stdin);
	printf("Matricula:\n");
	scanf("%ld", &matricula);
	while (matricula_ja_cadastrada(lista_alunos, matricula)) {
		printf("Matricula ja cadastrada. Informe novamente: \n");
		scanf("%ld", &matricula);
	}
	setbuf(stdin, NULL);
	printf("Curso: \n");
	fgets (curso, 100, stdin);

	retira_espaco(curso);
	retira_espaco(nome);

	while (!curso_cadastrado(lista_cursos, curso)) {
		setbuf(stdin, NULL);
		printf("Curso nao cadastrado. Informe novamente: \n");
		fgets (curso, 100, stdin);
		retira_espaco(curso);
	}

	strcpy(novo_aluno.nome, nome);
	strcpy(novo_aluno.curso, curso);
	novo_aluno.matricula = matricula;

	insere_inicio_lista_alunos(lista_alunos, novo_aluno);
	printf("ALUNO CADASTRADO COM SUCESSO!\n");
}

void cadastro_prof(struct l_descr_prof *lista) {
	struct prof novo_prof;
	long int siape;
	char nome[100];
	char area_atuacao[100];
	char titulacao[100];

	printf("---------------CADASTRO DE PROFESSOR---------------\n");
	setbuf(stdin, NULL);
	printf("Nome:\n");
	fgets(nome, 100, stdin);
	printf("SIAPE:\n");
	scanf("%ld", &siape);
	while (prof_ja_cadastrado(lista, siape)) {
		printf("SIAPE ja cadastrado. Informe novamente:\n");
		scanf("%ld", &siape);
	}
	setbuf(stdin, NULL);
	printf("Área de atuação:\n");
	fgets(area_atuacao, 100, stdin);
	setbuf(stdin, NULL);
	printf("Titulação:\n");
	fgets(titulacao, 100, stdin);

	retira_espaco(nome);
	retira_espaco(area_atuacao);
	retira_espaco(titulacao);

	novo_prof.siape = siape;
	strcpy(novo_prof.nome, nome);
    strcpy(novo_prof.area_atuacao, area_atuacao);  
    strcpy(novo_prof.titulacao, titulacao);  

	insere_inicio_lista_profs(lista, novo_prof);

}

void cadastro_cadeira(struct l_descr_cadeira *lista, struct l_descr_curso *lista_cursos) {
	while(lista_cursos->inicio == NULL) {
		printf("Nenhum curso cadastrado. Para prosseguir com a cadastro de disciplina, preencha o cadastro de curso.\n");
		cadastro_curso(lista_cursos);
	}

	struct cadeira nova_cadeira;
	long int cod;
	char nome[100];
	char curso[100];
	char pre_requisito[250];
	float carga_horaria;

	printf("---------------CADASTRO DE DISCIPLINA---------------\n");
	printf("Codigo: \n");
	scanf("%ld", &cod);
	while(cadeira_ja_cadastrada(lista, cod)) {
		printf("Codigo ja cadastrado. Informe novamente:\n");
		scanf("%ld", &cod);
	}
	setbuf(stdin, NULL);
	printf("Nome:\n");
	fgets(nome, 100, stdin);
	setbuf(stdin, NULL);
	printf("Curso:\n");
	fgets(curso, 100, stdin);
	retira_espaco(curso);
	while(!curso_cadastrado(lista_cursos, curso)) {
		setbuf(stdin, NULL);
		printf("Curso não cadastrado. Informe novamente:\n");
		fgets(curso, 100, stdin);
		retira_espaco(curso);
	}
	setbuf(stdin, NULL);
	printf("Pré requisito:\n");
	fgets(pre_requisito, 250, stdin);
	printf("Carga horária:\n");
	scanf("%f", &carga_horaria);

	retira_espaco(nome);
	retira_espaco(pre_requisito);  

	nova_cadeira.cod = cod;
	strcpy(nova_cadeira.nome, nome);
	strcpy(nova_cadeira.curso, curso);
	strcpy(nova_cadeira.pre_requisito, pre_requisito);
	nova_cadeira.carga_horaria = carga_horaria;

	insere_inicio_lista_cadeiras(lista, nova_cadeira);
	printf("DISCIPLINA CADASTRADA COM SUCESSO!\n");
}

void cadastro_turma(struct l_descr_turma *lista, struct l_descr_cadeira *lista_cadeiras, struct l_descr_curso *lista_cursos, struct l_descr_prof *lista_profs) {
	while(lista_cadeiras->inicio == NULL){
		printf("Nenhuma disciplina cadastrada. Para prosseguir com o cadastro de turma, preencha o cadastro de disciplina.\n");
		cadastro_cadeira(lista_cadeiras, lista_cursos);
	}
	while(lista_profs->inicio == NULL){
		printf("Nenhum professor cadastrado. Para prosseguir com o cadastro de turma, preencha o cadastro de professores.\n");
		cadastro_prof(lista_profs);
	}

	struct turma nova_turma;
	long int cod_cadeira, siape;

	printf("---------------CADASTRO DE TURMA---------------\n");
	printf("Codigo da disciplina: \n");
	printf("Disciplinas cadastradas no sistema\n");
	imprime_lista_cadeiras(lista_cadeiras);
	scanf("%ld", &cod_cadeira);
	while(!cadeira_ja_cadastrada(lista_cadeiras, cod_cadeira)) {
		printf("Código não cadastrado. Informe novamente:\n");
		scanf("%ld", &cod_cadeira);
	}
	nova_turma.lista_profs = malloc(sizeof(struct l_descr_no_prof));
	inicializa_lista_no_profs(nova_turma.lista_profs);
	printf("Informe o SIAPE do professor que você deseja vincular a turma ou informe 0 para sair: \n");
	printf("Professores cadastrados no sistema\n");
	imprime_lista_profs(lista_profs);
	scanf("%ld", &siape);
	while (siape != 0) {
		while(!prof_ja_cadastrado(lista_profs, siape) || prof_ja_vinculado_turma(nova_turma.lista_profs,
		busca_prof_by_siape(lista_profs, siape))) {
			printf("SIAPE inválida. Informe novamente ou informe 0 para sair: \n");
			scanf("%ld", &siape);
			if (siape == 0) {
				break;
			}
		}
		if (siape == 0)  {
			break;
		}
		vincula_prof_turma(&nova_turma, siape, lista_profs);
		if (nova_turma.lista_profs->cont < lista_profs->cont){
			printf("Professores ja vinculados:\n");
			imprime_lista_no_profs(nova_turma.lista_profs);
			printf("Informe o SIAPE do professor que você deseja vincular a turma ou informe 0 para sair: \n");
			scanf("%ld", &siape);
		}else{
			printf("Desculpe, não há mais professores disponíveis para vincular a turma.\n");
			break;
		}
	}

	nova_turma.cod = 0;
	nova_turma.cod_cadeira = cod_cadeira;

	insere_inicio_lista_turmas(lista, nova_turma);
	printf("TURMA CADASTRADA COM SUCESSO!\n");
}

void cadastro_avaliacao(struct l_descr_aluno *lista_alunos, struct l_descr_turma *lista_turmas, struct l_descr_cadeira *lista_cadeiras, 
struct l_descr_curso *lista_cursos, struct l_descr_prof *lista_profs) {
	while(lista_turmas->inicio == NULL) {
		printf("Nenhuma turma cadastrada. Para prosseguir com o cadastro de avalição, preencha o cadastro de turma.\n");
		cadastro_turma(lista_turmas, lista_cadeiras, lista_cursos, lista_profs);
	}

	struct avaliacao nova_avaliacao;
	struct aluno *aluno;
	struct turma *turma;
	long int matricula, cod_turma;
	float n1, n2;

	printf("---------------CADASTRO DE AVALIAÇÃO---------------\n");
	printf("Código da turma que você deseja cadastrar avaliação: \n");
	imprime_lista_turmas(lista_turmas, lista_cadeiras);
	scanf("%ld", &cod_turma);
	turma = turma_cadastrada(lista_turmas, cod_turma);
	while (turma == NULL) {
		printf("Turma inválida. Informe novamente o código: \n");
		scanf("%ld", &cod_turma);
		turma = turma_cadastrada(lista_turmas, cod_turma);
	}
	if (turma->lista_alunos->cont == 0) {
		printf("Nenhum aluno matriculado nessa turma. Primeiro, realize a matrícula de algum aluno.\n");
	} else{
		printf("Alunos matriculados na turma\n");
		imprime_lista_no_alunos(turma->lista_alunos);
		printf("Matrícula do aluno que você deseja cadastrar a avaliação: \n");
		scanf("%ld", &matricula);
		aluno = busca_aluno_by_matricula(lista_alunos, matricula);
		while (aluno == NULL) {
			printf("Matricula não cadastrada no sistema. Informe novamente ou informe 0 para sair: \n");
			scanf("%ld", &matricula);
			if (matricula != 0) { 
				aluno = busca_aluno_by_matricula(lista_alunos, matricula);
			}else {
				break;
			}
		}
		if (matricula != 0) {
			while (!aluno_ja_matriculado_turma(turma->lista_alunos, aluno)) {
				printf("Matricula inválida. Informe novamente ou informe 0 para sair: \n");
				scanf("%ld", &matricula);
				if (matricula != 0) {
					aluno = busca_aluno_by_matricula(lista_alunos, matricula);
				}else{
					break;
				}
			}
			if (matricula != 0) {
				while (avaliacao_ja_cadastrada(turma->lista_avaliacoes, aluno->matricula) && matricula != 0) {
					printf("Avaliação ja cadastrada para esse aluno. Informe outra matrícula ou informe 0 para sair:\n");
					scanf("%ld", &matricula);
					if (matricula != 0) {
						aluno = busca_aluno_by_matricula(lista_alunos, matricula);
						while (aluno == NULL) {
							printf("Matricula não cadastrada no sistema. Informe novamente ou informe 0 para sair: \n");
							scanf("%ld", &matricula);
							if (matricula != 0) {
								aluno = busca_aluno_by_matricula(lista_alunos, matricula);
								while (!aluno_ja_matriculado_turma(turma->lista_alunos, aluno) && matricula != 0) {
									printf("Matricula inválida. Informe novamente ou informe 0 para sair: \n");
									scanf("%ld", &matricula);
									if (matricula != 0)
										aluno = busca_aluno_by_matricula(lista_alunos, matricula);
								}
							}else{
								break;
							}
													}
					}else{
						break;
					}
				}

				if (matricula != 0) {
					printf("Nota 1:\n");
					scanf("%f", &n1);
					while(n1 < 0 && n1 > 10) {
						printf("Nota inválida. Informe novamente: \n");
						scanf("%f", &n2);
					}
					printf("Nota 2:\n");
					scanf("%f", &n2);
					while(n2 < 0 && n2 > 10) {
						printf("Nota inválida. Informe novamente: \n");
						scanf("%f", &n2);
					}

					nova_avaliacao.nota1 = n1;
					nova_avaliacao.nota2 = n2;
					nova_avaliacao.aluno = aluno;   

					insere_inicio_lista_avaliacoes(turma->lista_avaliacoes, nova_avaliacao);
					printf("AVALIAÇÃO CADASTRADA COM SUCESSO!\n");
				}
			}
		}
	}
}

///////////////////////FUNCOES DE EXCLUSAO///////////////////////
void exclui_aluno(struct l_descr_aluno *lista, struct l_descr_turma *lista_turmas) {
	if (lista->inicio == NULL) {
		printf("Nenhum aluno cadastrado. Impossível realizar exclusão.\n");
	}else{
		long int matricula;
		long int cod_turma;
		struct turma *turma;
		struct aluno *aluno;

		printf("Alunos cadastrados\n");
		imprime_lista_alunos(lista);
		printf("Informe a matricula do aluno que você deseja excluir:\n");
		scanf("%ld", &matricula);
		while(!matricula_ja_cadastrada(lista, matricula)){
			printf("Matrícula inválida. Informe novamente:\n");
			scanf("%ld", &matricula);
		}

		cod_turma = busca_cod_turma_by_matricula(matricula, lista_turmas);
		while (cod_turma != 0) {
			aluno = busca_aluno_by_matricula(lista, matricula);
			turma = busca_turma_by_cod(lista_turmas, cod_turma);
			exclui_lista_avaliacoes(turma->lista_avaliacoes, matricula);
			struct aula *aux = turma->lista_aulas->inicio;
			while (aux != NULL) {
				struct falta *aux2 = aux->lista_faltas->inicio;
				while (aux2 != NULL) {
					if (aux2->aluno->matricula == matricula) {
						exclui_falta_aluno(aux->lista_faltas, matricula);
					}
					aux2 = aux2->proximo;
				}
				aux = aux->proximo;
			}
			exclui_aluno_turma(turma, matricula);
			cod_turma = busca_cod_turma_by_matricula(matricula, lista_turmas);
		}

		exclui_lista_alunos(lista, matricula);
		printf("ALUNO DE MATRICULA '%ld' REMOVIDO COM SUCESSO.\n", matricula);
	}
}

void exclui_prof(struct l_descr_prof *lista, struct l_descr_turma *lista_turmas, struct l_descr_cadeira *lista_cadeiras) {
	if (lista->inicio == NULL) {
		printf("Nenhum professor cadastrado. Impossível realizar exclusão.\n");
	}else{
		long int siape;
		long int cod_turma;

		printf("Professores cadastrados\n");
		imprime_lista_profs(lista);
		printf("Informe o SIAPE do professor que você deseja excluir:\n");
		scanf("%ld", &siape);
		while(!prof_ja_cadastrado(lista, siape)){
			printf("SIAPE inválida. Informe novamente:\n");
			scanf("%ld", &siape);
		}
		cod_turma = busca_cod_turma_by_siape(siape, lista_turmas);
		while(cod_turma != 0) {
			exclui_prof_turma(lista_turmas, cod_turma, siape);
			cod_turma = busca_cod_turma_by_siape(siape, lista_turmas);
		}
		exclui_lista_profs(lista, siape);
		printf("PROFESSOR DE SIAPE '%ld' REMOVIDO COM SUCESSO.\n", siape);
	}
}

void exclui_turma(struct l_descr_turma *lista, struct l_descr_cadeira *lista_cadeiras) {
	if (lista->inicio == NULL) {
		printf("Nenhuma turma cadastrada. Impossível realizar exclusão.\n");
	}else{
		long int cod;

		printf("Turmas cadastradas\n");
		imprime_lista_turmas(lista, lista_cadeiras);
		printf("Informe o codigo da turma que você deseja excluir:\n");
		scanf("%ld", &cod);
		while(!turma_ja_cadastrada(lista, cod)){
			printf("Codigo inválido. Informe novamente:\n");
			scanf("%ld", &cod);
		}
		exclui_lista_turmas(lista, cod);
		printf("TURMA DE CODIGO '%ld' REMOVIDO COM SUCESSO.\n", cod);
	}
}

void exclui_cadeira(struct l_descr_cadeira *lista, struct l_descr_turma *lista_turmas) {
	if (lista->inicio == NULL) {
		printf("Nenhuma disciplina cadastrada. Impossível realizar exclusão.\n");
	}else{
		long int cod, cod_turma;

		printf("Disciplinas cadastradas\n");
		imprime_lista_cadeiras(lista);
		printf("Informe o codigo da disciplina que você deseja excluir:\n");
		scanf("%ld", &cod);
		while(!cadeira_ja_cadastrada(lista, cod)){
			printf("Código não cadastrado. Informe novamente:\n");
			scanf("%ld", &cod);
		}
		cod_turma = busca_cod_turma_by_cod_cadeira(cod, lista_turmas);
		while(cod_turma != 0) {
			exclui_lista_turmas(lista_turmas, cod_turma);
			cod_turma = busca_cod_turma_by_cod_cadeira(cod, lista_turmas);
		}
		exclui_lista_cadeiras(lista, cod);
		printf("DISCIPLINA DE CODIGO '%ld' REMOVIDA COM SUCESSO.\n", cod);
	}
}

void exclui_avaliacao(struct l_descr_turma *lista_turmas, struct l_descr_cadeira *lista_cadeiras, struct l_descr_aluno *lista_alunos) {
	if (lista_turmas->inicio == NULL) {
		printf("Nenhuma turma cadastrada. Impossível realizar exclusão.\n");
	}else{
		long int mat, cod_turma;
		struct turma *turma;

		printf("Código da turma que você deseja excluir avaliação: \n");
		imprime_lista_turmas(lista_turmas, lista_cadeiras);
		scanf("%ld", &cod_turma);
		turma = turma_cadastrada(lista_turmas, cod_turma);
		while (turma == NULL) {
			printf("Turma inválida. Informe novamente o código: \n");
			scanf("%ld", &cod_turma);
			turma = turma_cadastrada(lista_turmas, cod_turma);
		}
		if (turma->lista_alunos->cont == 0) {
			printf("Nenhum aluno matriculado nessa turma. Impossível realizar exclusão de avaliação.\n");
		} else{
			printf("Informe a matrícula do aluno o qual voce deseja excluir a avaliação:\n");
			imprime_lista_avaliacoes(turma->lista_avaliacoes);
			scanf("%ld", &mat);
			while(!aluno_ja_matriculado_turma(turma->lista_alunos, busca_aluno_by_matricula(lista_alunos, mat))) {
				printf("Matricula inválida. Informe novamente:\n");
				scanf("%ld", &mat);
			}
			exclui_lista_avaliacoes(turma->lista_avaliacoes, mat);
			printf("AVALIACAO DE ALUNO DE MATRICULA '%ld' REMOVIDA COM SUCESSO.\n", mat);
		}
	}
}

///////////////////////FUNCOES DE BUSCA///////////////////////////
void busca_aluno(struct l_descr_aluno *lista) {
	long int mat;
	bool encontrou = false;

	printf("Informe a matrícula do aluno que você deseja buscar: \n");
	scanf("%ld", &mat);

	struct aluno *aux = lista->inicio;
	while (aux != NULL){
		if (aux->matricula == mat) {
			encontrou = true;
			printf("\nRESULTADO\n");
			printf("Nome: %s\n", aux->nome);
			printf("Matrícula: %ld\n", mat);
			printf("Curso: %s\n", aux->curso);
			printf("Lista de faltas: \n");
			struct falta *aux2 = aux->lista_faltas->inicio;
			if (aux->lista_faltas->inicio == NULL) {
				printf("Nenhuma falta registrada.\n");
			}else{
				while (aux2 != NULL){
					printf("->Falta na cadeira de código: %ld\n", aux2->cod_cadeira);
					aux2 = aux2->proximo;
				}	
			}
			printf("\n");
		}
		aux = aux->proximo;
	}
	if (!encontrou) {
		printf("Aluno não encontrado.\n");
	}
}

void busca_prof(struct l_descr_prof *lista) {
	long int siape;
	bool encontrou = false;

	printf("Informe a SIAPE do professor que você deseja buscar: \n");
	scanf("%ld", &siape);

	struct prof *aux = lista->inicio;
	while (aux != NULL){
		if (aux->siape == siape) {
			encontrou = true;
			printf("\nRESULTADO\n");
			printf("Nome: %s\n", aux->nome);
			printf("SIAPE: %ld\n", siape);
			printf("Área de atuação: %s\n", aux->area_atuacao);
			printf("Titulação: %s\n", aux->titulacao);
			printf("\n");
		}
		aux = aux->proximo;
	}
	if (!encontrou) {
		printf("Professor não encontrado.\n");
	}
}

void busca_cadeira(struct l_descr_cadeira *lista) {
	long int cod;
	bool encontrou = false;

	printf("Informe o código da cadeira que você deseja buscar: \n");
	scanf("%ld", &cod);

	struct cadeira *aux = lista->inicio;
	while (aux != NULL){
		if (aux->cod == cod) {
			encontrou = true;
			printf("\nRESULTADO\n");
			printf("Nome: %s\n", aux->nome);
			printf("Código: %ld\n", cod);
			printf("Carga Horária: %.2f\n", aux->carga_horaria);
			printf("Pré-requisito: %s\n", aux->pre_requisito);
			printf("\n");
		}
		aux = aux->proximo;
	}
	if (!encontrou) {
		printf("Cadeira não encontrada.\n");
	}
}

void busca_turma(struct l_descr_turma *lista) {
	long int cod;
	bool encontrou = false;

	printf("Informe o código da turma que você deseja buscar: \n");
	scanf("%ld", &cod);

	struct turma *aux = lista->inicio;
	while (aux != NULL){
		if (aux->cod == cod) {
			encontrou = true;
			printf("\nRESULTADO\n");
			printf("Código: %ld\n", cod);
			printf("Código da cadeira: %ld\n", aux->cod_cadeira);
			printf("Alunos:\n");
			imprime_lista_no_alunos(aux->lista_alunos);
			printf("Aulas:\n");
			if (aux->lista_aulas->inicio == NULL) {
				printf("Nenhuma aula registrada.\n");
			}else{
				imprime_lista_aulas(aux->lista_aulas);
			}
			printf("Professores: \n");
			if (aux->lista_profs->inicio == NULL) {
				printf("Nenhum professor registrado.\n");
			}else{
				imprime_lista_no_profs(aux->lista_profs);
			}
			printf("Avaliações: \n");
			if (aux->lista_avaliacoes->inicio == NULL){
				printf("Nenhuma avaliação cadastrada.\n");
			}else{			
				imprime_lista_avaliacoes(aux->lista_avaliacoes);
			}
			printf("\n");
		}
		aux = aux->proximo;
	}
	if (!encontrou) {
		printf("Turma não encontrada.\n");
	}
}

void busca_avaliacao(struct l_descr_turma *lista_turmas, struct l_descr_cadeira *lista_cadeiras) {
	long int cod_turma, mat;
	struct turma *turma;
	bool encontrou = false;

	printf("Turmas cadastradas\n");
	imprime_lista_turmas(lista_turmas, lista_cadeiras);
	printf("Informe o código da turma que você deseja buscar uma avaliação: \n");
	scanf("%ld", &cod_turma);
	while(!turma_ja_cadastrada(lista_turmas, cod_turma)){
		printf("Codigo inválido. Informe novamente:\n");
		scanf("%ld", &cod_turma);
	}
	printf("Informe a matrícula do aluno que você deseja buscar a avaliação: \n");
	scanf("%ld", &mat);

	turma = busca_turma_by_cod(lista_turmas, cod_turma);
	struct avaliacao *aux = turma->lista_avaliacoes->inicio;
	while (aux != NULL){
		if (aux->aluno->matricula == mat) {
			encontrou = true;
			printf("\nRESULTADO\n");
			printf("Matrícula do aluno: %ld\n", aux->aluno->matricula);
			printf("Nota 1: %.2f\n", aux->nota1);
			printf("Nota 2: %.2f\n", aux->nota2);
			printf("\n");
		}
		aux = aux->proximo;
	}
	if (!encontrou) {
		printf("Avaliação não encontrada.\n");
	}
}

///////////////////////FUNCOES DE MATRICULA///////////////////////
void vincula_aluno_turma(struct turma *turma, long int matricula, struct l_descr_aluno *lista_alunos) {
	struct aluno *aluno = busca_aluno_by_matricula(lista_alunos, matricula);
	insere_inicio_lista_no_alunos(turma->lista_alunos, aluno);		
	printf("ALUNO MATRICULADO COM SUCESSO!\n");
}

void matricula_aluno(struct l_descr_aluno *lista_alunos, struct l_descr_turma *lista_turmas, struct l_descr_cadeira *lista_cadeiras,
struct l_descr_curso *lista_cursos, struct l_descr_prof *lista_profs) {
	long int cod_turma, matricula;
	struct turma *turma;
	int cont=0;

	if (lista_turmas->inicio == NULL) {
		printf("Nenhuma turma cadastrada. Primeiro, realize o cadastro de uma turma.\n");
	}else if (lista_alunos->inicio == NULL){
		printf("Nenhum aluno cadastrado. Primeiro, realize o cadastro de um aluno.\n");
	} else{
		printf("Informe o código da turma que você deseja realizar a matrícula: \n");
		imprime_lista_turmas(lista_turmas, lista_cadeiras);
		scanf("%ld", &cod_turma);
		turma = turma_cadastrada(lista_turmas, cod_turma);
		while (turma == NULL) {
			printf("Turma inválida. Informe novamente o código: \n");
			scanf("%ld", &cod_turma);
			turma = turma_cadastrada(lista_turmas, cod_turma);
		}
		printf("Alunos cadastrados no sistema\n");
		imprime_lista_alunos(lista_alunos);
		while(turma->lista_alunos->cont < 50) {
			if (turma->lista_alunos->cont != lista_alunos->cont) {
				printf("Informe a matrícula do aluno que você deseja matricular na turma ou digite 0 para sair: \n");
				scanf("%ld", &matricula);
				if (matricula != 0) {
					while(!matricula_ja_cadastrada(lista_alunos, matricula) || aluno_ja_matriculado_turma(turma->lista_alunos,
					busca_aluno_by_matricula(lista_alunos, matricula))) {
						printf("Matrícula inválida. Informe novamente: \n");
						scanf("%ld", &matricula);
					}
					vincula_aluno_turma(turma, matricula, lista_alunos);
					printf("Alunos ja matriculados:\n");
					imprime_lista_no_alunos(turma->lista_alunos);
				}else{
					break;
				}
			}else{
				printf("Desculpe, não há mais alunos disponíveis para realizar matrícula.\n");
				break;
			}
		}
	}
} 

///////////////////////OUTRAS FUNÇÕES///////////////////////
void lancar_aulas(struct l_descr_turma *lista_turmas, struct l_descr_cadeira *lista_cadeiras, struct l_descr_curso *lista_cursos,
struct l_descr_prof *lista_profs) {
	if (lista_turmas->inicio == NULL) {
		printf("Nenhuma turma cadastrada.\n");
	}else{
		struct aula nova_aula;
		struct turma *turma;
		char data[25], conteudo[255];
		long int cod_turma;

		printf("Informe o código da turma que você deseja lançar aula: \n");
		imprime_lista_turmas(lista_turmas, lista_cadeiras);
		scanf("%ld", &cod_turma);
		turma = turma_cadastrada(lista_turmas, cod_turma);
		while (turma == NULL) {
			printf("Turma inválida. Informe novamente o código: \n");
			scanf("%ld", &cod_turma);
			turma = turma_cadastrada(lista_turmas, cod_turma);
		}
		setbuf(stdin, NULL);
		printf("Data da aula (dd/mm/aaaa):\n");
		fgets(data, 25, stdin);
		setbuf(stdin, NULL);
		printf("Conteúdo ministrado: \n");
		fgets(conteudo, 255, stdin);

		retira_espaco(data);
		retira_espaco(conteudo);

		strcpy(nova_aula.data, data);
		strcpy(nova_aula.conteudo, conteudo);

		insere_inicio_lista_aulas(turma->lista_aulas, nova_aula);
		printf("AULA LANÇADA COM SUCESSO\n");
	}
}

void lancar_faltas(struct l_descr_turma *lista_turmas, struct l_descr_cadeira *lista_cadeiras, struct l_descr_curso *lista_cursos,
struct l_descr_prof *lista_profs, struct l_descr_aluno *lista_alunos) {
	if (lista_turmas->inicio == NULL) {
		printf("Nenhuma turma cadastrada.\n");
	}else{
		struct falta nova_falta;
		struct turma *turma;
		struct aluno *aluno;
		struct aula *aula;
		long int id_aula, cod_turma, matricula;

		printf("Informe o código da turma que você deseja lançar faltas: \n");
		imprime_lista_turmas(lista_turmas, lista_cadeiras);
		scanf("%ld", &cod_turma);
		turma = turma_cadastrada(lista_turmas, cod_turma);
		while (turma == NULL) {
			printf("Turma inválida. Informe novamente o código: \n");
			scanf("%ld", &cod_turma);
			turma = turma_cadastrada(lista_turmas, cod_turma);
		}

		if (turma->lista_aulas->cont == 0) {
			printf("Nenhuma aula registrada nessa turma. Primeiro, lançe alguma aula no sistema.\n");
		} else{
			if (turma->lista_alunos->cont == 0) {
				printf("Nenhum aluno matriculado nessa turma. Primeiro, faça a matricula de um aluno.\n");
			} else {
				printf("Informe a aula que você deseja lançar faltas (Exemplo: se deseja lançar faltas para aula 1, informe 1): \n");
				printf("Aulas lançadas\n");
				imprime_lista_aulas(turma->lista_aulas);
				scanf("%ld", &id_aula);
				while (id_aula < 1 || id_aula > turma->lista_aulas->cont_id) {
					printf("Número informado inválido. Informe novamente: \n");
					scanf("%ld", &id_aula);
				}
				aula = busca_aula_by_id(turma->lista_aulas, id_aula);
				printf("Informe a matrícula do aluno que você deseja vincular a falta: \n");
				printf("Alunos matriculados na turma\n");
				imprime_lista_no_alunos(turma->lista_alunos);
				scanf("%ld", &matricula);
				aluno = busca_aluno_by_matricula(lista_alunos, matricula);
				while (aluno == NULL) {
					printf("Matricula inválida. Informe novamente: \n");
					scanf("%ld", &matricula);
					aluno = busca_aluno_by_matricula(lista_alunos, matricula);
				}
				while (!aluno_ja_matriculado_turma(turma->lista_alunos, aluno)) {
					printf("Matricula inválida. Informe novamente: \n");
					scanf("%ld", &matricula);
					aluno = busca_aluno_by_matricula(lista_alunos, matricula);
				}
				nova_falta.aluno = aluno;
				nova_falta.cod_cadeira = turma->cod_cadeira;
				insere_inicio_lista_faltas(aula->lista_faltas, nova_falta);
				insere_inicio_lista_faltas(aluno->lista_faltas, nova_falta);
				printf("Falta registrada com sucesso.\n");
			}
		}
	}
}

void gera_relatorio(struct l_descr_turma *lista_turmas, struct l_descr_aluno *lista_alunos, struct l_descr_cadeira *lista_cadeiras) {
	struct turma *aux = lista_turmas->inicio;
	struct cadeira *cadeira;
	float carga_horaria_min;
	int cont_faltas=0;
	bool aprovado_nota = false;

	printf("\t---------------RELATÓRIO---------------\n");
	while(aux != NULL) {
		cadeira = busca_cadeira_by_cod(aux->cod_cadeira, lista_cadeiras);
		printf("Turma: %ld | Cadeira: %s\n", aux->cod, cadeira->nome);
		carga_horaria_min = cadeira->carga_horaria*0.75;

		struct no_aluno *aux2 = aux->lista_alunos->inicio;
		while (aux2 != NULL) {
			cont_faltas = 0;
			struct aula *aux3 = aux->lista_aulas->inicio;
			while (aux3 != NULL) {
				struct falta *aux4 = aux3->lista_faltas->inicio;
				while (aux4 != NULL) {
					if (aux4->aluno->matricula == aux2->aluno->matricula) {
						cont_faltas++;
					}
					aux4 = aux4->proximo;
				}
				aux3 = aux3->proximo;
			}

			aprovado_nota = false;
			struct avaliacao *aux5 = aux->lista_avaliacoes->inicio;
			while (aux5 != NULL) {
				if (aux5->aluno->matricula == aux2->aluno->matricula) {
					if ((aux5->nota1 + aux5->nota2)/2 >= 7) {
						aprovado_nota = true;
					}
				}
				aux5 = aux5->proximo;
			}
			if (cadeira->carga_horaria-cont_faltas < carga_horaria_min) {
				printf("->Aluno: %s | Matrícula: %ld | Situação: REPROVADO POR FREQUÊNCIA.\n", aux2->aluno->nome, aux2->aluno->matricula);
			}else{
				if (aprovado_nota) {
					printf("->Aluno: %s | Matrícula: %ld | Situação: APROVADO.\n", aux2->aluno->nome, aux2->aluno->matricula);
				}else{
					printf("->Aluno: %s | Matrícula: %ld | Situação: REPROVADO.\n", aux2->aluno->nome, aux2->aluno->matricula);
				}
			}
			aux2 = aux2->proximo;
		}
		aux = aux->proximo;
	}
}

void menu_crud(int *opcao, int tipo) {
	if (tipo == 1) {
		printf("Que tipo de cadastro você deseja fazer?\n1 - Alunos\n2 - Professores\n3 - Disciplinas\n4 - Avaliações\n5 - Turmas\n6 - Cursos\n7 - Sair\n");
		scanf("%d", opcao);
		while(*opcao < 1 || *opcao > 7) {
			printf("Opção inválida. Informe novamente.\n");
			scanf("%d", opcao);
		}
	}else if (tipo == 2) {
		printf("Que tipo de exclusão você deseja fazer?\n1 - Alunos\n2 - Professores\n3 - Disciplinas\n4 - Avaliações\n5 - Turmas\n6 - Sair\n");
		scanf("%d", opcao);
		while(*opcao < 1 || *opcao > 6) {
			printf("Opção inválida. Informe novamente.\n");
			scanf("%d", opcao);
		}
	}else{
		printf("Que tipo de busca você deseja fazer?\n1 - Alunos\n2 - Professores\n3 - Disciplinas\n4 - Avaliações\n5 - Turmas\n6 - Sair\n");
		scanf("%d", opcao);
		while(*opcao < 1 || *opcao > 6) {
			printf("Opção inválida. Informe novamente.\n");
			scanf("%d", opcao);
		}
	}
}

void menu_inicial(int *opcao, struct l_descr_aluno *lista_alunos, struct l_descr_curso *lista_cursos, struct l_descr_prof *lista_profs,
	struct l_descr_cadeira *lista_cadeiras, struct l_descr_turma *lista_turmas) {
	printf("Qual operação voce deseja realizar?\n");
	printf("1 - Cadastro\n");
	printf("2 - Matrículas\n");
	printf("3 - Lançar aulas\n");
	printf("4 - Lançar faltas\n");
	printf("5 - Gerar relatório\n");
	printf("6 - Exclusão\n");
	printf("7 - Busca\n");
	printf("8 - Sair\n");	
	scanf("%d", opcao);

	while(*opcao < 1 || *opcao > 8) {
		printf("Opção inválida. Informe novamente.\n");
		scanf("%d", opcao);
	}

	if (*opcao == 1) {

		menu_crud(opcao, 1);
		if (*opcao == 1) {
			cadastro_aluno(lista_alunos, lista_cursos);
		}else if (*opcao == 2){
			cadastro_prof(lista_profs);
		}else if (*opcao == 3){	
			cadastro_cadeira(lista_cadeiras, lista_cursos);
		}else if (*opcao == 4){
			cadastro_avaliacao(lista_alunos, lista_turmas, lista_cadeiras, lista_cursos, lista_profs);
		}else if (*opcao == 5){
			cadastro_turma(lista_turmas, lista_cadeiras, lista_cursos, lista_profs);
		}else if (*opcao == 6){
			cadastro_curso(lista_cursos);
		}else if (*opcao == 7){
			printf("Saindo...\n");			
		}

	}else if (*opcao == 2){
		matricula_aluno(lista_alunos, lista_turmas, lista_cadeiras, lista_cursos, lista_profs);
	}else if (*opcao == 3){
		lancar_aulas(lista_turmas, lista_cadeiras, lista_cursos, lista_profs);
	}else if (*opcao == 4){
		lancar_faltas(lista_turmas, lista_cadeiras, lista_cursos, lista_profs, lista_alunos);
	}else if (*opcao == 5){
		gera_relatorio(lista_turmas, lista_alunos, lista_cadeiras);
	}else if (*opcao == 6){

		menu_crud(opcao, 2);
		if (*opcao == 1) {
			exclui_aluno(lista_alunos, lista_turmas);
		}else if (*opcao == 2){
			exclui_prof(lista_profs, lista_turmas, lista_cadeiras);
		}else if (*opcao == 3){	
			exclui_cadeira(lista_cadeiras, lista_turmas);
		}else if (*opcao == 4){
			exclui_avaliacao(lista_turmas, lista_cadeiras, lista_alunos);
		}else if (*opcao == 5){
			exclui_turma(lista_turmas, lista_cadeiras);
		}else if (*opcao == 6){
			printf("Saindo...\n");			
		}

	}else if (*opcao == 7){

		menu_crud(opcao, 3);
		if (*opcao == 1) {
			busca_aluno(lista_alunos);
		}else if (*opcao == 2){
			busca_prof(lista_profs);
		}else if (*opcao == 3){	
			busca_cadeira(lista_cadeiras);
		}else if (*opcao == 4){
			busca_avaliacao(lista_turmas, lista_cadeiras);
		}else if (*opcao == 5){
			busca_turma(lista_turmas);
		}else if (*opcao == 6){
			printf("Saindo...\n");			
		}
		
	}else if (*opcao == 8){
		return;
	}
}

void libera_lista_alunos(struct l_descr_aluno *lista) {
	int cont = lista->cont, i;
	for (i=0;i<cont;i++){
		exclui_inicio_lista_alunos(lista, lista->inicio);
	}
}

void libera_lista_cursos(struct l_descr_curso *lista) {
	int cont = lista->cont, i;
	for (i=0;i<cont;i++){
		exclui_inicio_lista_cursos(lista, lista->inicio);
	}
}

void libera_lista_cadeiras(struct l_descr_cadeira *lista) {
	int cont = lista->cont, i;
	for (i=0;i<cont;i++){
		exclui_inicio_lista_cadeiras(lista, lista->inicio);
	}
}

void libera_lista_turmas(struct l_descr_turma *lista) {
	int cont = lista->cont, i;
	for (i=0;i<cont;i++){
		exclui_inicio_lista_turmas(lista, lista->inicio);
	}
}

void libera_lista_profs(struct l_descr_prof *lista) {
	int cont = lista->cont, i;
	for (i=0;i<cont;i++){
		exclui_inicio_lista_profs(lista, lista->inicio);
	}
}

void libera_lista_aulas(struct l_descr_aula *lista) {
	int cont = lista->cont, i;
	for (i=0;i<cont;i++){
		exclui_inicio_lista_aulas(lista, lista->inicio);
	}
}

void libera_lista_faltas(struct l_descr_falta *lista) {
	int cont = lista->cont, i;
	for (i=0;i<cont;i++){
		exclui_inicio_lista_faltas(lista);
	}
}

void libera_lista_no_alunos(struct l_descr_no_aluno *lista) {
	int cont = lista->cont, i;
	for (i=0;i<cont;i++){
		exclui_inicio_lista_no_alunos(lista, lista->inicio);
	}
}

void libera_lista_no_profs(struct l_descr_no_prof *lista) {
	int cont = lista->cont, i;
	for (i=0;i<cont;i++){
		exclui_inicio_lista_no_profs(lista, lista->inicio);
	}
}

void libera_lista_avaliacoes(struct l_descr_avaliacao *lista) {
	int cont = lista->cont, i;
	for (i=0;i<cont;i++){
		exclui_inicio_lista_avaliacoes(lista, lista->inicio);
	}
}

int main(){

	int opcao = 1;
	struct l_descr_aluno alunos_cadastrados;
	struct l_descr_curso cursos_cadastrados;
	struct l_descr_prof profs_cadastrados;
	struct l_descr_cadeira cadeiras_cadastradas;
	struct l_descr_turma turmas_cadastradas;

	inicializa_lista_cursos(&cursos_cadastrados);
	inicializa_lista_alunos(&alunos_cadastrados);
	inicializa_lista_profs(&profs_cadastrados);
	inicializa_lista_cadeiras(&cadeiras_cadastradas);
	inicializa_lista_turmas(&turmas_cadastradas);

	while (opcao == 1) {
		menu_inicial(&opcao, &alunos_cadastrados, &cursos_cadastrados, &profs_cadastrados, &cadeiras_cadastradas, &turmas_cadastradas);
		printf("Deseja realizar outra operação? 1-SIM e 2-NÃO\n");
		scanf("%d", &opcao);
		while(opcao != 1 && opcao != 2) {
			printf("Opção inválida. Informe novamente.\n");
			scanf("%d", &opcao);
		}
	}

	struct turma *aux_turma = turmas_cadastradas.inicio;
	while (aux_turma != NULL) {
		struct aula *aux_aula = aux_turma->lista_aulas->inicio;
		while (aux_aula != NULL) {
			libera_lista_faltas(aux_aula->lista_faltas);
			aux_aula = aux_aula->proximo;
		}
		libera_lista_aulas(aux_turma->lista_aulas);
		libera_lista_avaliacoes(aux_turma->lista_avaliacoes);
		libera_lista_no_profs(aux_turma->lista_profs);
		libera_lista_no_alunos(aux_turma->lista_alunos);
		aux_turma = aux_turma->proximo;
	}
	libera_lista_alunos(&alunos_cadastrados);
	libera_lista_cursos(&cursos_cadastrados);
	libera_lista_profs(&profs_cadastrados);
	libera_lista_cadeiras(&cadeiras_cadastradas);
	libera_lista_turmas(&turmas_cadastradas);

	return 0;
}
