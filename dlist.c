#include "dlist.h"


DList* dlist_crear() {
  DList *dlist = malloc(sizeof(DList));
  dlist->primero = NULL;
  dlist->ultimo = NULL;
  dlist->cant = 0;
  return dlist;
}


void dlist_destruir(DList *lista) {
  dlist_destruir_Nodo(lista->primero);
  free(lista);
}

void dlist_liberar(DList *lista) {
    if (!lista) return;
    Nodo *actual = lista->primero;
    while (actual) {
        Nodo *sig = actual->siguiente;
        liberar_nodo(actual);
        actual = sig;
    }
    free(lista);
}


int dlist_vacia(DList *lista) {
  return lista->primero == NULL;
}


DList* dlist_agregar_final(DList* lista, long long dato) {
  Nodo *nuevo_nodo = malloc(sizeof(Nodo));
  nuevo_nodo->mensaje = dato;
  nuevo_nodo->siguiente = NULL;
  nuevo_nodo->anterior = lista->ultimo;

  if (lista->ultimo != NULL)
    lista->ultimo->siguiente = nuevo_nodo;

  if (lista->primero == NULL)
    lista->primero = nuevo_nodo;

  lista->ultimo = nuevo_nodo;
  return lista;
}


void dlist_recorrer_hacia_adelante(DList *lista, FuncionVisitante visit) {
  for (Nodo *nodo = lista->primero; nodo != NULL; nodo = nodo->siguiente)
    visit(nodo->mensaje);
}


void dlist_recorrer_hacia_atras(DList *lista, FuncionVisitante visit) {
  for (Nodo *nodo = lista->ultimo; nodo != NULL; nodo = nodo->anterior)
    visit(nodo->mensaje);
}

