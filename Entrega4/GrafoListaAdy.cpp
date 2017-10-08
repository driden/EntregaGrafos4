#ifndef GRAFO_MATRIZ_ADY_CPP
#define GRAFO_MATRIZ_ADY_CPP

#include "GrafoListaAdy.h"
#include "ListaEncadenada.h"
#include "HashAbiertoImpl.h"

template <class V, class A>
GrafoListaAdy<V, A>::GrafoListaAdy(nat maxVertices, Puntero<FuncionHash<V>> func, const Comparador<V>& comp)
	:compVertice(comp)
{
	tope = -1;
	
	lGrafo = Array<Tupla<V,Puntero<Lista<NodoGrafo<V, A>>>>>(maxVertices);
	hashVertices = new HashAbiertoImpl<V, A>(func,maxVertices * 2,comp);
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

template <class V, class A>
void GrafoListaAdy<V, A>::BorrarVertice(const V& v)
{
	nat posV = GetPosVertice(v);

	//Sacarlo del grafo
	BorrarDeArray(lGrafo, posV, tope);
	
	//Sacarlo del array de vertices
	BorrrarDeArray(arrVertices, posV, tope);

	//Sacarlo del hash
	hashVertices->Borrar(v);

	tope--;
}

template <class V, class A>
void GrafoListaAdy<V, A>::AgregarArco(const V& v1, const V& v2, const A& arco)
{
	// Arvo de v1 a v2.
	// Busco a v1 primero.
	nat posV1 = GetPosVertice(v1);
	
	Tupla<V, Puntero<Lista<NodoGrafo<V, A>>>> tupla = lGrafo[posV1];
	Puntero<Lista<NodoGrafo<V, A>>> adyacencias = tupla.Dato2;

	if (adyacencias == nullptr)
		adyacencias = new ListaEncadenada<NodoGrafo<V, A>>();
	
}

template<class T>
void BorrarDeArray(Array<T> &arr, const nat pos, const nat tope)
{
	for(nat i = pos; i < tope; i++ )
	{
		arr[i] = arr[i + 1];
	}	
}
#endif
