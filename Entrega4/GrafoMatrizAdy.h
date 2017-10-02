#pragma once

#include "Grafo.h"
#include "Matriz.h"

template <class V, class A>
class GrafoMatrizAdy: public Grafo<V,A>
{
public:
	
	GrafoMatrizAdy(nat maxVertices, Puntero<FuncionHash<V>> func, const Comparador<V>& comp);
	~GrafoMatrizAdy(){}

	private:
		Matriz<A> matriz;
		Puntero<FuncionHash<V>> fHash;
		const Comparador<V> compVertice;
		Array<V> vertices;
};
#include "GrafoMatrizAdy.cpp"

