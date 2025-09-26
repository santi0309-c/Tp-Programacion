#include "operaciones.h"

int main (){
    Federada *F = crearFederada(2);
    federadaAgregarBlock(F);
    federadaAgregarBlock(F);
    federada_alta(F, 0, "Genesis 0");
    federada_alta(F, 1, "Genesis 1");
    modificar_dato(F, 0, 2, "Modificado 0");
    int ok = federada_validar(F);
    printf("Validación completa: %s\n", ok ? "OK" : "FALLA");
}