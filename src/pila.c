#include "pila.h"
#include <stddef.h>
#include <stdlib.h>

typedef struct nodo {
	void *elemento;
	struct nodo *anterior;
} nodo_t;

struct _pila_t {
	nodo_t *tope;
	size_t cantidad_nodos;
};


pila_t *pila_crear()
{
	return calloc(1, sizeof(pila_t));
}

pila_t *pila_apilar(pila_t *pila, void *elemento)
{
	if (!pila)
		return NULL;

	nodo_t *nodo = calloc(1, sizeof(nodo_t));
	if (!nodo)
		return NULL;

	if (pila->tope != NULL)
		nodo->anterior = pila->tope;

	pila->tope = nodo;
	pila->cantidad_nodos++;
	nodo->elemento = elemento;

	return pila;
}

void *pila_desapilar(pila_t *pila)
{
	if (!pila || pila_vacia(pila))
		return NULL;

	nodo_t *nodo_a_desapilar = pila->tope;
	void *elemento = nodo_a_desapilar->elemento;

	if (pila_tamanio(pila) == 1)
		pila->tope = NULL;
	else
		pila->tope = nodo_a_desapilar->anterior;

	free(nodo_a_desapilar);
	pila->cantidad_nodos--;

	return elemento;
}

void *pila_tope(pila_t *pila)
{
	if (!pila)
		return NULL;

	return pila->tope;
}

size_t pila_tamanio(pila_t *pila)
{
	if (!pila)
		return 0;

	return pila->cantidad_nodos;
}

bool pila_vacia(pila_t *pila)
{
	if (!pila || !pila->cantidad_nodos)
		return true;

	return false;
}

void pila_destruir(pila_t *pila)
{
	if (!pila)
		return;

	while (pila_tamanio(pila) != 0) {
		nodo_t *nodo_a_destruir = pila->tope;
		pila->tope = nodo_a_destruir->anterior;
		free(nodo_a_destruir);
		pila->cantidad_nodos--;
	}

	free(pila);

	return;
}
