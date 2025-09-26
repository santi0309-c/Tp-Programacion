#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "federada.h"
#include "generador_primos.h"
#include "tree.h"

typedef struct Nodo {
    long long id; 
    char *mensaje;
    Nodo *anterior;
    Nodo *siguiente;
} Nodo;


typedef struct {
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

