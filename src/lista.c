#include "lista.h"
#include <stddef.h>
#include <stdlib.h>

lista_t *lista_crear()
{	
	lista_t *nueva_lista = malloc(sizeof(lista_t));
	if (!nueva_lista)
		return NULL;
	nueva_lista->cantidad = 0;
	nueva_lista->nodo_inicio = NULL;
	nueva_lista->nodo_fin = NULL;
	
	return nueva_lista;
}

lista_t *lista_insertar(lista_t *lista, void *elemento)
{
	if (!lista)
		return NULL;
	nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
	if(!nuevo_nodo)
		return NULL;
	nuevo_nodo->elemento = elemento;
	if (lista_vacia(lista)){
		nuevo_nodo->siguiente = NULL;
		lista->nodo_fin = nuevo_nodo;
		lista->nodo_inicio = nuevo_nodo;
		lista->cantidad ++;
		return lista;
	}

	nuevo_nodo->siguiente = NULL;
	lista->nodo_fin->siguiente = nuevo_nodo;
	lista->nodo_fin = nuevo_nodo;
	lista->cantidad ++;
	return lista;
}


nodo_t *lista_buscar_nodo(lista_t *lista, size_t posicion){
	if (!lista)
		return NULL;
	nodo_t *nodo_actual = lista->nodo_inicio;
	if (posicion == 0)
		return nodo_actual;
	for (size_t i = 0; i < posicion; i++){
		nodo_actual = nodo_actual->siguiente;
	}
	return nodo_actual;
}

lista_t *lista_insertar_nodo_posicion (lista_t *lista, nodo_t *nuevo_nodo, size_t posicion)
{	
	if (posicion == 0){
		nuevo_nodo->siguiente = lista->nodo_inicio;
		lista->nodo_inicio = nuevo_nodo;
		lista->cantidad ++;
		return lista;
	}
	nodo_t *nodo_actual = lista_buscar_nodo(lista, posicion -1);
	nuevo_nodo->siguiente = nodo_actual->siguiente;
	nodo_actual->siguiente = nuevo_nodo;
	lista->cantidad ++;	
	return lista;
}

lista_t *lista_insertar_en_posicion(lista_t *lista, void *elemento,
				    size_t posicion)
{	
	if (!lista){
		return NULL;
	}
	lista_t *nueva_lista = NULL;
	if (lista->cantidad <= posicion){
		nueva_lista = lista_insertar(lista, elemento);
		if (!nueva_lista)
			return NULL;
		return nueva_lista;
	}
	nodo_t *nuevo_nodo = malloc(sizeof(nodo_t));
	if (!nuevo_nodo)
		return NULL;
	nuevo_nodo->elemento = elemento;
	nueva_lista = lista_insertar_nodo_posicion(lista, nuevo_nodo, posicion);
	return nueva_lista;
}

void *lista_quitar(lista_t *lista)
{	
	if(!lista)
		return NULL;
	if(lista_vacia(lista))
		return NULL;
	nodo_t *nodo_actual = lista->nodo_inicio;
	void* elemento_removido = NULL;
	if (lista->cantidad == 1){
		elemento_removido = nodo_actual->elemento;
		lista->nodo_inicio = NULL;
		lista->nodo_fin = NULL;
		free(nodo_actual);
		lista->cantidad--;
		return elemento_removido;
	}
	while(nodo_actual->siguiente != lista->nodo_fin)
		nodo_actual = nodo_actual->siguiente;
	elemento_removido = lista->nodo_fin->elemento;
	lista->nodo_fin = nodo_actual;
	free(lista->nodo_fin->siguiente);
	lista->nodo_fin->siguiente = NULL;
	lista->cantidad --;
	return elemento_removido;
}

void *lista_quitar_de_posicion(lista_t *lista, size_t posicion)
{	
	if (!lista || lista_vacia(lista))
		return NULL;
	nodo_t *nodo_aux = NULL;
	void *elemento_removido = NULL;
	if ((posicion>=lista->cantidad) || (lista->cantidad == 1))
		return lista_quitar(lista);
	if (posicion == 0){
		nodo_aux = lista->nodo_inicio;
		lista->nodo_inicio = lista->nodo_inicio->siguiente;
		elemento_removido = nodo_aux->elemento;
		free(nodo_aux);
		lista->cantidad--;
		return elemento_removido;
	}
	nodo_t *nodo_previo = lista_buscar_nodo(lista, posicion - 1);
	nodo_aux = nodo_previo->siguiente;
	nodo_previo->siguiente = nodo_aux->siguiente;
	elemento_removido = nodo_aux->elemento;
	free(nodo_aux);
	lista->cantidad --;	
	return elemento_removido;
}

