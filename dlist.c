#include "dlist.h"

Nodo* crear_nodo(unsigned long long id, const char *mensaje) {
    Nodo *node = malloc(sizeof(Nodo));
    node->id = id;
    node->mensaje = strdup(mensaje ? mensaje : "");
    node->anterior = NULL;
    node->siguiente = NULL;
    return node;
}

DList* dlist_crear() {
  DList *dlist = malloc(sizeof(DList));
  dlist->primero = NULL;
  dlist->ultimo = NULL;
  dlist->cant = 0;
  return dlist;
}

void dlist_destruir_Nodo(Nodo *lista) {
  Nodo *nodo_a_eliminar;
  while (lista != NULL) {
    nodo_a_eliminar = lista;
    lista = lista->siguiente;
    free(nodo_a_eliminar);
  }
}

void dlist_destruir(DList *lista) {
  dlist_destruir_Nodo(lista->primero);
  free(lista);
}

int dlist_vacia(DList *lista) {
  return lista->primero == NULL;
}

DList* dlist_agregar_final(DList* lista, int dato) {
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

DList* dlist_agregar_inicio(DList *lista, int dato) {
  Nodo *nuevo_nodo = malloc(sizeof(Nodo));
  nuevo_nodo->mensaje = dato;
  nuevo_nodo->siguiente = lista->primero;
  nuevo_nodo->anterior = NULL;
  nuevo_nodo->id = 0;
  lista->cant++;

  Nodo *aux = malloc(sizeof(Nodo));
  aux = nuevo_nodo;

  for (int i = 0; i < lista->cant; i++){
    aux->siguiente->id++;
    aux = aux->siguiente;
  }
  
  if (lista->primero != NULL)
    lista->primero->anterior = nuevo_nodo;

  if (lista->ultimo == NULL)
    lista->ultimo = nuevo_nodo;

  lista->primero = nuevo_nodo;
  return lista;
}

void dlist_recorrer_hacia_adelante(DList *lista, FuncionVisitante visit) {
  for (Nodo *nodo = lista->primero; nodo != NULL; nodo = nodo->sig)
    visit(nodo->mensaje);
}

void dlist_recorrer_hacia_atras(DList *lista, FuncionVisitante visit) {
  for (Nodo *nodo = lista->ultimo; nodo != NULL; nodo = nodo->ant)
    visit(nodo->mensaje);
}

