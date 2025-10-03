#include "blockchains.h"

Nodo* crear_nodo(long long id, const char *mensaje) {
    Nodo *node = malloc(sizeof(Nodo));
    if (!node) return NULL;
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
    Block->primero = NULL;
    Block->ultimo = NULL;
    Block->cant = 0;
    return Block;
}

void liberaBlockchain(Blockchain *Block) {
    if (!Block || !Block->primero) return;
    Nodo *actual = Block->primero;
    printf("Liberando blockchain con %d nodos\n", Block->cant);
    while (actual != NULL) {
        printf("Liberando nodo con ID: %lld y mensaje: %s\n", actual->id, actual->mensaje);
        Nodo *sig = actual->siguiente;
        free(actual->mensaje);
        free(actual);
        actual = sig;
    }

    printf("Libere todos los nodos\n");
    free(Block);
}

void blockchain_agregar_id(Blockchain *block, long long id, char *mensaje) {
    if (!block) {
        printf("Error: Blockchain es NULL\n");
    return;}
    Nodo *node = crear_nodo(id, mensaje);

    if (block->primero == NULL) {
        block->ultimo = node;
        block->primero = node;
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




