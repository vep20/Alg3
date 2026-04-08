#include "arvoreB.h"

void erro (char *msg){
    fprintf (stderr, "ERRO: %s\n", msg);
    exit (1);
}

//pronto
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

//pronto
struct arvoreB *criarArvoreB (int32_t t_arvore){
    struct arvoreB *nova_arvore;

    nova_arvore = malloc (sizeof (struct arvoreB));
    if (!nova_arvore)
        erro ("Falha ao alocar memoria para arvore");

    nova_arvore->t_arvore = t_arvore;

    // cria o nodo e preenche os membros para armazenar na arvore 
    nova_arvore->raiz = cria_nodo (t_arvore, true);
    
    return nova_arvore;
}

//imcompleto
void dividir_filho (struct nodo *nodo, int32_t indice, int32_t t_arvore){
    struct nodo *aux, *novo_nodo;

    aux = nodo->filhos[indice];
    novo_nodo = cria_nodo (t_arvore, aux->eh_folha);
    novo_nodo->n_chaves = t_arvore - 1;

    for (int32_t i = 0; i < t_arvore - 1; i++)
        novo_nodo->chaves[i] = aux->chaves[i + t_arvore];

    if (!aux->eh_folha)
        for (int32_t i = 0; i < t_arvore; i++)
            novo_nodo->filhos[i] = aux->filhos[i + t_arvore];

    aux->n_chaves = t_arvore;

}

//imcompleto
void inserir_não_cheio (struct nodo *nodo, int32_t chave, int32_t t_arvore){
    int32_t aux;

    aux = nodo->n_chaves;

    if (nodo->eh_folha){
        // descoloca as chaves maiores do nodo para abrir espaço para nova
        // ser inserida - adaptado para c
        while ((aux > 0) && (chave < nodo->chaves[aux - 1])){
            nodo->chaves[aux] = nodo->chaves[aux - 1];
            aux--;
        }

        nodo->chaves[aux] = chave;
        nodo->n_chaves++; // atualiza quantidade de chaves no nodo
    }

    else{
        // encontra o filho ao qual descer 
        while ((aux > 0) && (chave < nodo->chaves[aux - 1]))
            aux--;

        // realiza a divisão do filho se ele já esta cheio
        if (nodo->filhos[aux]->n_chaves ==  (2 * t_arvore - 1)){
            //dividir_filho (nodo, aux); //faltando argumentos da função

            // verificação para saber se a chave desce para o filho a direita
            if (chave > nodo->chaves[aux])
                aux++;
        }

        //chamada recursiva descendo para o filho
        inserir_não_cheio (nodo->filhos[aux], chave, t_arvore);
    }
}

//incompleto
struct nodo *dividir_Raiz (struct arvoreB *arvore){
    struct nodo *nova_raiz;

    nova_raiz = cria_nodo(arvore->t_arvore, false);
    nova_raiz->filhos[0] = arvore->raiz; // adaptado para linguagem c
    arvore->raiz = nova_raiz;
    
    //dividir_filho (nova_raiz, 0);// faltando argumentos da função
    
    return nova_raiz;
}

//pronto
void inserirArvoreB (struct arvoreB* arvore, int32_t chave){
    struct nodo *aux, *novo_nodo;

    aux = arvore->raiz;
    // verificar se o nodo já esta cheio, ou seja as 2t-1 preenchidas
    if (aux->n_chaves == (2 * arvore->t_arvore - 1)){
        novo_nodo = dividir_Raiz (arvore);
        inserir_não_cheio (novo_nodo, chave, arvore->t_arvore);
    }

    else 
        // insere na raiz, pois é o unico nodo
        inserir_não_cheio(aux, chave, arvore->t_arvore);

}

//Estrutura da fila para impressão hierárquica da arvoreB

// Nó da fila que guarda um ponteiro para um nó da arvore B
struct no_fila{
    struct nodo *nodo_arvore;
    struct no_fila *prox;
};

// Controle da fila
struct Fila{
    struct no_fila *inicio;
    struct no_fila *fim;
    int tamanho;
};

// inicializando a fila
struct Fila* criarFila(){
    struct Fila *fila = malloc(sizeof(struct Fila));

