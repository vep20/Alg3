#ifndef ARVORE_B_H_
#define ARVORE_B_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
 
// estrutura de um nodo para arvorB
struct nodo {
    int32_t n_chaves; // numero de chaves em um nodo 
    int32_t *chaves; // chaves do nodo 
    struct nodo **filhos; // ponteiro para array dos filhos de cada nodo
    bool eh_folha; // booleano que informa se o nodo é folha ou não é 
};

// estrutura da arvoreB
struct arvoreB {
  struct nodo *raiz; // ponteiro para um nodo raiz
  int32_t t_arvore; // grau minimo da arvore 
};

// fução para alocação de um nodo, retorna o nodo em caso de sucesso
// ou mensagem de erro em caso de falha
struct nodo *cria_nodo (int32_t t_arvore, bool eh_folha);

// função para alocação de uma arvoreB seguindo especificações Cormen
// retorna a arvore em caso de sucesso ou mensagem de erro
struct arvoreB* criarArvoreB(int32_t t_arvore);

void inserirArvoreB(struct arvoreB* arvore, int32_t chave);

void imprimirArvoreB(struct arvoreB* arvore);

void imprimirEmOrdem(struct arvoreB* arvore);

struct nodo* buscarArvoreB(struct arvoreB* arvore, int32_t chave,
                            int32_t* idxEncontrado);
                            
void deletarArvore(struct arvoreB* arvore);

// função para imprimir mensagem de erro e encerrar execução 
void erro (char *msg);

#endif