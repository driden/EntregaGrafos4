#ifndef GRAFO_MATRIZ_ADY_CPP
#define GRAFO_MATRIZ_ADY_CPP

#include "GrafoMatrizAdy.h"
#include "NaturalFuncionHash.h"

template <class V, class A>
GrafoMatrizAdy<V, A>::GrafoMatrizAdy(nat maxVertices, Puntero<FuncionHash<V>> func, const Comparador<V>& comp)
{
	this->matriz = Matriz<A>(maxVertices, A());
	this->vertices = Array<V>(maxVertices);
	this->compVertice = comp;
	this->fHash = func;
	this->hashVertices = new HashCerradoImpl<V, nat>(maxVertices,func,comp);
	this->hashNatVertices = new HashCerradoImpl<nat, V>(maxVertices,new NaturalFuncionHash(), Comparador<nat>::Default);
}

#endif