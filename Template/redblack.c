#include "redblack.h"

#include <stdlib.h>
#include <string.h>

struct aluno* getAluno(){
    struct aluno* retorno = malloc(sizeof(struct aluno));
    if(!retorno)
        matarProgramaFaltaMemoria();
    retorno->nome = malloc(sizeof("SEU_NOME"));//sizeof conta o \0
	if(!retorno->nome)
		matarProgramaFaltaMemoria();
    retorno->nomeDinf = malloc(sizeof("NOME_NAS_SERVIDORAS_DINF"));
    if(!retorno->nomeDinf)
        matarProgramaFaltaMemoria();
    
	strcpy(retorno->nome, "SEU_NOME");
    strcpy(retorno->nomeDinf, "NOME_NAS_SERVIDORAS_DINF");
    retorno->grr = 1234;

	return retorno;
}

void imprimirDadosAluno(){
    struct aluno* aluno = getAluno();
    
    printf("Trabalho de %s\n", aluno->nome);
    printf("Login Dinf %s\n", aluno->nomeDinf);
    printf("GRR %u\n\n", aluno->grr);

    free(aluno->nome);
    free(aluno->nomeDinf);
    free(aluno);

    return;
}

struct nodo* inserir(struct nodo** raiz, int chave){

}

int excluir(struct nodo** raiz, int chave){

}

struct nodo* buscar(struct nodo* raiz, int chave){

}

void imprimirEmOrdem(struct nodo* nodo){

}

void imprimirEmLargura(struct nodo* raiz){
    
}