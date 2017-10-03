#pragma once

#include "Grafo.h"
#include "Matriz.h"
#include "HashCerradoImpl.h"

template <class V, class A>
class GrafoMatrizAdy : public Grafo<V, A>
{
public:

	GrafoMatrizAdy(nat maxVertices, Puntero<FuncionHash<V>> func, const Comparador<V>& comp);
	~GrafoMatrizAdy() {}

private:
	Matriz<A> matriz;
	Puntero<FuncionHash<V>> fHash;
	const Comparador<V> compVertice;
	Puntero<Tabla<V, nat>> hashVertices;
	Puntero<Tabla<nat, V>> hashNatVertices;


	// Funciones

	// Pre: existe vertice V en el grafo
	// Pos: devuelve el natural que ocupa el Vertice en el hash
	const nat GetPosVertice(const V &v) const;

	// Pre: Existe un V con posicion pos
	// Pos: Devuelve una referencia al vertice en la posicion "pos"
	const V& GetVertice(const nat pos) const;
};
#include "GrafoMatrizAdy.cpp"

