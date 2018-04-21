#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct aluno {
	long int matricula;
	char nome[100];
	char curso[100];
	struct aluno *proximo;
	// struct l_descr_avaliacao *lista_avaliacoes;
	struct l_descr_faltas *lista_faltas;
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

struct no_curso{
	struct curso *curso;
	struct no_curso *proximo;
};

struct cadeira{
	long int cod;
	char curso[100];
	char nome[70];
	int carga_horaria;
	char pre_requisito[250];
	struct cadeira *proximo;
};

struct aula{
	char data[25];
	char conteudo[250];
	// long int cod_turma;
	struct aula *proximo;
	struct l_descr_falta *lista_faltas;
};

struct turma{
	long int cod;
	long int cod_cadeira;
	struct l_descr_no_aluno *lista_alunos;
	struct l_descr_aula *lista_aulas;
	struct l_descr_no_prof *lista_profs;
	struct l_descr_no_avaliacao *lista_avaliacoes;
	struct turma *proximo;
};

struct avaliacao{
	float nota;
	long int matricula_aluno;
	// long int cod_cadeira;
	struct avaliacao *proximo;
};

struct no_avaliacao{
	struct avaliacao *avaliacao;
	struct no_avaliacao *proximo;
};

struct falta{
	long int matricula_aluno;
	long int cod_cadeira;
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

struct l_descr_no_curso{
	struct no_curso *inicio;
	int cont;
	struct no_curso *fim;
};

struct l_descr_cadeira{
	struct cadeira *inicio;
	int cont;
	struct cadeira *fim;
};

struct l_descr_aula{
	struct aula *inicio;
	int cont;
	struct aula *fim;
};

struct l_descr_turma{
	struct turma *inicio;
	int cont;
	struct turma *fim;
};

struct l_descr_avaliacao{
	struct avaliacao *inicio;
	int cont;
	struct avaliacao *fim;
};

struct l_descr_no_avaliacao{
	struct no_avaliacao *inicio;
	int cont;
	struct no_avaliacao *fim;
};

struct l_descr_falta{
	struct falta *inicio;
	int cont;
	struct falta *fim;
};

void retira_espaco(char *string) {
	int len = strlen(string);
	if (string[len - 1] == '\n') 
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

///////////////////////FUNCOES PARA LISTA DE ALUNOS///////////////////////
void inicializa_lista_alunos(struct l_descr_aluno *lista) {
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->cont = 0;
}

void imprime_lista_alunos(struct l_descr_aluno *lista) {
    struct aluno *aux = lista->inicio;
    while(aux !=  NULL) {
        printf("->Nome: %s | Matrícula: %ld\n", aux->nome, aux->matricula);
        aux = aux->proximo;
    }
}

void insere_vazia_lista_alunos(struct l_descr_aluno *lista, struct aluno aluno) {
	lista->inicio = malloc(sizeof(struct aluno));
    lista->inicio->matricula = aluno.matricula;
    strcpy(lista->inicio->nome, aluno.nome);
    strcpy(lista->inicio->curso, aluno.curso);
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

///////////////////////FUNCOES PARA LISTA DE AVALIACOES///////////////////////
void inicializa_lista_avaliacoes(struct l_descr_avaliacao *lista) {
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->cont = 0;
}

void imprime_lista_avaliacoes(struct l_descr_avaliacao *lista) {
    struct avaliacao *aux = lista->inicio;
    while(aux !=  NULL) {
        printf("->Nota: %f. Matricula do aluno: %ld\n", aux->nota, aux->matricula_aluno);
        aux = aux->proximo;
    }	
}

void insere_vazia_lista_avaliacoes(struct l_descr_avaliacao *lista, struct avaliacao avaliacao) {
	lista->inicio = malloc(sizeof(struct avaliacao));
	lista->inicio->nota = avaliacao.nota;  
	// lista->inicio->cod_cadeira = avaliacao.cod_cadeira;
	lista->inicio->matricula_aluno = avaliacao.matricula_aluno;
    lista->inicio->proximo = NULL;
    lista->cont++;
    lista->fim = lista->inicio;
}

void insere_inicio_lista_avaliacoes(struct l_descr_avaliacao *lista, struct avaliacao avaliacao) {
    if (lista->inicio == NULL) {
    	insere_vazia_lista_avaliacoes(lista, avaliacao);
    }else{
        struct avaliacao *aux = malloc(sizeof(struct avaliacao));
        aux->nota = avaliacao.nota;  
		// aux->cod_cadeira = avaliacao.cod_cadeira;
		aux->matricula_aluno = avaliacao.matricula_aluno;
        aux->proximo = lista->inicio;
        lista->inicio = aux;
        lista->cont++;
    }
}

bool avaliacao_ja_cadastrada(struct l_descr_avaliacao *lista, long int cod_cadeira, long int matricula_aluno) {
	struct avaliacao *aux = lista->inicio;

	while(aux != NULL){
		// if (aux->cod_cadeira == cod_cadeira && aux->matricula_aluno == matricula_aluno) {
		// 	return true;
		// }
		aux = aux->proximo;
	}
	return false;	
}

///////////////////////FUNCOES PARA LISTA DE TURMAS///////////////////////
void inicializa_lista_turmas(struct l_descr_turma *lista) {
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->cont = 0;
}

void imprime_lista_turmas(struct l_descr_turma *lista, struct l_descr_cadeira *lista_cadeiras) {
    struct turma *aux = lista->inicio;
    while(aux !=  NULL) {
        printf("->Turma %ld | Cadeira: %s | Numero de alunos %d| Número de profs %d\n", aux->cod, nome_cadeira_por_cod(lista_cadeiras, aux->cod_cadeira),
        aux->lista_alunos->cont, aux->lista_profs->cont);
        aux = aux->proximo;
    }	
}

void insere_vazia_lista_turmas(struct l_descr_turma *lista, struct turma turma) {
	lista->inicio = malloc(sizeof(struct turma));
    lista->cont++;  
	lista->inicio->cod = lista->cont;
	lista->inicio->cod_cadeira = turma.cod_cadeira;
	lista->inicio->lista_alunos = malloc(sizeof(struct l_descr_no_aluno));
    lista->inicio->lista_aulas = malloc(sizeof(struct l_descr_aula));
    lista->inicio->lista_profs = malloc(sizeof(struct l_descr_no_prof));
    lista->inicio->lista_avaliacoes = turma.lista_avaliacoes;
    lista->inicio->proximo = NULL;
    lista->fim = lista->inicio;
}

void insere_inicio_lista_turmas(struct l_descr_turma *lista, struct turma turma) {
    if (lista->inicio == NULL) {
    	insere_vazia_lista_turmas(lista, turma);
    }else{
        struct turma *aux = malloc(sizeof(struct turma));
        lista->cont++;
        aux->cod = lista->cont;  
		aux->cod_cadeira = turma.cod_cadeira;
		aux->lista_alunos = malloc(sizeof(struct l_descr_no_aluno));
		aux->lista_aulas = malloc(sizeof(struct l_descr_aula));
		aux->lista_profs = malloc(sizeof(struct l_descr_no_prof));
		aux->lista_avaliacoes = turma.lista_avaliacoes;
        aux->proximo = lista->inicio;
        lista->inicio = aux;
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

///////////////////////FUNCOES PARA LISTA DE NO_ALUNOS///////////////////////
void inicializa_lista_no_alunos(struct l_descr_no_aluno *lista) {
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->cont = 0;
}

void imprime_lista_no_alunos(struct l_descr_no_aluno *lista) {
    struct no_aluno *aux = lista->inicio;
    while(aux !=  NULL) {
        printf("->Aluno %s | Matricula: %ld\n", aux->aluno->nome, aux->aluno->matricula);
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

///////////////////////FUNCOES PARA LISTA DE NO_PROFS///////////////////////
void inicializa_lista_no_profs(struct l_descr_no_prof *lista) {
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->cont = 0;
}

void imprime_lista_no_profs(struct l_descr_no_prof *lista) {
    struct no_prof *aux = lista->inicio;
    while(aux !=  NULL) {
        printf("->Professor %s | SIAPE: %ld\n", aux->prof->nome, aux->prof->siape);
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

///////////////////////FUNCOES PARA LISTA DE AULAS///////////////////////
void inicializa_lista_aulas(struct l_descr_aula *lista) {
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->cont = 0;
}

void imprime_lista_aulas(struct l_descr_aula *lista) {
    struct aula *aux = lista->inicio;
    while(aux !=  NULL) {
        printf("->Aula do dia %s\n", aux->data);
        aux = aux->proximo;
    }	
}

void insere_vazia_lista_aulas(struct l_descr_aula *lista, struct aula aula) {
	lista->inicio = malloc(sizeof(struct aula));
    lista->cont++;
    strcpy(lista->inicio->data, aula.data); 
    strcpy(lista->inicio->conteudo, aula.conteudo); 
	// lista->inicio->cod_turma = aula.cod_turma;
	lista->inicio->lista_faltas = malloc(sizeof(struct l_descr_falta));
	lista->inicio->proximo = NULL;
    lista->fim = lista->inicio;
}

void insere_inicio_lista_aulas(struct l_descr_aula *lista, struct aula aula) {
    if (lista->inicio == NULL) {
    	insere_vazia_lista_aulas(lista, aula);
    }else{
        struct aula *aux = malloc(sizeof(struct aula));
        lista->cont++;
        strcpy(aux->data, aula.data);
        strcpy(aux->conteudo, aula.conteudo);
		// aux->cod_turma = aula.cod_turma;
		aux->lista_faltas = malloc(sizeof(struct l_descr_falta));  
        aux->proximo = lista->inicio;
        lista->inicio = aux;
    }
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
		printf("Nenhum curso cadastrado. Para prosseguir, preencha o cadastro de curso.\n");
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
	printf("Informe o curso: \n");
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
		printf("Nenhum curso cadastrado. Para prosseguir, preencha o cadastro de curso.\n");
		cadastro_curso(lista_cursos);
	}

	struct cadeira nova_cadeira;
	long int cod;
	char nome[100];
	char curso[100];
	char pre_requisito[250];
	int carga_horaria;

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
	scanf("%d", &carga_horaria);

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

void cadastro_avaliacao(struct l_descr_avaliacao *lista, struct l_descr_aluno *lista_alunos, struct l_descr_cadeira *lista_cadeiras, struct l_descr_curso *lista_cursos) {
	while(lista_alunos->inicio == NULL){
		printf("Nenhum aluno cadastrado. Para prosseguir, preencha o cadastro de aluno.\n");
		cadastro_aluno(lista_alunos, lista_cursos);
	}
	while(lista_cadeiras->inicio == NULL){
		printf("Nenhuma disciplina cadastrada. Para prosseguir, preencha o cadastro de disciplina.\n");
		cadastro_cadeira(lista_cadeiras, lista_cursos);
	}

	struct avaliacao nova_avaliacao;
	long int cod_cadeira, matricula_aluno;
	float nota;

	printf("---------------CADASTRO DE AVALIAÇÃO---------------\n");
	printf("Codigo da cadeira: \n");
	scanf("%ld", &cod_cadeira);
	while(!cadeira_ja_cadastrada(lista_cadeiras, cod_cadeira)) {
		printf("Cadeira não cadastrada. Informe novamente:\n");
		scanf("%ld", &cod_cadeira);
	}
	printf("Matricula do aluno:\n");
	scanf("%ld", &matricula_aluno);
	while(!matricula_ja_cadastrada(lista_alunos, matricula_aluno)) {
		printf("Matricula não cadastrada. Informe novamente:\n");
		scanf("%ld", &matricula_aluno);
	}

	// while(avaliacao_ja_cadastrada(lista, cod_cadeira, matricula_aluno)) {
	// 	printf("Avaliacao ja cadastrada para esses dados. Informe novamente os dados:\n");
	// 	printf("Codigo da cadeira: \n");
	// 	scanf("%ld", &cod_cadeira);
	// 	while(!cadeira_ja_cadastrada(lista_cadeiras, cod_cadeira)) {
	// 		printf("Cadeira não cadastrada. Informe novamente:\n");
	// 		scanf("%ld", &cod_cadeira);
	// 	}
	// 	printf("Matricula do aluno:\n");
	// 	scanf("%ld", &matricula_aluno);
	// 	while(!matricula_ja_cadastrada(lista_alunos, matricula_aluno)) {
	// 		printf("Matricula não cadastrada. Informe novamente:\n");
	// 		scanf("%ld", &matricula_aluno);
	// 	}
	// }

	printf("Informe a nota da avaliação:\n");
	scanf("%f", &nota);

	nova_avaliacao.nota = nota;
	// nova_avaliacao.cod_cadeira = cod_cadeira; 
	nova_avaliacao.matricula_aluno = matricula_aluno; 

	insere_inicio_lista_avaliacoes(lista, nova_avaliacao);
	printf("AVALIAÇÃO CADASTRADA COM SUCESSO!\n");
}

void cadastro_turma(struct l_descr_turma *lista, struct l_descr_cadeira *lista_cadeiras, struct l_descr_curso *lista_cursos, struct l_descr_prof *lista_profs) {
	while(lista_cadeiras->inicio == NULL){
		printf("Nenhuma disciplina cadastrada. Para prosseguir, preencha o cadastro de disciplina.\n");
		cadastro_cadeira(lista_cadeiras, lista_cursos);
	}
	while(lista_profs->inicio == NULL){
		printf("Nenhum professor cadastrado. Para prosseguir, preencha o cadastro de professores.\n");
		cadastro_prof(lista_profs);
	}

	struct turma nova_turma;
	long int cod_cadeira, siape;

	printf("---------------CADASTRO DE TURMA---------------\n");
	printf("Cadeiras cadastradas\n");
	imprime_lista_cadeiras(lista_cadeiras);
	printf("Codigo da cadeira: \n");
	scanf("%ld", &cod_cadeira);
	while(!cadeira_ja_cadastrada(lista_cadeiras, cod_cadeira)) {
		printf("Cadeira não cadastrada. Informe novamente:\n");
		scanf("%ld", &cod_cadeira);
	}

	nova_turma.lista_profs = malloc(sizeof(struct l_descr_no_prof));
	inicializa_lista_no_profs(nova_turma.lista_profs);
	printf("Professores cadastrados no sistema\n");
	imprime_lista_profs(lista_profs);
	printf("Informe o SIAPE do professor que você deseja vincular a turma ou digite 0 para sair: \n");
	scanf("%ld", &siape);
	while (siape != 0) {
		while(!prof_ja_cadastrado(lista_profs, siape) || prof_ja_vinculado_turma(nova_turma.lista_profs,
		busca_prof_by_siape(lista_profs, siape))) {
			printf("SIAPE inválida. Informe novamente: \n");
			scanf("%ld", &siape);
		}
		vincula_prof_turma(&nova_turma, siape, lista_profs);
		printf("Professores ja vinculados:\n");
		imprime_lista_no_profs(nova_turma.lista_profs);
		printf("Informe o SIAPE do professor que você deseja vincular a turma ou digite 0 para sair: \n");
		scanf("%ld", &siape);
	}

	nova_turma.cod = 0;
	nova_turma.cod_cadeira = cod_cadeira;

	insere_inicio_lista_turmas(lista, nova_turma);
	printf("TURMA CADASTRADA COM SUCESSO!\n");
}

///////////////////////FUNCOES DE EXCLUSAO///////////////////////
void exclui_aluno(struct l_descr_aluno *lista) {
	if (lista->inicio == NULL) {
		printf("Nenhum aluno cadastrado. Impossível realizar exclusão.\n");
	}else{
		long int matricula;

		printf("Alunos cadastrados\n");
		imprime_lista_alunos(lista);
		printf("Informe a matricula do aluno que você deseja excluir:\n");
		scanf("%ld", &matricula);
		while(!matricula_ja_cadastrada(lista, matricula)){
			printf("Matrícula inválida. Informe novamente:\n");
			scanf("%ld", &matricula);
		}
		exclui_lista_alunos(lista, matricula);
		printf("ALUNO DE MATRICULA '%ld' REMOVIDO COM SUCESSO.\n", matricula);
	}
}

void exclui_prof(struct l_descr_prof *lista) {
	if (lista->inicio == NULL) {
		printf("Nenhum professor cadastrado. Impossível realizar exclusão.\n");
	}else{
		long int siape;

		printf("Professores cadastrados\n");
		imprime_lista_profs(lista);
		printf("Informe o SIAPE do professor que você deseja excluir:\n");
		scanf("%ld", &siape);
		while(!prof_ja_cadastrado(lista, siape)){
			printf("SIAPE inválida. Informe novamente:\n");
			scanf("%ld", &siape);
		}
		exclui_lista_profs(lista, siape);
		printf("PROFESSOR DE SIAPE '%ld' REMOVIDO COM SUCESSO.\n", siape);
	}
}

void exclui_curso(struct l_descr_curso *lista) {

}

void exclui_turma(struct l_descr_turma *lista) {

}

void exclui_cadeira(struct l_descr_cadeira *lista) {

}

void exclui_avaliacao(struct l_descr_avaliacao *lista) {

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
		printf("Nenhuma turma cadastrada. Primeiro, preencha o cadastro de turma: \n");
		cadastro_turma(lista_turmas, lista_cadeiras, lista_cursos, lista_profs);
	}
	if (lista_alunos->inicio == NULL){
		printf("Nenhum aluno cadastrado. Primeiro, preencha o cadastro de aluno: \n");
		cadastro_aluno(lista_alunos, lista_cursos);
	}
	printf("Informe o código da turma que você deseja realizar a matrícula: \n");
	imprime_lista_turmas(lista_turmas, lista_cadeiras);
	scanf("%ld", &cod_turma);
	turma = turma_cadastrada(lista_turmas, cod_turma);
	while (turma == NULL) {
		printf("Turma inválida. Informe novamente o código: \n");
		scanf("%ld", &cod_turma);
		turma = turma_cadastrada(lista_turmas, cod_turma);
	}
	// turma->lista_alunos = malloc(sizeof(struct l_descr_no_aluno));
	inicializa_lista_no_alunos(turma->lista_alunos);
	printf("Alunos cadastrados no sistema\n");
	imprime_lista_alunos(lista_alunos);
	while(turma->lista_alunos->cont < 50) {
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
	}
} 

///////////////////////OUTRAS FUNÇÕES///////////////////////
void lancar_aulas(struct l_descr_turma *lista_turmas, struct l_descr_cadeira *lista_cadeiras, struct l_descr_curso *lista_cursos,
struct l_descr_prof *lista_profs) {
	if (lista_turmas->inicio == NULL) {
		printf("Nenhuma turma cadastrada. Primeiro, preencha o cadastro de turma: \n");
		cadastro_turma(lista_turmas, lista_cadeiras, lista_cursos, lista_profs);
	}
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
	printf("lista de aulas\n");
	imprime_lista_aulas(turma->lista_aulas);
}

void menu_crud(int *opcao, int tipo) {
	if (tipo == 1) {
		printf("Que tipo de cadastro você deseja fazer?\n1 - Alunos\n2 - Professores\n3 - Disciplinas\n4 - Avaliações\n5 - Turmas\n6 - Cursos\n7 - Sair\n");
	}else if (tipo == 2) {
		printf("Que tipo de exclusão você deseja fazer?\n1 - Alunos\n2 - Professores\n3 - Disciplinas\n4 - Avaliações\n5 - Turmas\n6 - Cursos\n7 - Sair\n");
	}else{
		printf("Que tipo de busca você deseja fazer?\n1 - Alunos\n2 - Professores\n3 - Disciplinas\n4 - Avaliações\n5 - Turmas\n6 - Cursos\n7 - Sair\n");
	}

	scanf("%d", opcao);

	while(*opcao < 1 || *opcao > 8) {
		printf("Opção inválida. Informe novamente.\n");
		scanf("%d", opcao);
	}
}

void menu_inicial(int *opcao, struct l_descr_aluno *lista_alunos, struct l_descr_curso *lista_cursos, struct l_descr_prof *lista_profs,
	struct l_descr_cadeira *lista_cadeiras, struct l_descr_turma *lista_turmas, struct l_descr_avaliacao *lista_avalicoes) {
	printf("Qual operação voce deseja realizar?\n1 - Cadastro\n2 - Matrículas\n3 - Lançar notas\n4 - Lançar aulas\n5 - Lançar faltas\n6 - Gerar relatório\n7 - Exclusão\n8 - Busca\n");
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
			cadastro_avaliacao(lista_avalicoes, lista_alunos, lista_cadeiras, lista_cursos);
		}else if (*opcao == 5){
			cadastro_turma(lista_turmas, lista_cadeiras, lista_cursos, lista_profs);
		}else if (*opcao == 6){
			cadastro_curso(lista_cursos);
		}else if (*opcao == 7){
			printf("Saindo...\n");			
		}

	}else if (*opcao == 2){
		//matriculas
		matricula_aluno(lista_alunos, lista_turmas, lista_cadeiras, lista_cursos, lista_profs);
	}else if (*opcao == 3){
		//notas
	}else if (*opcao == 4){
		//aulas

		lancar_aulas(lista_turmas, lista_cadeiras, lista_cursos, lista_profs);

	}else if (*opcao == 5){
		//faltas
	}else if (*opcao == 6){
		//relatorio
	}else if (*opcao == 7){
		//exclusao

		menu_crud(opcao, 2);
		if (*opcao == 1) {
			exclui_aluno(lista_alunos);
		}else if (*opcao == 2){
			exclui_prof(lista_profs);
		}else if (*opcao == 3){	
			// exclui_cadeira(lista_cadeiras, lista_cursos);
		}else if (*opcao == 4){
			// exclui_avaliacao(lista_avalicoes, lista_alunos, lista_cadeiras, lista_cursos);
		}else if (*opcao == 5){
			// exclui_turma(lista_turmas, lista_cadeiras, lista_cursos);
		}else if (*opcao == 6){
			// exclui_curso(lista_cursos);
		}else if (*opcao == 7){
			printf("Saindo...\n");			
		}

	}else if (*opcao == 8){
		//busca
		menu_crud(opcao, 3);
		if (*opcao == 1) {
			//aluno
		}else if (*opcao == 2){
			//prof
		}else if (*opcao == 3){	
			//cadeira
		}else if (*opcao == 4){
			//avaliacao
		}else if (*opcao == 5){
			//turma
		}else if (*opcao == 6){
			//curso
		}else if (*opcao == 7){
			printf("Saindo...\n");			
		}
	}
}

int main(){

	int opcao = 1;
	struct l_descr_aluno alunos_cadastrados;
	// struct l_descr_no_aluno alunos_cadastrados;
	struct l_descr_curso cursos_cadastrados;
	// struct l_descr_no_curso cursos_cadastrados;
	// struct l_descr_no_aluno ;
	struct l_descr_prof profs_cadastrados;
	struct l_descr_cadeira cadeiras_cadastradas;
	struct l_descr_turma turmas_cadastradas;
	struct l_descr_avaliacao avaliacoes_cadastradas;

	inicializa_lista_cursos(&cursos_cadastrados);
	inicializa_lista_alunos(&alunos_cadastrados);
	inicializa_lista_profs(&profs_cadastrados);
	inicializa_lista_cadeiras(&cadeiras_cadastradas);
	inicializa_lista_turmas(&turmas_cadastradas);
	inicializa_lista_avaliacoes(&avaliacoes_cadastradas);

	// menu_inicial(&opcao, &alunos_cadastrados, &cursos_cadastrados, &profs_cadastrados, &cadeiras_cadastradas, &turmas_cadastradas, &avaliacoes_cadastradas);

	// printf("Deseja realizar outra operação? 1-SIM e 2-NÃO\n");
	// scanf("%d", &opcao);

	// while(opcao != 1 && opcao != 2) {
	// 	printf("Opção inválida. Informe novamente.\n");
	// 	scanf("%d", &opcao);
	// }

	while (opcao == 1) {
		menu_inicial(&opcao, &alunos_cadastrados, &cursos_cadastrados, &profs_cadastrados, &cadeiras_cadastradas, &turmas_cadastradas, &avaliacoes_cadastradas);
		printf("Deseja realizar outra operação? 1-SIM e 2-NÃO\n");
		scanf("%d", &opcao);
		while(opcao != 1 && opcao != 2) {
			printf("Opção inválida. Informe novamente.\n");
			scanf("%d", &opcao);
		}
	}

	printf("ALUNOS:\n");
	imprime_lista_alunos(&alunos_cadastrados);
	printf("PROFESSORES: \n");
	imprime_lista_profs(&profs_cadastrados);
	printf("CURSOS:\n");
	imprime_lista_cursos(&cursos_cadastrados);
	printf("DISCIPLINAS:\n");
	imprime_lista_cadeiras(&cadeiras_cadastradas);
	printf("AVALIAÇÕES\n");
	imprime_lista_avaliacoes(&avaliacoes_cadastradas);
	printf("TURMAS\n");
	imprime_lista_turmas(&turmas_cadastradas, &cadeiras_cadastradas);

	return 0;
}
