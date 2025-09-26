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
    int hojas = FedBlock->cantHojas;
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
            else FedBlock->treeValidation[indexH] = 1;
        } else {
            FedBlock->treeValidation[indexH] = 1;
        }
    }
    for (int i = firstHoja - 1; i >= 1; --i) {
        long long izq = FedBlock->treeValidation[2*i];
        long long der = FedBlock->treeValidation[2*i + 1];
        FedBlock->treeValidation[i] = izq * der;
    }
}

void actualizarHoja(Federada *FedBlock, int indexHoja, long long id) {
    if (!FedBlock->treeValidation) return;
    int hojas = FedBlock->cantHojas;
    int potDos = followPotenciaDos(hojas);
    int indexCambiar = potDos + indexHoja;
    FedBlock->treeValidation[indexCambiar] = id;
    while (indexCambiar > 0) {
        if(indexCambiar % 2 == 1){
            indexCambiar = (indexCambiar - 1) / 2;
        } else{
            indexCambiar = indexCambiar / 2;
        }
        FedBlock->treeValidation[indexCambiar] = FedBlock->treeValidation[2*indexCambiar] * FedBlock->treeValidation[2*indexCambiar + 1];
    }
}