#ifndef GRAFO_MATRIZ_ADY_CPP
#define GRAFO_MATRIZ_ADY_CPP

#include "GrafoListaAdy.h"
#include "ListaEncadenada.h"

template <class V, class A>
GrafoListaAdy<V, A>::GrafoListaAdy(nat maxVertices, Puntero<FuncionHash<V>> func, const Comparador<V>& comp)
	:compVertice(comp)
{
	tope = -1;
	
	lGrafo = Array<Tupla<V,Puntero<Lista<NodoGrafo<V, A>>>>>(maxVertices);
	hashVertices = new HashCerradoImpl<V, A>(maxVertices * 2, func, comp);
	arrVertices = Array<V>(maxVertices, V());	
}

template <class V, class A>
const nat GrafoListaAdy<V, A>::GetPosVertice(const V& v) const
{
	return hashVertices->Obtener(v);
}

template <class V, class A>
const V& GrafoListaAdy<V, A>::GetVertice(const nat pos) const
{
	return arrVertices[pos];
}

template <class V, class A>
void GrafoListaAdy<V, A>::AgregarVertice(const V& v)
{
	tope++;
	arrVertices[tope] = v;
	hashVertices->Agregar(v);
	Puntero<Lista<NodoGrafo<V, A>>> lista = nullptr;
	Tupla<V, Puntero<Lista<NodoGrafo<V, A>>>>t(v, lista);
	lGrafo[tope] = t;
}
#endif
