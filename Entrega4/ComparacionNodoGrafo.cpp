#ifndef COMPARACION_NODO_GRAFO_CPP
#define COMPARACION_NODO_GRAFO_CPP
#include "ComparacionNodoGrafo.h"

template <class V, class A>
ComparacionNodoGrafo<V, A>::ComparacionNodoGrafo(Comparador<V> comparadorVertice, 
	Comparador<A> comparadorArista = Comparador<A>::Default)
{
	compV = comparadorVertice;
	compA = comparadorArista;
}

template <class V, class A>
CompRetorno ComparacionNodoGrafo<V, A>::Comparar(const NodoGrafo<V, A>& t1, const NodoGrafo<V, A>& t2) const
{
	if (compV.SonIguales(t1.v1,t2.v1) && compV.SonIguales(t1.v2,t2.v2))
	{
		return IGUALES;
	}
	return DISTINTOS;
}

#endif