    if (!fila)
        erro("Falha ao alocar memoria para fila");

    fila->inicio = NULL;
    fila->fim = NULL;
    fila->tamanho = 0;

    return fila;
}

// insere os nodos da arvoreB na fila para impressão hierárquica
void inserir_fila(struct Fila *fila, struct nodo *nodo_atual){
    if(!fila || !nodo_atual)
        erro("Fila ou nodo nulo");

    struct no_fila *novo_no_fila = malloc(sizeof(struct no_fila));

    if (!novo_no_fila)
        erro("Falha ao alocar memoria para nó da fila");

    novo_no_fila->nodo_arvore = nodo_atual;
    novo_no_fila->prox = NULL;

    if (fila->fim)
        fila->fim->prox = novo_no_fila;
    else
        fila->inicio = novo_no_fila;

    fila->fim = novo_no_fila;
    fila->tamanho++;
}

// remove os nodos da fila para impressão hierárquica, retornando o nodo da arvoreB
struct nodo *remover_fila(struct Fila *fila){
    if(!fila || !fila->inicio)
        erro("Fila vazia");

    struct no_fila *aux = fila->inicio;
    struct nodo *info = aux->nodo_arvore;

    fila->inicio = aux->prox;
    if (!fila->inicio)
        fila->fim = NULL;

    free(aux);
    fila->tamanho--;

    return info;
}

// verifica se a fila esta vazia
bool fila_vazia(struct Fila *fila){
    return fila->tamanho == 0;
}

void liberar_fila(struct Fila *fila){
    if(!fila)
        return;
    while (!fila_vazia(fila))
        remover_fila(fila);
    free(fila);
}
// fim da estrutura de fila

//pronto
void imprimirArvoreB(struct arvoreB* arvore){
    if(!arvore || !arvore->raiz)
        erro("Arvore vazia");

    struct Fila *fila = criarFila();
    if(!fila)
        erro("Falha ao criar fila");
    
    int nivel, nos_nivel_atual;
    
    nivel = 0;
    
    //incia a busca em largura, inserindo a raiz da arvore na fila
    inserir_fila(fila, arvore->raiz);

    while (!fila_vazia(fila)){
        // recebe quantos nodos tem no nivel atual para controle de impressão
        nos_nivel_atual = fila->tamanho;

        // cabeçalho do nivel
        printf("----//----\n");
        printf("Nivel %d:\n", nivel);
        printf("----//----\n");

        // percorre os nodos do nivel atual
        for(int i = 0; i < nos_nivel_atual; i++){
            struct nodo *nodo_atual = remover_fila(fila);

            // Indica se o nodo é interno ou folha
            printf("%c ", nodo_atual->eh_folha ? 'F' : 'I');

            //numero de chaves
            printf("(n:%d) [", nodo_atual->n_chaves);

            for(int j = 0; j < nodo_atual->n_chaves; j++){
                printf("%d", nodo_atual->chaves[j]);
                // espaço entre as chaves, mas não após a última
                if(j < nodo_atual->n_chaves - 1)
                    printf(" ");
            }
            printf("]");

            // espaçamento entre os nodos do mesmo nivel, mas não após o último
            if(i < nos_nivel_atual - 1)
                printf("        ");
                
            // insere os filhos dos nodos do nivel atual na fila para o próximo nivel
            if(!nodo_atual->eh_folha){
                for(int j = 0; j <= nodo_atual->n_chaves; j++){
                    if(nodo_atual->filhos[j] != nullptr)
                        inserir_fila(fila, nodo_atual->filhos[j]);
                }
            }
        }

        printf("\n");
        nivel++;
    }
    liberar_fila(fila);
}

// void imprimirEmOrdem(struct arvoreB* arvore){

// }

//pronto
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

//pronto
struct nodo* buscarArvoreB(struct arvoreB* arvore, int32_t chave, int32_t* idxEncontrado){
    struct nodo *aux;

    // chamada de função auxiliar para buscar chave recursivamente
    aux = buscarArvoreBrec (arvore->raiz, chave, idxEncontrado);
    return aux;    
}


// void deletarArvore(struct arvoreB* arvore){

// }    