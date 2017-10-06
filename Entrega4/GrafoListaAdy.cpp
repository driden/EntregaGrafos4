#include "Lista.h"
#ifndef GRAFO_MATRIZ_ADY_CPP
#define GRAFO_MATRIZ_ADY_CPP

#include "GrafoListaAdy.h"

template <class V, class A>
GrafoListaAdy<V, A>::GrafoListaAdy(nat maxVertices, Puntero<FuncionHash<V>> func, const Comparador<V>& comp)
	:compVertice(comp)
{
	tope = -1;
	
	lGrafo = Array<ListaOrd<Lista<NodoGrafo<V, A>>>>(maxVertices, nullptr);
	arrVertices = Array<V>(maxVertices, V());

	hashVertices = new HashCerradoImpl<V, A>(maxVertices * 2, func,comp);
}




#endif