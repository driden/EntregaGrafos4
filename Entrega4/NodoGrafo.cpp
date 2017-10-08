#ifndef NODO_GRAFO_H
#define NODO_GRAFO_H

#include "NodoGrafo.h"

template <class V, class A>
NodoGrafo<V, A>::NodoGrafo(const V& v1, const V& v2, const A& arista, const nat peso)
{
	this->v1 = v1;
	this->v2 = v2;
	this->arista = arista;
	costo = peso;
}

#endif