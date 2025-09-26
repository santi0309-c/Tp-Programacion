/*
 * blockchain_lista_doble_federada_heap.c
 * Implementación en C de:
 * - Blockchain como lista doblemente enlazada
 * - Blockchain federada como arreglo dinámico de blockchains (lista doble)
 * - Árbol de validación como "heap" dinámico (arreglo que representa árbol binario completo)
 *
 * Funciones implementadas: crear red federada, alta (agregar), modificar, validar, validar subconjunto.
 * Nota: para la generación de identificadores se usa un generador de primos simple (siguiente_primo).
 * IMPORTANTE: los productos pueden desbordar unsigned long long si hay muchos nodos/primos grandes.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

/* ------------------ Estructuras ------------------ */

typedef struct Nodo {
    unsigned long long id; // identificador (primo)
    char *mensaje;
    Nodo *anterior;
    Nodo *siguiente;
} Nodo;

typedef struct Blockchain {
    Nodo *primero; // primer nodo
    Nodo *ultimo;  // último nodo
    int longitud;
} Blockchain;

typedef struct Federada {
    Blockchain **cadenas;       // arreglo dinámico de punteros a blockchains
    int cantidad;               // cantidad de blockchains
    int capacidad;              // capacidad actual del arreglo de blockchains
    unsigned long long *heap;   // arreglo dinámico que representa el árbol de validación (1-indexado)
    int tamanio_heap;           // tamaño en elementos del arreglo heap
    unsigned long long ultimo_primo; // último primo asignado
} Federada;

/* ------------------ Primos (generador simple) ------------------ */

static int es_primo(unsigned long long x) {
    if (x < 2) return 0;
    if (x % 2 == 0) return x == 2;
    for (unsigned long long i = 3; i * i <= x; i += 2) {
        if (x % i == 0) return 0;
    }
    return 1;
}

static unsigned long long siguiente_primo(unsigned long long desde) {
    unsigned long long p = desde + 1;
    if (p <= 2) return 2;
    if (p % 2 == 0) p++;
    while (!es_primo(p)) p += 2;
    return p;
}

/* ------------------ Operaciones sobre lista doblemente enlazada ------------------ */

/* ------------------ Heap / Árbol de validación ------------------ */

/*
void federada_construir_heap(Federada *F) {
    int hojas = F->cantidad;
    if (hojas == 0) {
        free(F->heap);
        F->heap = NULL;
        F->tamanio_heap = 0;
        return;
    }
    int pot2 = siguiente_potencia_de_dos(hojas);
    int total = 2 * pot2;
    if (F->heap) free(F->heap);
    F->heap = calloc(total, sizeof(unsigned long long));
    F->tamanio_heap = total;
    int base = pot2;
    for (int i = 0; i < pot2; ++i) {
        int idx = base + i;
        if (i < hojas) {
            Blockchain *bc = F->cadenas[i];
            if (bc && bc->ultimo) F->heap[idx] = bc->ultimo->id;
            else F->heap[idx] = 1ULL;
        } else {
            F->heap[idx] = 1ULL;
        }
    }
    for (int i = base - 1; i >= 1; --i) {
        unsigned long long izq = F->heap[2*i];
        unsigned long long der = F->heap[2*i + 1];
        F->heap[i] = izq * der;
        if (i == 1) break;
    }
}
*/

unsigned long long federada_raiz(Federada *F) {
    if (!F->heap || F->tamanio_heap <= 1) return 1ULL;
    return F->heap[1];
}

void federada_actualizar_hoja(Federada *F, int indice_hoja, unsigned long long valor) {
    if (!F->heap) return;
    int hojas = F->cantidad;
    int pot2 = siguiente_potencia_de_dos(hojas);
    int idx = pot2 + indice_hoja;
    F->heap[idx] = valor;
    while (idx > 1) {
        idx /= 2;
        F->heap[idx] = F->heap[2*idx] * F->heap[2*idx + 1];
    }
}

/* ------------------ Federada: crear, redimensionar, alta, modificar, validar ------------------ */

Federada* crear_federada(int capacidad_inicial) {
    Federada *F = malloc(sizeof(Federada));
    F->cantidad = 0;
    F->capacidad = capacidad_inicial > 0 ? capacidad_inicial : 1;
    F->cadenas = calloc(F->capacidad, sizeof(Blockchain*));
    F->heap = NULL;
    F->tamanio_heap = 0;
    F->ultimo_primo = 2;
    return F;
}

