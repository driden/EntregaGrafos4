#ifndef SISTEMATEMPLATES_CPP
#define SISTEMATEMPLATES_CPP

#include "Sistema.h"
#include "GrafoListaAdy.h"

template <class V, class A>
Tupla<TipoRetorno, Puntero<Grafo<V, A>>> Sistema::CrearGrafo(nat maxVertices, Puntero<FuncionHash<V>> funcionHash, const Comparador<V>& comp)
{
	Puntero <Grafo<V, A>> grafo = new GrafoListaAdy<V, A>(maxVertices, funcionHash, comp);
	return Tupla<TipoRetorno, Puntero<Grafo<V, A>>>(OK, grafo);
}


#endif