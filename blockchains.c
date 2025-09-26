#include "blockchains.h"

Nodo* crear_nodo(long long id, const char *mensaje) {
    Nodo *node = malloc(sizeof(Nodo));
    node->id = id;
    node->mensaje = strdup(mensaje ? mensaje : "");
    node->anterior = NULL;
    node->siguiente = NULL;
    return node;
}

void destruir_Nodo(Nodo *lista) {
  Nodo *nodo_a_eliminar;
  while (lista != NULL) {
    nodo_a_eliminar = lista;
    lista = lista->siguiente;
    free(nodo_a_eliminar);
  }
}

Blockchain* crearBlockchain() {
    Blockchain *Block = malloc(sizeof(Blockchain));
    Block->primero = Block->ultimo = NULL;
    Block->cant = 0;
    return Block;
}

void liberaBlockchain(Blockchain *Block) {
    if (!Block) return;
    Nodo *actual = Block->primero;
    while (actual) {
        Nodo *sig = actual->siguiente;
        destruir_Nodo(actual);
        actual = sig;
    }
    free(Block);
}

void blockchain_agregar_id(Blockchain *block, long long id, char *mensaje) {
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
        if (actual->id == id) 
            return actual;
    }
    return NULL;
}




