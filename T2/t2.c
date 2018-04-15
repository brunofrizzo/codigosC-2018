#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

struct aluno {
	long int matricula;
	char nome[100];
	char curso[100];
	struct aluno *proximo;
	struct l_descr_avaliacao *lista_avaliacoes;
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
	// struct prof *proximo;
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
	struct curso *curso;
	char nome[70];
	int carga_horaria;
	char pre_requisito[250];
	struct cadeira *proximo;
};

struct aula{
	char data[25];
	char conteudo[250];
	long int cod_turma;
	struct aula *proximo;
	struct l_descr_falta *lista_faltas;
};

struct turma{
	long int cod;
	long int cod_cadeira;
	struct l_descr_no_aluno *lista_alunos;
	struct l_descr_aula *lista_aulas;
	struct l_descr_no_prof *lista_profs;
	struct turma *proximo;
};

struct avaliacao{
	int num;
	float nota;
	struct avaliacao *proximo;
};

struct falta{
	struct aluno aluno;
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

// void inicializa_lista(struct l_descr *lista) {
//     lista->fim = NULL;
//     lista->inicio = NULL;
//     lista->cont = 0;
// }

// void imprime_lista(struct l_descr *lista) {
//     struct no *aux = lista->inicio;
//     printf("Lista: \n");
//     while(aux !=  NULL) {
//         printf("->%d\n", aux->valor);
//         aux = aux->proximo;
//     }
// }

// int esta_vazia(struct l_descr *lista) {
//     if (lista->inicio == NULL) {
//         return 1;
//     } else {
//         return 0;
//     }
// }

// void insere_inicio(struct l_descr *lista, int val) {
//     if (esta_vazia(lista) == 1) {
//         lista->inicio = malloc(sizeof(struct no));
//         lista->inicio->valor = val;
//         lista->inicio->proximo = NULL;
//         lista->cont++;
//         lista->fim = lista->inicio;
//     }else{
//         struct no *aux = malloc(sizeof(struct no));
//         aux->valor = val;
//         aux->proximo = lista->inicio;
//         lista->inicio = aux;
//         lista->cont++;
//     }
// }

void inicializa_lista_cursos(struct l_descr_curso *lista) {
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->cont = 0;
}

void imprime_lista_cursos(struct l_descr_curso *lista) {
    struct curso *aux = lista->inicio;
    printf("Lista: \n");
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

void inicializa_lista_alunos(struct l_descr_aluno *lista) {
    lista->fim = NULL;
    lista->inicio = NULL;
    lista->cont = 0;
}

void imprime_lista_alunos(struct l_descr_aluno *lista) {
    struct aluno *aux = lista->inicio;
    printf("Lista: \n");
    while(aux !=  NULL) {
        printf("->%s\n", aux->nome);
        aux = aux->proximo;
    }
}

void insere_vazia_lista_alunos(struct l_descr_aluno *lista, long int matricula, char nome[], char curso[]) {
	lista->inicio = malloc(sizeof(struct aluno));
    lista->inicio->matricula = matricula;
    // lista->inicio->nome = nome;
    strcpy(lista->inicio->nome, nome);
    // lista->inicio->curso = curso;
    strcpy(lista->inicio->curso, curso);
    lista->inicio->proximo = NULL;
    lista->cont++;
    lista->fim = lista->inicio;
}

void insere_inicio_lista_alunos(struct l_descr_aluno *lista, long int matricula, char nome[], char curso[]) {
    if (lista->inicio == NULL) {
        insere_vazia_lista_alunos(lista, matricula, nome, curso);
    }else{
        struct aluno *aux = malloc(sizeof(struct aluno));
        aux->matricula = matricula;
	    // aux->nome = nome;
	    strcpy(aux->nome, nome);
	    // aux->curso = curso;
	    strcpy(aux->curso, curso);
        aux->proximo = lista->inicio;
        lista->inicio = aux;
        lista->cont++;
    }
}

bool matricula_ja_cadastrada(struct l_descr_aluno *lista_alunos, long int matricula) {
	struct aluno *aux = lista_alunos->inicio;

	while(aux != NULL){
		if (aux->matricula == matricula) {
			return true;
		}
		aux = aux->proximo;
	}
	return false;
}

void cadastro_aluno(struct l_descr_aluno *lista_alunos, struct l_descr_curso *lista_cursos) {

	char nome[100];
	char curso[100];
	// char len;
	long int matricula;

	printf("CADASTRO DE ALUNO\n");
	setbuf(stdin, NULL);
	printf("Informe o nome:\n");
	fgets (nome, 100, stdin);
	printf("Informe a matricula:\n");
	scanf("%ld", &matricula);
	while (matricula_ja_cadastrada(lista_alunos, matricula)) {
		printf("Matricula ja cadastrada. Informe novamente:\n");
		scanf("%ld", &matricula);
	}
	setbuf(stdin, NULL);
	printf("Informe o curso: \n");
	fgets (curso, 100, stdin);

	retira_espaco(curso);
	retira_espaco(nome);

	while (!curso_cadastrado(lista_cursos, curso)) {
		setbuf(stdin, NULL);
		printf("Curso nao cadastrado. Informe novamente: ");
		fgets (curso, 100, stdin);
		retira_espaco(curso);
	}


	insere_inicio_lista_alunos(lista_alunos, matricula, nome, curso);
	
}

void cadastro_curso(struct l_descr_curso *lista_cursos) {

	char nome[100];

	printf("CADASTRO DE CURSO\n");
	setbuf(stdin, NULL);
	printf("Informe o nome:\n");
	fgets(nome, 100, stdin);

	retira_espaco(nome);

	while (curso_cadastrado(lista_cursos, nome)) {
		setbuf(stdin, NULL);
		printf("Curso ja cadastrado. Informe novamente o curso: ");
		fgets(nome, 100, stdin);
		retira_espaco(nome);
	}

	insere_inicio_lista_cursos(lista_cursos, nome);
	
}

void menu_cadastro(int *opcao) {
	printf("Que tipo de cadastro você deseja fazer?\n1 - Alunos\n2 - Professores\n3 - Disciplinas\n4 - Avaliações\n5 - Turmas\n6 - Cursos\n");
	scanf("%d", opcao);

	while(*opcao < 1 || *opcao > 6) {
		printf("Opção inválida. Informe novamente.\n");
		scanf("%d", opcao);
	}
}

void menu_inicial(int *opcao, struct l_descr_aluno *alunos_cadastrados, struct l_descr_curso *cursos_cadastrados) {
	printf("Qual operação voce deseja realizar?\n1 - Cadastro\n2 - Matrículas\n3 - Lançar notas\n4 - Lançar aulas\n5 - Lançar faltas\n6 - Gerar relatório\n");
	scanf("%d", opcao);

	while(*opcao < 1 || *opcao > 6) {
		printf("Opção inválida. Informe novamente.\n");
		scanf("%d", opcao);
	}

	if (*opcao == 1) {
		menu_cadastro(opcao);
		if (*opcao == 1) {
			if (cursos_cadastrados->inicio == NULL){
				printf("Nenhum curso cadastrado.\n");
				printf("Deseja cadastrar novo curso? 1-SIM ou 2-NAO\n");
				scanf("%d", opcao);
				while(*opcao != 1 && *opcao != 2) {
					printf("Opção inválida. Informe novamente: \n");
					scanf("%d", opcao);
				}
				if (*opcao == 1) {
					cadastro_curso(cursos_cadastrados);
				}
			}else{
				cadastro_aluno(alunos_cadastrados, cursos_cadastrados);
				imprime_lista_alunos(alunos_cadastrados);

			}
		}else if (*opcao == 2){
			//professores
		}else if (*opcao == 3){
			//disciplinas
		}else if (*opcao == 4){
			//avaliacoes
		}else if (*opcao == 5){
			//turmas
		}else if (*opcao == 6){
			cadastro_curso(cursos_cadastrados);
			imprime_lista_cursos(cursos_cadastrados);
		}
	}else if (*opcao == 2){
		//matriculas
	}else if (*opcao == 3){
		//notas
	}else if (*opcao == 4){
		//aulas
	}else if (*opcao == 5){
		//faltas
	}else if (*opcao == 6){
		//relatorio
	}
}

int main(){

	int opcao;
	struct l_descr_aluno alunos_cadastrados;
	// struct l_descr_no_aluno alunos_cadastrados;
	struct l_descr_curso cursos_cadastrados;
	// struct l_descr_no_curso cursos_cadastrados;
	// struct l_descr_no_aluno ;
	struct l_descr_prof profs_cadastrados;
	struct l_descr_cadeira cadeira_cadastrados;
	struct l_descr_turma turmas_cadastrados;
	struct l_descr_avaliacao avaliacoes_cadastrados;

	inicializa_lista_cursos(&cursos_cadastrados);
	inicializa_lista_alunos(&alunos_cadastrados);

	menu_inicial(&opcao, &alunos_cadastrados, &cursos_cadastrados);

	printf("Deseja realizar outra operação? 1-SIM e 2-NÃO\n");
	scanf("%d", &opcao);

	while(opcao != 1 && opcao != 2) {
		printf("Opção inválida. Informe novamente.\n");
		scanf("%d", &opcao);
	}

	while (opcao == 1) {
		menu_inicial(&opcao, &alunos_cadastrados, &cursos_cadastrados);
		printf("Deseja realizar outra operação? 1-SIM e 2-NÃO\n");
		scanf("%d", &opcao);
		while(opcao != 1 && opcao != 2) {
			printf("Opção inválida. Informe novamente.\n");
			scanf("%d", &opcao);
		}
	}

	return 0;
}
