#include "arvoreB.h"

void erro (char *msg){
    fprintf (stderr, "ERRO: %s\n", msg);
    exit (1);
}

struct nodo *cria_nodo (int32_t t_arvore, bool eh_folha){
    struct nodo *novo_nodo;

    novo_nodo = malloc (sizeof (struct nodo));
    if (!novo_nodo)
        erro ("Falha ao alocar memoria para nodo");

    // valores iniciais para o nodo
    novo_nodo->n_chaves = 0;
    novo_nodo->eh_folha = eh_folha;

    // alocação conforme descrição do Cormen para nº max chaves e filhos
    novo_nodo->chaves = malloc (sizeof (int32_t) * (2 * t_arvore - 1));
    if (!novo_nodo->chaves)
        erro ("Falha ao alocar memoria para chaves de um nodo");

    novo_nodo->filhos = malloc (sizeof (struct nodo *) * (2 * t_arvore));
    if (!novo_nodo->filhos)
        erro ("Falha ao alocar memoria para filhos do nodo");

    return novo_nodo;
}

struct arvoreB *criarArvoreB(int32_t t_arvore){
    struct arvoreB *arvore;

    arvore = malloc (sizeof (struct arvoreB));
    if (!arvore)
        erro ("Falha ao alocar memoria para arvore");

    arvore->t_arvore = t_arvore;

    // cria o nodo e preenche os membros para armazenar na arvore 
    arvore->raiz = cria_nodo (t_arvore, true);
         
    return arvore;
}

// void inserirArvoreB(struct arvoreB* arvore, int32_t chave){

// }

// void imprimirArvoreB(struct arvoreB* arvore){

// }

// void imprimirEmOrdem(struct arvoreB* arvore){

// }

// função auxiliar para realizar a busca de forma recursiva (conforme Cormen)
struct nodo* buscarArvoreBrec (struct nodo *atual, int32_t chave, int32_t* idxEncontrado){
    // struct nodo *aux_atual;
    int32_t aux;

    aux = 0;// adaptado para vetores em c 
    while ((aux < atual->n_chaves) && (chave > atual->chaves[aux]))
        aux++;

    if ((aux < atual->n_chaves) && (chave == atual->chaves[aux])){
        *idxEncontrado = aux;
        return atual;
    } 
    
    else if (atual->eh_folha)
        return NULL;
    
    atual = atual->filhos[aux];

    return buscarArvoreBrec (atual, chave, idxEncontrado); 
}

struct nodo* buscarArvoreB(struct arvoreB* arvore, int32_t chave, int32_t* idxEncontrado){
    struct nodo *aux;

    aux = buscarArvoreBrec (arvore->raiz, chave, idxEncontrado);
    return aux;    
}


// void deletarArvore(struct arvoreB* arvore){

// }
