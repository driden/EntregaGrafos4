#ifndef GRAFO_MATRIZ_ADY_CPP
#define GRAFO_MATRIZ_ADY_CPP

#include "GrafoMatrizAdy.h"

template <class V, class A>
GrafoMatrizAdy<V, A>::GrafoMatrizAdy(nat maxVertices, Puntero<FuncionHash<V>> func, const Comparador<V>& comp)
{
	this->matriz = Matriz<A>(maxVertices, A());
	this->vertices = Array<V>(maxVertices);
	this->compVertice = comp;
	this->fHash = func;
}

#endif