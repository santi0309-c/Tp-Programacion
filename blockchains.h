#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>

typedef struct Nodo {
    int id; 
    char *mensaje;
    Nodo *anterior;
    Nodo *siguiente;
} Nodo;


typedef struct Blockchain {
    Nodo *primero; 
    Nodo *ultimo; 
    int longitud;
} Blockchain;


typedef struct Federada {
    Blockchain **BlockchainsArray;
    int cantBlock; 
    int largoBlock; 
    int *treeValidation; // arreglo que representa el arbol de validacion 
    int longTree; 
    int lastPrimo; 
} Federada;