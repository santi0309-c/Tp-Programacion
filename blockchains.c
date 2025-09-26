#include "blockchains.h"

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
        int izq = Federada->treeValidation[i*2];
        int der = Federada->treeValidation[i*2 + 1];
        Federada->treeValidation[i] = izq * der;
    }
    return NULL;
}