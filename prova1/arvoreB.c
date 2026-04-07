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
    struct arvoreB *nova_arvore;

    nova_arvore = malloc (sizeof (struct arvoreB));
    if (!nova_arvore)
        erro ("Falha ao alocar memoria para arvore");

    nova_arvore->t_arvore = t_arvore;

    // cria o nodo e preenche os membros para armazenar na arvore 
    nova_arvore->raiz = cria_nodo (t_arvore, true);
         
    return nova_arvore;
}

void dividir_filho (struct nodo *nodo, int32_t indice){

}

void inserir_não_cheio (struct nodo *nodo, int32_t chave){
    
}

struct nodo *dividir_Raiz (struct arvoreB *arvore){
    struct nodo *nova_raiz;

    nova_raiz = cria_nodo(arvore->t_arvore, false);
    nova_raiz->filhos[1] = arvore->raiz;
    arvore->raiz = nova_raiz;
    
    dividir_filho (nova_raiz, 1);
    
    return nova_raiz;
}


void inserirArvoreB(struct arvoreB* arvore, int32_t chave){
    struct nodo *aux, *novo_nodo;

    aux = arvore->raiz;
    // verificar se o nodo já esta cheio, ou seja as 2t-1 preenchidas
    if (aux->n_chaves == (2 * arvore->t_arvore -1)){
        novo_nodo = dividir_Raiz (arvore);
        inserir_não_cheio (novo_nodo, chave);
    }

    else 
        // insere na raiz
        inserir_não_cheio(aux, chave);

}

// void imprimirArvoreB(struct arvoreB* arvore){

// }

// void imprimirEmOrdem(struct arvoreB* arvore){

// }

struct nodo* buscarArvoreBrec (struct nodo *atual, int32_t chave, int32_t* idxEncontrado){
    int32_t aux;

    aux = 0; // adaptado para vetores em c 
    // laço para não ultrapassar onde a chave esta ou "deveria" estar
    while ((aux < atual->n_chaves) && (chave > atual->chaves[aux]))
        aux++;

    if ((aux < atual->n_chaves) && (chave == atual->chaves[aux])){
        *idxEncontrado = aux;
        return atual;
    } 
    
    else if (atual->eh_folha)
        return NULL;
    
    atual = atual->filhos[aux]; // atual atualizado para ponteiro do filho 

    return buscarArvoreBrec (atual, chave, idxEncontrado); 
}

struct nodo* buscarArvoreB(struct arvoreB* arvore, int32_t chave, int32_t* idxEncontrado){
    struct nodo *aux;

    // chamada de função auxiliar para buscar chave recursivamente
    aux = buscarArvoreBrec (arvore->raiz, chave, idxEncontrado);
    return aux;    
}


// void deletarArvore(struct arvoreB* arvore){

// }
