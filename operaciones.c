#include "federada.h"

void federada_alta(Federada *FedBlock, int nroBlock, char *mensaje) {
    if (nroBlock >= FedBlock->nroHojas) {
        fprintf(stderr, "Índice fuera de rango en alta\n");
        return;
    }
    long long primo = primos(FedBlock->lastPrimo);
    FedBlock->lastPrimo = primo;
    blockchain_agregar_con_id(FedBlock->treeValidation[nroBlock], primo, mensaje);
    actualizarHoja(FedBlock, nroBlock, primo);
}

void federada_modificar(Federada *FedBlock, int nroBlock, long long idAntiguo, char *mensajeNew) {
    if (nroBlock >= FedBlock->cantHojas) { fprintf(stderr, "Índice fuera de rango en modificar\n"); return; }
    Blockchain *b = FedBlock->BlockchainsArray[indice_cadena];
    Nodo *inicio = blockchain_buscar_por_id(b, id_antiguo);
    if (!inicio) { fprintf(stderr, "ID no encontrado en la blockchain\n"); return; }
    free(inicio->mensaje);
    inicio->mensaje = strdup(mensajeNew ? mensajeNew : "");
    Nodo *actual = inicio;
    unsigned long long ultimo = FedBlock->lastPrimo;
    while (actual) {
        unsigned long long p = siguiente_primo(ultimo);
        actual->id = p;
        ultimo = p;
        actual = actual->siguiente;
    }
    FedBlock->lastPrimo = ultimo;
    unsigned long long id_final = b->ultimo ? b->ultimo->id : 1ULL;
    federada_actualizar_hoja(F, indice_cadena, id_final);
}

federada_validar(Federada *FedBlock) {
    for (int i = 0; i < FedBlock->cantHojas; i++) {
        blockchain = FedBlock->treeValidation[i];
        Nodo *nodo = blockchain->ultimo;
        while (nodo->anterior){
            if (nodo->id < nodo->anterior->id) return 0;
            nodo = nodo->anterior;
        }
        int cont = 1
        for (o = FedBlock->longTree/2; o < (FedBlock->cantHojas + FedBlock->longTree/2); o++) {
            cont = cont * FedBlock->treeValidation[o];
        }
        if (cont != FedBlock->treeValidation[1]) return 0;
    }
}

federada_validar_subconjunto(Federada *FedBlock, long long esperado, int minIdx, int maxIdx) {
    if (minIdx > maxIdx || maxIdx >= FedBlock->cantHojas) return 0;
    producto = 1;
    
    if (minIdx%2 == 1){
        for (int i = minIdx; i <= maxIdx; ++i){
            producto = producto * FedBlock->treeValidation[(FedBlock->longTree/2) + i];
        }
        else for (int i = minIdx; i <= maxIdx; ++i){
            if (maxIdx >= i+2){
                producto = producto * FedBlock->treeValidation[((FedBlock->longTree/2) + i)/2];
            }
            else {
                producto = producto * FedBlock->treeValidation[(FedBlock->longTree/2) + i];
            }
        }
    }
}