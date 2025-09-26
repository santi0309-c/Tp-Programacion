#include "opercaiones.h"

int main (){
    federada *F = crear_federada(2);
    federada_agregar_blockchain(F);
    federada_agregar_blockchain(F);
    federada_alta(F, 0, "Genesis 0");
    federada_alta(F, 1, "Genesis 1");
    federada_modificar(F, 0, 2, "Modificado 0");
    int ok = federada_validar(F);
    printf("Validación completa: %s\n", ok ? "OK" : "FALLA");
}