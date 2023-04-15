#include "pa2m.h"

#include "src/lista.h"

#include <stdio.h>
#include <stdlib.h>

void pruebas_creacion_y_destruccion()
{
	lista_t *lista = lista_crear();
	pa2m_afirmar(lista != NULL, "Se puede crear una lista correctamente");

	pa2m_afirmar(lista_tamanio(lista) == 0 && !lista_primero(lista) &&
	 	     !lista_ultimo(lista) && lista_vacia(lista),
	  	     "La lista esta vacia");

	lista_destruir(lista);

	return;
}

void pruebas_parametros_invalidos()
{
	void *elemento = (void*)0x1234;

	pa2m_afirmar(!lista_insertar(NULL, elemento),
		     "No se puede insertar un elemento a una lista que no existe");

	pa2m_afirmar(!lista_insertar_en_posicion(NULL, elemento, 0),
		     "No se puede insertar un elemento en cualquier posicion a una lista que no existe");

	pa2m_afirmar(!lista_quitar(NULL), 
		     "No se puede quitar un elemento de una lista que no existe");

	pa2m_afirmar(!lista_quitar_de_posicion(NULL, 0),
		     "No se puede quitar un elemento de cualquier posicion de una lista que no existe");

	return;
}

void pruebas_insertar_al_final()
{
	lista_t *lista = lista_crear();
	void *elemento1 = (void*)0x1234;
	void *elemento2 = (void*)0x4321;

	pa2m_afirmar(lista_insertar(lista, elemento1) != NULL,
		     "Se puede insertar un elemento al final de la lista");

	pa2m_afirmar(lista_insertar(lista, NULL) != NULL,
		     "Se puede insertar NULL al final de la lista");

	lista_insertar(lista, elemento2);

	pa2m_afirmar(lista_primero(lista) == elemento1,
		     "El primer elemento ingresado es el primero en la lista");

	pa2m_afirmar(lista_ultimo(lista) == elemento2,
		      "El ultimo elemento ingresado es el ultimo en la lista");

	pa2m_afirmar(lista_tamanio(lista) == 3,
		     "Se insertaron 3 elementos, y el tamanio es 3");

	lista_destruir(lista);
}

void pruebas_insertar_en_cualquier_posicion()
{
	lista_t *lista = lista_crear();

	void *elemento1 = (void*)0x1234;
	void *elemento2 = (void*)0x4321;

	pa2m_afirmar(lista_insertar_en_posicion(lista, elemento1, 0) != NULL,
		     "Se puede insertar al principio de una lista vacia");

	pa2m_afirmar(lista_primero(lista) == elemento1,
		     "El elemento ingresado es el primero en la lista");

	pa2m_afirmar(lista_ultimo(lista) == elemento1,
		      "El elemento ingresado es el ultimo en la lista");


	pa2m_afirmar(lista_insertar_en_posicion(lista, elemento2, 1) != NULL,
		     "Se puede insertar a continuacion del primer elemento");

	pa2m_afirmar(lista_ultimo(lista) == elemento2,
		      "Ahora el segundo elemento ingresado es el ultimo de la lista");


	pa2m_afirmar(lista_insertar_en_posicion(lista, elemento2, 0) != NULL,
		     "Se puede insertar otra vez al principio de la lista");

	pa2m_afirmar(lista_primero(lista) == elemento2,
		     "Ahora el tercer elemento ingresado es el primero de la lista");


	pa2m_afirmar(lista_insertar_en_posicion(lista, elemento1, 100) != NULL,
		     "Se puede insertar un elemento en una posicion inexistente, al final de la lista");

	pa2m_afirmar(lista_ultimo(lista) == elemento1,
		      "El elemento ingresado ahora es el ultimo de la lista");


	pa2m_afirmar(lista_insertar_en_posicion(lista, NULL, 2) != NULL,
		     "Se puede insertar NULL cualquier posicion");
	
	pa2m_afirmar(lista_tamanio(lista) == 5,
		     "Se insertaron 5 elementos, y el tamanio es 5");

	lista_destruir(lista);

	return;
}