void *lista_elemento_en_posicion(lista_t *lista, size_t posicion)
{	
	if (!lista || (posicion >= lista->cantidad) || lista_vacia(lista))
		return NULL;
	nodo_t *nodo_actual = lista_buscar_nodo(lista, posicion);
	return nodo_actual->elemento;
}

void *lista_buscar_elemento(lista_t *lista, int (*comparador)(void *, void *),
			    void *contexto)
{	
	if (!lista || !comparador)
		return NULL;
	nodo_t *nodo_actual = lista->nodo_inicio;
	int resultado = -1;
	while (nodo_actual){
		resultado = comparador(nodo_actual->elemento, contexto);
		if (resultado == 0)
			return nodo_actual->elemento;
		nodo_actual = nodo_actual->siguiente;
	}
	return NULL;
}

void *lista_primero(lista_t *lista)
{	
	if(!lista || lista_vacia(lista))
		return NULL;

	return lista->nodo_inicio->elemento;
}

void *lista_ultimo(lista_t *lista)
{
	if(!lista || lista_vacia(lista))
		return NULL;

	return lista->nodo_fin->elemento;
}

bool lista_vacia(lista_t *lista)
{	
	if (!lista) 
		return true;
	if ((lista->cantidad == 0) && lista->nodo_fin == NULL && lista->nodo_inicio == NULL)
		return true;
	return false;
}

size_t lista_tamanio(lista_t *lista)
{	
	if (!lista)
		return 0;
	return (*lista).cantidad;
}

void lista_destruir(lista_t *lista)
{
	if (!lista)
		return;
	while (lista->nodo_inicio){
		nodo_t *nodo_aux;
		nodo_aux = lista->nodo_inicio->siguiente;
		free(lista->nodo_inicio);
		lista->nodo_inicio = nodo_aux;
	}
	free(lista);
}

void lista_destruir_todo(lista_t *lista, void (*funcion)(void *))
{
	if (!lista)
		return;
	while (lista->nodo_inicio){
		nodo_t *nodo_aux;
		nodo_aux = lista->nodo_inicio->siguiente;
		if (lista->nodo_inicio->elemento && funcion)
			funcion(lista->nodo_inicio->elemento);
		free(lista->nodo_inicio);
		lista->nodo_inicio = nodo_aux;
	}
	free(lista);
}

lista_iterador_t *lista_iterador_crear(lista_t *lista)
{	
	if(!lista)
		return NULL;
	lista_iterador_t *nuevo_iterador = malloc(sizeof(lista_iterador_t));
	if (!nuevo_iterador)
		return NULL;
	nuevo_iterador->corriente = lista->nodo_inicio;
	nuevo_iterador->lista = lista;
	return nuevo_iterador;
}

bool lista_iterador_tiene_siguiente(lista_iterador_t *iterador)
{	
	if (!iterador)
		return false;
	if (iterador->corriente)
		return true;
	return false;
}

bool lista_iterador_avanzar(lista_iterador_t *iterador)
{
	if (!iterador)
		return false;
	if (iterador->corriente){
		nodo_t *nodo_aux = iterador->corriente->siguiente;
		iterador->corriente = nodo_aux;
		if (iterador->corriente)
			return true;
		return false;
	}
	return false;
}

void *lista_iterador_elemento_actual(lista_iterador_t *iterador)
{
	if (!iterador)
		return NULL;
	if (!iterador->corriente)
		return NULL;
	return iterador->corriente->elemento;
}

void lista_iterador_destruir(lista_iterador_t *iterador)
{
	if (iterador)
		free(iterador);

}

size_t lista_con_cada_elemento(lista_t *lista, bool (*funcion)(void *, void *),
			       void *contexto)
{
	if (!lista || !funcion)
		return 0;
	nodo_t *nodo_actual = lista->nodo_inicio;
	bool resultado = true;
	size_t i = 0;
	while(nodo_actual){
		resultado = funcion(nodo_actual->elemento, contexto);
		if (!resultado)
			return i+1;
		nodo_actual = nodo_actual->siguiente;
		i++;
	}
	return i;
}