void federada_redimensionar(Federada *F, int nueva_capacidad) {
    if (nueva_capacidad <= F->capacidad) return;
    F->cadenas = realloc(F->cadenas, nueva_capacidad * sizeof(Blockchain*));
    for (int i = F->capacidad; i < nueva_capacidad; i++) {
        F->cadenas[i] = NULL;
    }
    F->capacidad = nueva_capacidad;
}

void liberar_federada(Federada *F) {
    if (!F) return;
    for (int i = 0; i < F->cantidad; ++i) liberar_blockchain(F->cadenas[i]);
    free(F->cadenas);
    free(F->heap);
    free(F);
}

void federada_agregar_blockchain(Federada *F) {
    if (F->cantidad >= F->capacidad) {
        federada_redimensionar(F, F->capacidad * 2);
    }
    F->cadenas[F->cantidad] = crear_blockchain();
    F->cantidad++;
    federada_construir_heap(F);
}

void federada_alta(Federada *F, int indice_cadena, const char *mensaje) {
    if (indice_cadena >= F->cantidad) {
        fprintf(stderr, "Índice fuera de rango en alta\n");
        return;
    }
    unsigned long long p = siguiente_primo(F->ultimo_primo);
    F->ultimo_primo = p;
    blockchain_agregar_con_id(F->cadenas[indice_cadena], p, mensaje);
    federada_actualizar_hoja(F, indice_cadena, p);
}

void federada_modificar(Federada *F, int indice_cadena, unsigned long long id_antiguo, const char *nuevo_mensaje) {
    if (indice_cadena >= F->cantidad) { fprintf(stderr, "Índice fuera de rango en modificar\n"); return; }
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

int federada_validar(Federada *F) {
    for (int i = 0; i < F->cantidad; ++i) {
        Blockchain *b = F->cadenas[i];
        Nodo *actual = b->primero;
        unsigned long long previo = 0ULL;
        while (actual) {
            if (actual->id <= previo) return 0;
            previo = actual->id;
            actual = actual->siguiente;
        }
    }
    unsigned long long producto = 1ULL;
    for (int i = 0; i < F->cantidad; ++i) {
        Blockchain *b = F->cadenas[i];
        unsigned long long v = b->ultimo ? b->ultimo->id : 1ULL;
        producto *= v;
    }
    unsigned long long raiz = federada_raiz(F);
    return producto == raiz;
}

int federada_validar_subconjunto(Federada *F, unsigned long long esperado, int minIdx, int maxIdx) {
    if (minIdx > maxIdx || maxIdx >= F->cantidad) return 0;
    unsigned long long producto = 1ULL;
    for (int i = minIdx; i <= maxIdx; ++i) {
        Blockchain *b = F->cadenas[i];
        unsigned long long v = b->ultimo ? b->ultimo->id : 1ULL;
        producto *= v;
    }
    return producto == esperado;
}

/* ------------------ Ejemplo de uso (main) ------------------ */

int main(void) {
    Federada *F = crear_federada(2);

    federada_agregar_blockchain(F);
    federada_agregar_blockchain(F);
    federada_agregar_blockchain(F);

    federada_alta(F, 0, "Génesis 0");
    federada_alta(F, 1, "Génesis 1");
    federada_alta(F, 2, "Génesis 2");

    printf("Raíz después de tres altas: %" PRIu64 "\n", federada_raiz(F));

    federada_alta(F, 0, "Segundo en 0");
    printf("Raíz después de otra alta: %" PRIu64 "\n", federada_raiz(F));

    for (int i = 0; i < F->cantidad; ++i) {
        printf("Cadena %d: ", i);
        Nodo *actual = F->cadenas[i]->primero;
        while (actual) {
            printf("%llu ", actual->id);
            actual = actual->siguiente;
        }
        printf("\n");
    }

    int ok = federada_validar(F);
    printf("Validación completa: %s\n", ok ? "OK" : "FALLA");

    unsigned long long id1 = F->cadenas[1]->primero->id;
    federada_modificar(F, 1, id1, "Modificado en 1");
    printf("Raíz después de modificar cadena 1: %" PRIu64 "\n", federada_raiz(F));

    unsigned long long prod01 = (F->cadenas[0]->ultimo?F->cadenas[0]->ultimo->id:1ULL) * (F->cadenas[1]->ultimo?F->cadenas[1]->ultimo->id:1ULL);
    printf("Validar subconjunto 0..1 esperado=%llu -> %s\n", prod01, federada_validar_subconjunto(F, prod01, 0, 1) ? "OK" : "FALLA");

    liberar_federada(F);
    return 0;
}
