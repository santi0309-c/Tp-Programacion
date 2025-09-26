#ifndef __SLIST_H__
#define __SLIST_H__

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

typedef void (*FuncionVisitante) (long long dato);

typedef struct Nodo {
    long long id; 
    char *mensaje;
    Nodo *anterior;
    Nodo *siguiente;
} Nodo;


typedef struct {
  Nodo *primero;
  Nodo *ultimo;
  int cant;
} DList;

Nodo* crear_nodo(long long id, const char *mensaje);


void dlist_destruir_Nodo(Nodo *lista);

 
DList* dlist_crear();  // Devuelve una lista vacía.


void dlist_destruir_Nodo(Nodo *lista);   // Destruccion de la lista.


void dlist_destruir(DList *lista);     // Destruccion de la lista.


int dlist_vacia(DList *lista);    // Determina si la lista es vacía.


DList* dlist_agregar_final(DList* lista, long long dato);    // Agrega un elemento al final de la lista.


void dlist_recorrer_hacia_adelante(DList *lista, FuncionVisitante visit);  // Recorrido de la lista, utilizando la funcion pasada.


void dlist_recorrer_hacia_atras(DList *lista, FuncionVisitante visit);      // Recorrido de la lista en orden inverso, utilizando la funcion pasada.

#endif 
