#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "blockchains.h"
#include "generador_primos.h"
#include "heap.h"

typedef struct Federada {
    Blockchain *BlockchainsArray;
    int cantHojas;  
    int capacidadTree;
    long long *treeValidation; // arreglo que representa el arbol de validacion  
    int longTree; 
    long long lastPrimo; 
} Federada;

Federada* crearFederada(int cantBlocks);

void federadaActuCant(Federada *FedBlock, int cantNuevaBlocks);

void liberarFederada(Federada *FedBlock);

void federadaAgregarBlock(Federada *FedBlock);