void pruebas_quitar_al_final()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(!lista_quitar(lista),
		     "No se pueden quitar elementos de una lista vacia");

	void *elemento1 = (void*)0x1234;
	void *elemento2 = (void*)0x4321;

	lista_insertar(lista, elemento1);
	lista_insertar(lista, elemento2);

	pa2m_afirmar(lista_quitar(lista) == elemento2,
		     "Se pueden quitar elementos del final de la lista");

	pa2m_afirmar(lista_ultimo(lista) == elemento1 &&
		     lista_tamanio(lista) == 1, "Se reajusta bien la lista");


	pa2m_afirmar(lista_quitar(lista) == elemento1,
		     "Se pueden quitar elementos de una lista con un solo elemento");

	pa2m_afirmar(lista_tamanio(lista) == 0 && lista_vacia(lista),
		     "Se eliminan todos los elementos y la lista queda vacia");
		     
	pa2m_afirmar(!lista_primero(lista) && !lista_ultimo(lista),
		     "Se reajusta bien la lista vacia");

	lista_destruir(lista);

	return;
}

void pruebas_quitar_en_cualquier_posicion()
{
	lista_t *lista = lista_crear();

	pa2m_afirmar(!lista_quitar_de_posicion(lista, 0),
		     "No se pueden quitar elementos de cualquier posicion de una lista vacia");

	void *elemento1 = (void*)0x1234;
	void *elemento2 = (void*)0x4321;
	void *elemento3 = (void*)0x1234;
	void *elemento4 = (void*)0x4321;
	void *elemento5 = (void*)0x4321;

	lista_insertar(lista, elemento1);
	lista_insertar(lista, elemento2);
	lista_insertar(lista, elemento3);
	lista_insertar(lista, elemento4);
	lista_insertar(lista, elemento5);


	pa2m_afirmar(lista_quitar_de_posicion(lista, 0) == elemento1,
		     "Se puede quitar el primer elemento de la lista");

	pa2m_afirmar(lista_quitar_de_posicion(lista, 1) == elemento3,
		     "Se pueden quitar elementos del medio de la lista");

	pa2m_afirmar(lista_quitar_de_posicion(lista, 2) == elemento5,
		     "Se puede quitar el ultimo elemento de la lista");

	pa2m_afirmar(lista_quitar_de_posicion(lista, 100) == elemento4,
		     "Se pueden quitar elementos de una posicion inexistente");

	pa2m_afirmar(lista_quitar_de_posicion(lista, 0) == elemento2,
		     "Se puede quitar el unico elemento de la lista");


	pa2m_afirmar(lista_tamanio(lista) == 0 && lista_vacia(lista),
		     "Se eliminan todos los elementos y la lista queda vacia");
		     
	pa2m_afirmar(!lista_primero(lista) && !lista_ultimo(lista),
		     "Se reajusta bien la lista vacia");

	lista_destruir(lista);

	return;
}

void pruebas_de_la_lista()
{
	pa2m_nuevo_grupo("PRUEBAS DE CREACION Y DESTRUCCION");
	pruebas_creacion_y_destruccion();

	pa2m_nuevo_grupo("PRUEBAS DE PARAMETROS INVALIDOS");
	pruebas_parametros_invalidos();

	pa2m_nuevo_grupo("PRUEBAS DE INSERTAR AL FINAL");
	pruebas_insertar_al_final();

	pa2m_nuevo_grupo("PRUEBAS DE INSERTAR EN CUALQUIER POSICION");
	pruebas_insertar_en_cualquier_posicion();

	pa2m_nuevo_grupo("PRUEBAS DE QUITAR AL FINAL");
	pruebas_quitar_al_final();

	pa2m_nuevo_grupo("PRUEBAS DE QUITAR EN CUALQUIER POSICION");
	pruebas_quitar_en_cualquier_posicion();

	return;
}

int main()
{
	pa2m_nuevo_grupo("----------- PRUEBAS DEL TP: TDA-LISTA -----------");

	pa2m_nuevo_grupo("--- PRUEBAS DEL TDA-LISTA ---");
	pruebas_de_la_lista();

	return pa2m_mostrar_reporte();
}
