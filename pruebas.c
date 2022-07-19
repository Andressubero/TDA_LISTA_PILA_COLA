#include "src/lista.h"
#include "src/pila.h"
#include "src/cola.h"
#include <stdio.h>
#include <stdlib.h>
#include "pa2m.h"

 void free_aux(void *elemento)
{
        //aca libero memoria;
}

int lista_creada_distinta_de_null_y_estructuras_inicializadas()
{
        lista_t *lista = lista_crear();
        if (!lista)
                return -1;
        
        pa2m_afirmar((lista != NULL), "La lista fue creada exitosamente");
        pa2m_afirmar((lista_tamanio(lista) == 0), "La lista creada tiene 0 elementos");

        lista_destruir(lista);
        return 0;
}

int no_puedo_insertar_lista_nula ()
{
        int numero = 5;
        lista_t *lista = lista_insertar(NULL, &numero);
        pa2m_afirmar(!lista, "No puedo insertar un elemento al final en una lista nula");
        return 0;
}

int inserto_elemento_ultima_posicion_lista_vacia ()
{
        lista_t *lista = lista_crear();
        int numero = 5;
        lista_t *nueva_lista = lista_insertar(lista, &numero);
        if (!nueva_lista){
                lista_destruir(lista);
                return -1;
        }

        lista = nueva_lista;
        
        pa2m_afirmar(lista_ultimo(lista) == &numero,
        "El elemento se inserto en la ultima posicion con la lista vacia");
        pa2m_afirmar(lista_tamanio(lista) == 1,"El tamanio de la lista ahora es 1");
        pa2m_afirmar(lista_primero(lista) == &numero,
        "El elemento coincide con la primera posicion porque la lista estaba vacia");
        lista_destruir(lista);
        return 0;

}

int inserto_elemento_ultima_posicion_lista_no_vacia ()
{
        lista_t *lista = lista_crear();
        int numero_1 = 5;
        int numero_2 = 10;
        lista_t *lista_aux_1 = lista_insertar(lista, &numero_1);
        if (!lista_aux_1){
                lista_destruir(lista);
                return -1;
        }

        lista = lista_aux_1;

        lista_t *lista_aux_2 = lista_insertar(lista, &numero_2);
        if (!lista_aux_2){
                lista_destruir(lista);
                return -1;
        }
        lista = lista_aux_2;
        
        pa2m_afirmar(lista_ultimo(lista) == &numero_2,
        "El elemento se inserto en la ultima posicion con la lista no vacia vacia");
        pa2m_afirmar(lista_tamanio(lista) == 2,
        "El tamaño de la lista coincide con lo esperado");
        pa2m_afirmar(lista_primero(lista) == &numero_1,
        "El elemento que estaba primero, sigue estando primero");
        lista_destruir(lista);
        return 0;

}

int puedo_insertar_elemento_null_ultima_posicion(){

        lista_t *lista = lista_crear();
        lista_t *nueva_lista = lista_insertar(lista, NULL);
        if (!nueva_lista){
                lista_destruir(lista);
                return -1;
        }

        lista = nueva_lista;
        
        pa2m_afirmar(lista_ultimo(lista) == NULL,
        "El elemento se inserto en la ultima posicion y es null");
        pa2m_afirmar(lista_tamanio(lista) == 1,
        "El tamaño de la lista aumento al insertar el elemento NULL");
        lista_destruir(lista);
        return 0;

}

int no_puedo_insertar_en_posicion_lista_nula()
{       
        int numero = 5;
        lista_t *nueva_lista = lista_insertar_en_posicion(NULL, &numero, 3);
        pa2m_afirmar(!nueva_lista,
        "No puedo insertar un elemento en una posicion dada en una lista nula");
        return 0;
}

int elemento_insertado_ultimo_si_no_existe_posicion()
{
        int numero = 5; 
        lista_t *lista = lista_crear();
        lista_t *nueva_lista = lista_insertar_en_posicion(lista, &numero, 3);
        if (!nueva_lista)
                return -1;
        lista = nueva_lista;
        pa2m_afirmar(lista_ultimo(lista) == &numero,
        "El elemento se inserto en la ultima posicion si no existe la posicion dada");
        lista_destruir(lista);
        return 0;
}

