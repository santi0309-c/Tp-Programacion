#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "blockchains.h"
#include "generador_primos.h"

typedef struct _Federada {
    Blockchain **BlockchainsArray;
    int cantHojas;  
    int capacidadTree;
    long long *treeValidation;
    int longTree; 
    long long lastPrimo; 
} Federada;

Federada* crearFederada(int cantBlocks);

void federadaActuCant(Federada *FedBlock, int cantNuevaBlocks);

void liberarFederada(Federada *FedBlock);

void federadaAgregarBlock(Federada *FedBlock);

int followPotenciaDos(int pDos);

void modificar_dato(long long arr[], long long nro_agregar, int posc_agregar);

void construirTree(Federada *F);

void actualizarHoja(Federada *FedBlock, int indexHoja, long long id);