#include "arvoreB.h"

int main (){

    struct arvoreB *arvore;

    arvore = criarArvoreB(7);

    for (int32_t i = 1; i <= 12; i++)
        inserirArvoreB(arvore, i);
    
    printf("\n");

    imprimirArvoreB(arvore);

    printf("\n");

    imprimirEmOrdem(arvore);

    deletarArvore(arvore);

    return 0;
}