int inserto_elemento_posicion_dada ()
{
        lista_t *lista = lista_crear();
        int numero_1 = 1;
        int numero_2 = 2;
        int numero_3 = 3;
        int numero_4 = 4;
        int numero_5 = 5;
        lista = lista_insertar(lista, &numero_1);
        lista = lista_insertar(lista, &numero_2);
        lista = lista_insertar(lista, &numero_3);
        lista = lista_insertar_en_posicion(lista, &numero_4, 1);
        lista = lista_insertar_en_posicion(lista, &numero_5, 4);
        pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == &numero_4,
        "El elemento se inserto en la posicion pedida");
        pa2m_afirmar(lista_elemento_en_posicion(lista, 4) == &numero_5,
        "El elemento se inserto en la previa ultima posicion");
         pa2m_afirmar(lista_tamanio(lista) == 5,
        "El tamaño de la lista aumento al insertar el elemento nuevo en la posicion");
        lista_destruir(lista);
        return 0;

}

int inserto_elemento_posicion_cero_lista_no_vacia ()
{
        lista_t *lista = lista_crear();
        int numero_1 = 1;
        int numero_2 = 2;
        int numero_3 = 3;
        int numero_4 = 4;
        lista = lista_insertar(lista, &numero_1);
        lista = lista_insertar(lista, &numero_2);
        lista = lista_insertar(lista, &numero_3);
        lista = lista_insertar_en_posicion(lista, &numero_4, 0);
        pa2m_afirmar(lista_elemento_en_posicion(lista, 0) == &numero_4,
        "El elemento se inserto en la posicion 0");
         pa2m_afirmar(lista_tamanio(lista) == 4,
        "El tamaño de la lista aumento al insertar el elemento nuevo en la posicion");
        lista_destruir(lista);
        return 0;

}

int elemento_coincide_con_buscado()
{
        lista_t *lista = lista_crear();
        int numero_1 = 1;
        int numero_2 = 2;
        int numero_3 = 3;
        lista = lista_insertar(lista, &numero_1);
        lista = lista_insertar(lista, &numero_2);
        lista = lista_insertar(lista, &numero_3);
        pa2m_afirmar(lista_elemento_en_posicion(lista, 1) == &numero_2,
        "El elemento encontrado en la posicion dada es el esperado");
        lista_destruir(lista);
        return 0;
}

int posicion_no_existe_devuelve_null()
{
        lista_t *lista = lista_crear();
        int numero_1 = 1;
        int numero_2 = 2;
        int numero_3 = 3;
        lista = lista_insertar(lista, &numero_1);
        lista = lista_insertar(lista, &numero_2);
        lista = lista_insertar(lista, &numero_3);
        pa2m_afirmar(lista_elemento_en_posicion(lista, 4) == NULL,
        "La posicion buscada no existe y devuelve NULL");
        lista_destruir(lista);
        return 0;
}

int no_puedo_quitar_ultimo_elemento_de_lista_null_o_vacia()
{
        lista_t *lista = lista_crear();
        pa2m_afirmar(lista_quitar(NULL) == NULL,
        "No puedo quitar ultimo elemento de una lista que no existe");
        pa2m_afirmar(lista_quitar(lista) == NULL,
        "No puedo quitar ultimo elemento de una lista vacia");
        lista_destruir(lista);
        return 0;
}

int quitar_ultimo_elemento_cantidad_disminuye_en_uno()
{       
        lista_t *lista = lista_crear();
        int numero_1 = 1;
        lista = lista_insertar(lista, &numero_1);
        pa2m_afirmar(lista_quitar(lista) == &numero_1,
        "Se removio el ultimo elemento y se retorno dicho elemento");
        pa2m_afirmar(lista_tamanio(lista) == 0,
        "Se disminuyo en uno el tamaño de la lista");
        lista_destruir(lista);
        return 0;

}

int quitar_elemento_posicion_dada()
{
        lista_t *lista = lista_crear();
        int numero_1 = 1;
        int numero_2 = 2;
        int numero_3 = 3;
        int numero_4 = 4;
        lista = lista_insertar(lista, &numero_1);
        lista = lista_insertar(lista, &numero_2);
        lista = lista_insertar(lista, &numero_3);
        lista = lista_insertar(lista, &numero_4);
        pa2m_afirmar(lista_quitar_de_posicion(lista, 0) == &numero_1,
        "Se removio el elemento de la posicion dada y se retorno dicho elemento");
        pa2m_afirmar(lista_tamanio(lista) == 3,
        "Se disminuyo en uno el tamaño de la lista al remover el elemento de la posicion");
        lista_destruir_todo(lista, free_aux);
        return 0;
}

