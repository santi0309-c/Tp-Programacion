#include "blockchains.h"

void actualizar(Federada *Federada){
    for (int i = 0; i < Federada->cantBlock; i++){
        Federada->treeValidation[(Federada->longTree / 2) + i] = Federada->BlockchainsArray->ultimo->id; 
    }
    for (int i = Federada->longTree / 2; i > 0; i--){
        Federada->treeValidation[i] = Federada->treeValidation[i*2] * Federada->treeValidation[i*2 + 1];
    }
}


void blockchain_agregar_con_id(Blockchain *block, long long id, char *mensaje) {
    Nodo *node = crear_nodo(id, mensaje);
    if (!block->primero) {
        block->primero = block->ultimo = node;
    } else {
        block->ultimo->siguiente = node;
        node->anterior = block->ultimo;
        block->ultimo = node;
    }
    block->cant++;
}


Nodo* blockchain_buscar_por_id(Blockchain *block, long long id) {
    Nodo *actual = block->primero;
    while (actual) {
        if (actual->id == id) return actual;
        actual = actual->siguiente;
    }
    return NULL;
}