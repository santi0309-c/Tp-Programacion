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

int federada_validar(Federada *fedblock){
    long long ids[fedblock->cantHojas];
    for (int i = 0; i < fedblock->cantHojas; i++){
        Blockchain *b = fedblock->BlockchainsArray[i];
        if (!b || !b->ultimo) {  
            ids[i] = 1; 
            continue;
        }
        ids[i] = b->ultimo->id;
    }
    long long producto = 1;
    for (int i = 0; i < fedblock->cantHojas; i++){
        producto *= ids[i];
    }
    if (producto != fedblock->treeValidation[1]){
        return 0;
    }else return 1;
}



int federada_validar_subconjunto(Federada *FedBlock, long long esperado, int minIdx, int maxIdx) {
    if (minIdx > maxIdx || maxIdx >= FedBlock->cantHojas) return 0;
    long long producto = 1;
    for (int i = minIdx; i <= maxIdx; ++i) {
        producto *= FedBlock->treeValidation[(FedBlock->longTree/2) + i];
    }
    return producto == esperado;
}