int no_puedo_quitar_elemento_de_posicion_en_lista_null_o_vacia ()
{       
        lista_t *lista = lista_crear();
        pa2m_afirmar(lista_quitar_de_posicion(NULL, 3) == NULL,
        "No puedo quitar un elemento de una posicion dada de una lista NULL");
        pa2m_afirmar(lista_quitar_de_posicion(lista, 3) == NULL,
        "No puedo quitar un elemento de una posicion dada de una lista vacia");
        lista_destruir_todo(lista, free_aux);
        return 0;
}

int comparador_aux (void* elemento_1, void *elemento_2)
{
        int *ele_1 = (int*) elemento_1;
        int *ele_2 = (int*) elemento_2;
        if (*ele_1 == *ele_2)
                return 0;
        return -1;
}

int no_puedo_buscar_elemento_en_lista_funcion_o_contexto_null()
{
        lista_t *lista = lista_crear();
        int numero = 5;
        pa2m_afirmar(lista_buscar_elemento(NULL,comparador_aux, &numero) == NULL,
        "No puedo buscar elemento en una lista NULL");
        pa2m_afirmar(lista_buscar_elemento(lista, NULL, &numero) == NULL,
        "No puedo buscar elemento con un comparador NULL");
        pa2m_afirmar(lista_buscar_elemento(lista, comparador_aux, NULL) == NULL,
        "No puedo buscar un elemento con un contexto NULL");
        lista_destruir_todo(lista, free_aux);
        return 0;

}

int encuentra_elemento_buscado_y_lo_retorna ()
{
        lista_t *lista = lista_crear();
        int numero_1 = 1;
        int numero_2 = 2;
        int numero_3 = 3;
        int numero_4 = 4;
        int numero_5 = 2;
        int numero_6 = 6;
        lista = lista_insertar(lista, &numero_1);
        lista = lista_insertar(lista, &numero_2);
        lista = lista_insertar(lista, &numero_3);
        lista = lista_insertar(lista, &numero_4);
        pa2m_afirmar(lista_buscar_elemento(lista, comparador_aux, &numero_5) == &numero_2,
        "El elemento fue encontrado y retornado");
        pa2m_afirmar(lista_buscar_elemento(lista, comparador_aux, &numero_6) == NULL,
        "Retorna NULL si no encuentra un elemento igual al contexto");
        lista_destruir_todo(lista, free_aux);
        return 0;
}

int no_puedo_crear_iterador_lista_null ()
{
        pa2m_afirmar(lista_iterador_crear(NULL) == NULL,
        "No puedo crear iterador externo con lista NULL");
        return 0;
}

int puedo_crear_iterador_externo_lista_vacia()
{
        lista_t *nueva_lista = lista_crear();
        lista_iterador_t *nuevo_iterador = lista_iterador_crear(nueva_lista);
        pa2m_afirmar( nuevo_iterador != NULL,
        "Puedo crear un iterador externo con una lista vacia");
        lista_iterador_destruir(nuevo_iterador);
        lista_destruir(nueva_lista);
        return 0;
}

int iterador_tiene_siguiente_aunque_sea_null()
{
        lista_t *nueva_lista = lista_crear();
        int numero = 5;
        lista_insertar(nueva_lista, &numero);
        lista_iterador_t *iterador = lista_iterador_crear(nueva_lista);
        pa2m_afirmar(lista_iterador_tiene_siguiente(iterador) == true,
        "Iterador tiene siguiente aunque apunte a null");
        lista_iterador_destruir(iterador);
        lista_destruir(nueva_lista);
        return 0;
}

int iterador_avanza_si_tiene_siguiente()
{
        lista_t *nueva_lista = lista_crear();
        int numero = 5;
        lista_insertar(nueva_lista, &numero);
        lista_iterador_t *iterador = lista_iterador_crear(nueva_lista);
        pa2m_afirmar(lista_iterador_avanzar(iterador) == true,
        "Iterador avanza si tiene siguiente");
        lista_iterador_destruir(iterador);
        lista_destruir(nueva_lista);
        return 0;
}

