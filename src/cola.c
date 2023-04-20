#include "cola.h"
#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct nodo {
	void *elemento;
	struct nodo *siguiente;
} nodo_t;

struct _cola_t {
	nodo_t *nodo_inicio;
	nodo_t *nodo_fin;
	size_t cantidad_nodos;
};


cola_t *cola_crear()
{
	return (cola_t *)(lista_crear());
}

cola_t *cola_encolar(cola_t *cola, void *elemento)
{
	return (cola_t *)(lista_insertar((lista_t *)(cola), elemento));
}

void *cola_desencolar(cola_t *cola)
{
	if (!cola || cola_vacia(cola))
		return NULL;

	nodo_t *nodo_a_desencolar = cola->nodo_inicio;
	void *elemento = cola->nodo_inicio->elemento;

	if (cola_tamanio(cola) == 1) {
		cola->nodo_inicio = NULL;
		cola->nodo_fin = NULL;
	} else
		cola->nodo_inicio = nodo_a_desencolar->siguiente;
	
	free(nodo_a_desencolar);
	cola->cantidad_nodos--;

	return elemento;
}

void *cola_frente(cola_t *cola)
{
	return (cola_t *)(lista_primero((lista_t *)(cola)));
}

size_t cola_tamanio(cola_t *cola)
{
	return lista_tamanio((lista_t *)(cola));
}

bool cola_vacia(cola_t *cola)
{
	return (cola_t *)(lista_vacia((lista_t *)(cola)));
}

void cola_destruir(cola_t *cola)
{
	if (!cola)
		return;

	while (cola_tamanio(cola) != 0) {
		nodo_t *nodo_a_destruir = cola->nodo_inicio;
		cola->nodo_inicio = nodo_a_destruir->siguiente;
		free(nodo_a_destruir);
		cola->cantidad_nodos--;
	}

	free(cola);

	return;
}