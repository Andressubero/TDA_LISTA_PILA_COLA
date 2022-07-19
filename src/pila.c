#include "pila.h"
#include "lista.h"

pila_t *pila_crear()
{	
	pila_t *nueva_pila = (pila_t*) lista_crear();
	if(!nueva_pila)
		return NULL;
	return nueva_pila;
}

pila_t *pila_apilar(pila_t *pila, void *elemento)
{	
	if (!pila)
		return NULL;
	return (pila_t*)lista_insertar((lista_t*)pila, elemento);
}

void *pila_desapilar(pila_t *pila)
{	
	if (!pila)
		return NULL;
	return lista_quitar((lista_t*)pila);
}

void *pila_tope(pila_t *pila)
{	
	if (!pila)
		return NULL;
	return lista_ultimo((lista_t*)pila);
}

size_t pila_tamanio(pila_t *pila)
{	
	if (!pila)
		return 0;
	return lista_tamanio((lista_t*)pila);
}

bool pila_vacia(pila_t *pila)
{	
	if (!pila)
		return true;
	return lista_vacia((lista_t*)pila);
}

void pila_destruir(pila_t *pila)
{
	if (pila)
		lista_destruir((lista_t*)pila);

}