int iterador_devuelve_elemento_posicion_actual()
{
        lista_t *nueva_lista = lista_crear();
        int numero = 5;
        lista_insertar(nueva_lista, &numero);
        lista_iterador_t *iterador = lista_iterador_crear(nueva_lista);
        pa2m_afirmar(lista_iterador_elemento_actual(iterador) == &numero,
        "Devuelve el elemento actual correctamente");
        lista_iterador_destruir(iterador);
        lista_destruir(nueva_lista);
        return 0;
}

int iterador_devuelve_null_ultima_posicion()
{
        lista_t *nueva_lista = lista_crear();
        int numero = 5;
        lista_insertar(nueva_lista, &numero);
        lista_iterador_t *iterador = lista_iterador_crear(nueva_lista);
        lista_iterador_avanzar(iterador);
        pa2m_afirmar(lista_iterador_elemento_actual(iterador) == NULL,
        "Cuando se encuentra en la ultima posicion devuelve NULL como elemento actual");
        lista_iterador_destruir(iterador);
        lista_destruir(nueva_lista);
        return 0;
}

bool aux_it_interno(void* elemento_1, void* elemento_2)
{
        if (elemento_1 == elemento_2)
                return false;
        return true;
}

int iterador_interno_recorre_elementos_hasta_que_funcion_retorne_false()
{
        lista_t *lista = lista_crear();
        int numero_1 = 1;
        int numero_2 = 2;
        int numero_3 = 3;
        lista = lista_insertar(lista, &numero_1);
        lista = lista_insertar(lista, &numero_2);
        lista = lista_insertar(lista, &numero_3);
        pa2m_afirmar(lista_con_cada_elemento(lista, aux_it_interno, &numero_2) == 1,
        "eL iterador interno devuelve la cantidad de elementos recorridos, recorrio un elemento");
        pa2m_afirmar(lista_con_cada_elemento(lista, aux_it_interno, NULL) == 3,
        "eL iterador interno devuelve la cantidad de elementos recorridos, al ser contexto == NULL, recorrio toda la lista");
        lista_destruir(lista);
        return 0;

}
void pila_creada_distinta_de_null_y_estructuras_inicializadas()
{
        pila_t *nueva_pila = pila_crear();
        pa2m_afirmar((nueva_pila != NULL), "La pila fue creada exitosamente");
        pa2m_afirmar((pila_tamanio(nueva_pila) == 0), "La pila creada tiene 0 elementos");
        pila_destruir(nueva_pila);
}

void puedo_apilar_un_elemento()
{
        pila_t *nueva_pila = pila_crear();
        char letra_a = 'a';
        pila_apilar(nueva_pila, &letra_a);
        pa2m_afirmar((pila_tope(nueva_pila) == &letra_a), "Se añadio 1 elemento a la pila");
        pa2m_afirmar((pila_tope(nueva_pila) == &letra_a), "Su tope ahora es el elemento añadido");
        pa2m_afirmar((pila_tamanio(nueva_pila) == 1), "La pila ahora tiene un elemento");
        pila_destruir(nueva_pila);
}

void no_puedo_apilar_en_pila_null()
{       
        char letra_a = 'a';
        pa2m_afirmar(pila_apilar(NULL, &letra_a) == NULL, "No puedo apilar elemento en pila NULL");
}

void puedo_desapilar_un_elemento()
{
        pila_t *nueva_pila = pila_crear();
        char letra_a = 'a';
        pila_apilar(nueva_pila, &letra_a);
        pa2m_afirmar(pila_desapilar(nueva_pila) == &letra_a, "Se desapilo 1 elemento y se retorno");
        pa2m_afirmar(pila_tamanio(nueva_pila) == 0, "La cantidad de la pila se disminuyo en 1");
        pila_destruir(nueva_pila);
}

void cola_creada_distinta_de_null_y_estructuras_inicializadas()
{
        cola_t *nueva_cola = cola_crear();
        pa2m_afirmar(nueva_cola != NULL, "Se creo la cola correctamente");
        cola_destruir(nueva_cola);
}

