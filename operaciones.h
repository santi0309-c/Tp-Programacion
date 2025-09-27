#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include "blockchains.h"
#include "generador_primos.h"
#include "federada.h"

void federada_alta(Federada *FedBlock, int nroBlock, char *mensaje);

void federada_modificar(Federada *FedBlock, int nroBlock, long long idAntiguo, char *mensajeNew);

int federada_validar(Federada *FedBlock);

int federada_validar_subconjunto(Federada *FedBlock, long long esperado, int minIdx, int maxIdx);

