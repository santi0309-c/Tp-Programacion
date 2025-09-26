#include "federada.h"

void construirTree(Federada *FedBlock) {
    int hojas = FedBlock->cantHojas;
    if (hojas == 0) {
        free(FedBlock->treeValidation);
        FedBlock->treeValidation = NULL;
        FedBlock->longTree = 0;
        return;
    }
    int potDos = followPotenciaDos(hojas);
    int longTree = 2 * potDos;
    if (FedBlock->treeValidation) 
        free(FedBlock->treeValidation);

    FedBlock->treeValidation = calloc(longTree, sizeof(long long));
    FedBlock->longTree = longTree;
    int firstHoja = potDos;
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

Federada* crearFederada(int cantBlocks) {
    Federada *FedBlock = malloc(sizeof(Federada));
    FedBlock->cantHojas = cantBlocks > 0 ? cantBlocks : 1;
    int cantNodos = 2*followPotenciaDos(FedBlock->cantHojas);
    FedBlock->capacidadTree = cantNodos; 
    FedBlock->BlockchainsArray = calloc(cantNodos, sizeof(Blockchain*)); 
    FedBlock->treeValidation = NULL;
    FedBlock->longTree = 0;
    FedBlock->lastPrimo = 2;
    return FedBlock;
}

void federadaActuCant(Federada *FedBlock, int cantNuevaBlocks) {
    if (cantNuevaBlocks <= FedBlock->capacidadTree) 
        return;

    FedBlock->BlockchainsArray = realloc(FedBlock->BlockchainsArray, cantNuevaBlocks * sizeof(Blockchain*));
    
    for (int i = FedBlock->capacidadTree; i < cantNuevaBlocks; i++) {
        FedBlock->BlockchainsArray[i] = NULL;
    }
    FedBlock->capacidadTree = cantNuevaBlocks;
}

void liberarFederada(Federada *FedBlock) {
    if (!FedBlock) return;
    for (int i = 0; i < FedBlock->cantHojas; ++i) liberaBlockchain(FedBlock->BlockchainsArray[i]);
    free(FedBlock->BlockchainsArray);
    free(FedBlock->treeValidation);
    free(FedBlock);
}

void federadaAgregarBlock(Federada *FedBlock) {
    if (FedBlock->cantHojas >= FedBlock->capacidadTree) {
        federadaActuCant(FedBlock, FedBlock->capacidadTree * 2);
    }
    FedBlock->BlockchainsArray[FedBlock->cantHojas] = crearBlockchain();
    FedBlock->cantHojas++;
    construirTree(FedBlock);
}

int followPotenciaDos(int nro){
    int pDos = 1;
    while (pDos < nro) pDos <<= 1;
    return pDos;
}

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