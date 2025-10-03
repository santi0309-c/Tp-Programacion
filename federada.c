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
    for (int i = 0; i < cantNodos; i++) {
        FedBlock->BlockchainsArray[i] = crearBlockchain();
    }
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
    if (FedBlock->BlockchainsArray) {
        for (int i = 0; i < FedBlock->cantHojas; ++i) {
            if (FedBlock->BlockchainsArray[i]) {
                printf("Liberando blockchain %d\n", i);
                liberaBlockchain(FedBlock->BlockchainsArray[i]);
                printf("Blockchain %d liberada\n", i);
            }
        printf("Libere blockchain %d\n", i);
        }
        free(FedBlock->BlockchainsArray);
    }
    if (FedBlock->treeValidation) {
        free(FedBlock->treeValidation);
    }
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

void modificar_dato(Federada *Fedblock, int bcModificar, long long id_nodoModificar, char mensajeNuevo[]){
    
    Blockchain *cambio = Fedblock->BlockchainsArray[bcModificar]; 



    Nodo *nodoCambiar = cambio->ultimo;
    while (nodoCambiar != NULL && nodoCambiar->id != id_nodoModificar){
        nodoCambiar = nodoCambiar->anterior;
    }
    if (nodoCambiar == NULL){
        fprintf(stderr, "No se encontro el nodo a modificar\n");
        return;
    }
    
    free(nodoCambiar->mensaje);
    nodoCambiar->mensaje = strdup(mensajeNuevo ? mensajeNuevo : "");

    unsigned long long ultimo = Fedblock->lastPrimo;
    while (nodoCambiar != NULL){
        unsigned long long *p = primos(ultimo);
        nodoCambiar->id = *p;
        ultimo = *p;
        nodoCambiar = nodoCambiar->siguiente;
    }

    free(cambio);
    
    return; 
}


void actualizarHoja(Federada *FedBlock, int indexHoja, long long id) {
    if (!FedBlock->treeValidation) return;
    int hojas = FedBlock->cantHojas;
    int potDos = followPotenciaDos(hojas);
    int indexCambiar = potDos + indexHoja;
    FedBlock->treeValidation[indexCambiar] = id;
    while (indexCambiar > 1) {
        indexCambiar /= 2;
        FedBlock->treeValidation[indexCambiar] = FedBlock->treeValidation[2*indexCambiar] * FedBlock->treeValidation[2*indexCambiar + 1];
    }
}