#include "blockchains.h"

void actualizar(Federada *Federada){
    for (int i = 0; i < Federada->cantBlock; i++){
        Federada->treeValidation[(Federada->longTree / 2) + i] = Federada->BlockchainsArray[i]->ultimo->id; 
    }
    for (int i = Federada->longTree / 2; i > 0; i--){
        Federada->treeValidation[i] = Federada->treeValidation[i*2] * Federada->treeValidation[i*2 + 1];
    }
}