#include "federada.h"

void federada_alta(Federada *FedBlock, int nroBlock, char *mensaje) {
    if (nroBlock >= FedBlock->nroHojas) {
        fprintf(stderr, "Índice fuera de rango en alta\n");
        return;
    }
    long long primo = primos(FedBlock->lastPrimo);
    FedBlock->ultimo_primo = primo;
    blockchain_agregar_con_id(FedBlock->treeValidation[nroBlock], primo, mensaje);
    actualizarHoja(FedBlock, nroBlock, primo);
}

void federada_modificar(Federada *FedBlock, int nroBlock, long long idAntiguo, char *mensajeNew) {
    if (indice_cadena >= FedBlock->cantHojas) { fprintf(stderr, "Índice fuera de rango en modificar\n"); return; }
    Blockchain *b = F->cadenas[indice_cadena];
    Nodo *inicio = blockchain_buscar_por_id(b, id_antiguo);
    if (!inicio) { fprintf(stderr, "ID no encontrado en la blockchain\n"); return; }
    free(inicio->mensaje);
    inicio->mensaje = strdup(nuevo_mensaje ? nuevo_mensaje : "");
    Nodo *actual = inicio;
    unsigned long long ultimo = F->ultimo_primo;
    while (actual) {
        unsigned long long p = siguiente_primo(ultimo);
        actual->id = p;
        ultimo = p;
        actual = actual->siguiente;
    }
    F->ultimo_primo = ultimo;
    unsigned long long id_final = b->ultimo ? b->ultimo->id : 1ULL;
    federada_actualizar_hoja(F, indice_cadena, id_final);
}

federada_validar(Federada *FedBlock) {
    for (int i = 0; i < FedBlock->cantHojas; i++) {
        blockchain = FedBlock->treeValidation[i];
        Nodo *hoja = blockchain->ultimo;
    })



}