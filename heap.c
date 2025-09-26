#include "heap.h"

void modificar_dato(long long tree[], long long nro_agregar, int posc_agregar){
    tree[posc_agregar] = nro_agregar;

    if (posc_agregar <= 1)
        return;
    
    if (posc_agregar % 2 == 1){
        posc_agregar = (posc_agregar - 1) / 2;
    } else{
        posc_agregar = posc_agregar / 2;
    }
    
    tree[posc_agregar] = tree[posc_agregar * 2] * tree[posc_agregar * 2 + 1];
    
    modificar_dato(tree, tree[posc_agregar], posc_agregar);
    return; 
}

int followPotenciaDos(int nro){
    int pDos = 1;
    while (pDos < nro) pDos <<= 1;
    return pDos;
}


void construirTree(Federada *FedBlock) {
    int hojas = FedBlock->cantBlock;
    if (hojas == 0) {
        free(FedBlock->treeValidation);
        FedBlock->treeValidation = NULL;
        FedBlock->longTree = 0;
        return;
    }
    int potDos = followPotenciaDos(hojas);
    int longTree = 2 * pot2;
    if (FedBlock->treeValidation) 
        free(FedBlock->treeValidation);

    FedBlock->treeValidation = calloc(longTree, sizeof(long long));
    FedBlock->longTree = longTree;
    int firstHoja = pot2;
    for (int i = 0; i < firstHoja; ++i) {
        int indexH = firstHoja + i;
        if (i < hojas) {
            Blockchain *blockC = FedBlock->BlockchainsArray[i];
            if (blockC && blockC->ultimo) 
                FedBlock->treeValidation[indexH] = blockC->ultimo->id;
            else FedBlock->treeValidation[indexH] = NULL;
        } else {
            FedBlock->treeValidation[indexH] = NULL;
        }
    }
    for (int i = firstHoja - 1; i >= 1; --i) {
        long long izq = FedBlock->treeValidation[2*i];
        long long der = FedBlock->treeValidation[2*i + 1];
        FedBlock->treeValidation[i] = izq * der;
    }
}