#ifndef BLOCKCHAINS_H
#define BLOCKCHAINS_H
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include<string.h>
#include "generador_primos.h"

typedef struct Nodo {
    long long id; 
    char *mensaje;
    struct Nodo *anterior;
    struct Nodo *siguiente;
} Nodo;


typedef struct _Blockchain {
  Nodo *primero;
  Nodo *ultimo;
  int cant;
} Blockchain;


Nodo* crear_nodo(long long id, const char *mensaje);

void destruir_Nodo(Nodo *lista);

Blockchain* crearBlockchain();

void liberaBlockchain(Blockchain *Block);

Nodo* blockchain_buscar_por_id(Blockchain *block, long long id);

void blockchain_agregar_id(Blockchain *block, long long id, char *mensaje);

#endif // BLOCKCHAINS_H

 