#include "federada.h"

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

void federadaActuCant(Federada *FedBlock, int cantNuevaBlocks); {
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
    for (int i = 0; i < FedBlock->cantHojas; ++i) liberar_blockchain(FedBlock->BlockchainsArray[i]);
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

