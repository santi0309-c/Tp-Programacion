#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "dlist.h"
#include "generador_primos.h"
#include "heap.h"

typedef *dlist Blockchain;

typedef struct Federada {
    Blockchain *BlockchainsArray;
    int cantBlock;  
    int *treeValidation; // arreglo que representa el arbol de validacion 
    int longTree; 
    int lastPrimo; 
} Federada;