void puedo_encolar_un_elemento_tamanio_aumenta_en_uno()
{
        cola_t *nueva_cola = cola_crear();
        char letra_a = 'a';
        nueva_cola = cola_encolar(nueva_cola, &letra_a);
        pa2m_afirmar(nueva_cola != NULL, "Puedo encolar un elemento");
        pa2m_afirmar(cola_tamanio(nueva_cola) == 1, "El tamaño aumento en 1");
        cola_destruir(nueva_cola);

}
void puedo_encolar_elemento_null()
{
        cola_t *nueva_cola = cola_crear();
        nueva_cola = cola_encolar(nueva_cola, NULL);
        pa2m_afirmar(nueva_cola != NULL, "Puedo encolar un elemento NULL");
        pa2m_afirmar(cola_tamanio(nueva_cola) == 1, "El tamaño aumento en 1");
        cola_destruir(nueva_cola);
}
void no_puedo_encolar_o_desencolar_cola_null()
{
        char letra_b = 'b';
        pa2m_afirmar(cola_encolar(NULL, &letra_b) == NULL, "No puedo encolar en una cola NULL");
        pa2m_afirmar(cola_desencolar(NULL) == NULL, "No puedo desencolar en una cola NULL");
}

void puedo_desencolar_un_elemento()
{
        cola_t *nueva_cola = cola_crear();
        char letra_a = 'a';
        char letra_b = 'b';
        nueva_cola = cola_encolar(nueva_cola, &letra_a);
        nueva_cola = cola_encolar(nueva_cola, &letra_b);
        pa2m_afirmar(cola_desencolar(nueva_cola) == &letra_a, "desencole el primer elemento encolado");
        pa2m_afirmar(cola_desencolar(nueva_cola) == &letra_b, "desencole el primer elemento encolado");
        pa2m_afirmar(cola_tamanio(nueva_cola) == 0, "El tamaño disminuyo en 1");
        cola_destruir(nueva_cola);
}

int main() {

        pa2m_nuevo_grupo("Pruebas de creacion de lista");
        lista_creada_distinta_de_null_y_estructuras_inicializadas();

        pa2m_nuevo_grupo("Pruebas de de insercion de elementos en la lista");
        no_puedo_insertar_lista_nula();
        inserto_elemento_ultima_posicion_lista_vacia();
        inserto_elemento_ultima_posicion_lista_no_vacia();
        puedo_insertar_elemento_null_ultima_posicion();
        no_puedo_insertar_en_posicion_lista_nula();
        elemento_insertado_ultimo_si_no_existe_posicion();
        inserto_elemento_posicion_dada ();
        inserto_elemento_posicion_cero_lista_no_vacia ();
        elemento_coincide_con_buscado();
        posicion_no_existe_devuelve_null();

        pa2m_nuevo_grupo("Pruebas de quitar elementos de la lista");
        no_puedo_quitar_ultimo_elemento_de_lista_null_o_vacia();
        quitar_ultimo_elemento_cantidad_disminuye_en_uno();
        quitar_elemento_posicion_dada();
        no_puedo_quitar_elemento_de_posicion_en_lista_null_o_vacia();

        pa2m_nuevo_grupo("Pruebas de buscar elemento en la lista");
        no_puedo_buscar_elemento_en_lista_funcion_o_contexto_null();
        encuentra_elemento_buscado_y_lo_retorna();

        pa2m_nuevo_grupo("Pruebas de iterador externo");
        no_puedo_crear_iterador_lista_null();
        puedo_crear_iterador_externo_lista_vacia();
        iterador_tiene_siguiente_aunque_sea_null();
        iterador_avanza_si_tiene_siguiente();
        iterador_devuelve_elemento_posicion_actual();
        iterador_devuelve_null_ultima_posicion();
        pa2m_nuevo_grupo("Pruebas de iterador interno");
        iterador_interno_recorre_elementos_hasta_que_funcion_retorne_false();

        pa2m_nuevo_grupo("Pruebas de pila");
        pila_creada_distinta_de_null_y_estructuras_inicializadas();
        puedo_apilar_un_elemento();
        no_puedo_apilar_en_pila_null();
        puedo_desapilar_un_elemento();

        pa2m_nuevo_grupo("Pruebas de cola");
        cola_creada_distinta_de_null_y_estructuras_inicializadas();
        puedo_encolar_un_elemento_tamanio_aumenta_en_uno();
        puedo_encolar_elemento_null();
        no_puedo_encolar_o_desencolar_cola_null();
        puedo_desencolar_un_elemento();



  return pa2m_mostrar_reporte();
}
