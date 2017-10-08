#pragma once
#include "Comparacion.h"
#include "NodoGrafo.h"
#include "Comparador.h"

template <class V, class A>
class ComparacionNodoGrafo :
	public Comparacion<NodoGrafo<V,A>>
{
public:
	ComparacionNodoGrafo(Comparador<V> comparadorVertice, 
		Comparador<A> comparadorArista = Comparador<A>::Default);
	~ComparacionNodoGrafo(){}
	CompRetorno Comparar(const NodoGrafo<V, A>& t1, const NodoGrafo<V, A>& t2) const override;
private:
	Comparador<V> compV;
	Comparador<A> compA;
};

#include "ComparacionNodoGrafo.cpp"

