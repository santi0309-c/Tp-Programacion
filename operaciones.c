#include "federada.h"


void federada_alta(Federada *FedBlock, int nroBlock, char *mensaje) {
    if (nroBlock >= FedBlock->cantHojas) {
        fprintf(stderr, "Índice fuera de rango en alta\n");
        return;
    }
    long long *primo = primos(FedBlock->lastPrimo);
    FedBlock->lastPrimo = *primo;
    Blockchain *b = FedBlock->BlockchainsArray[nroBlock];
    blockchain_agregar_id(b, *primo, mensaje);
    actualizarHoja(FedBlock, nroBlock, *primo);
}

void federada_modificar(Federada *FedBlock, int nroBlock, long long idAntiguo, char *mensajeNew) {
    if (nroBlock >= FedBlock->cantHojas) { fprintf(stderr, "Índice fuera de rango en modificar\n"); return; }
    Blockchain *b = FedBlock->BlockchainsArray[nroBlock];
    Nodo *inicio = blockchain_buscar_por_id(b, idAntiguo);
    if (!inicio) { fprintf(stderr, "ID no encontrado en la blockchain\n"); return; }
    free(inicio->mensaje);
    inicio->mensaje = strdup(mensajeNew ? mensajeNew : "");
    Nodo *actual = inicio;
    unsigned long long ultimo = FedBlock->lastPrimo;
    while (actual) {
        unsigned long long *p = primos(ultimo);
        actual->id = *p;
        ultimo = *p;
        actual = actual->siguiente;
    }
    FedBlock->lastPrimo = ultimo;
    unsigned long long id_final = b->ultimo ? b->ultimo->id : 1ULL;
    actualizarHoja(FedBlock, nroBlock, id_final);
}

int federada_validar(Federada *FedBlock) {
    for (int i = 0; i < FedBlock->cantHojas; i++) {
        Blockchain *blockchain = FedBlock->BlockchainsArray[i];
        Nodo *nodo = blockchain->ultimo;
        while (nodo->anterior){
            if (nodo->id < nodo->anterior->id) return 0;
            nodo = nodo->anterior;
        }
        int cont = 1;
        for (int o = FedBlock->longTree/2; o < (FedBlock->cantHojas + FedBlock->longTree/2); o++) {
            cont = cont * FedBlock->treeValidation[o];
        }
        if (cont != FedBlock->treeValidation[1]) return 0;
    }
    return 1;
}

int federada_validar_subconjunto(Federada *FedBlock, long long esperado, int minIdx, int maxIdx) {
    if (minIdx > maxIdx || maxIdx >= FedBlock->cantHojas) return 0;
    int producto = 1;
    
    if (minIdx%2 == 1){
        for (int i = minIdx; i <= maxIdx; ++i){
            producto = producto * FedBlock->treeValidation[(FedBlock->longTree/2) + i];
        }
    } else {
         for (int i = minIdx; i <= maxIdx; ++i){
            if (maxIdx >= i+2){
                producto = producto * FedBlock->treeValidation[((FedBlock->longTree/2) + i)/2];
            }
            else {
                producto = producto * FedBlock->treeValidation[(FedBlock->longTree/2) + i];
            }
        }
    }
}