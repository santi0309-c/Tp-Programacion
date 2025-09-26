#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "dlist.h"
#include "generador_primos.h"
#include "heap.h"

typedef DList Blockchain;


typedef struct Federada {
    Blockchain *BlockchainsArray;
    int cantBlock;  
    int *treeValidation; // arreglo que representa el arbol de validacion 
    int longTree; 
    int lastPrimo; 
} Federada;

Nodo* blockchain_buscar_por_id(Blockchain *block, long long id);

void blockchain_agregar_id(Blockchain *block, long long id, char *mensaje);

void agregar(Federada*, int, Blockchain*);

void actualizar(Federada*);