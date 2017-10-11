#pragma once
#include "Comparacion.h"
#include "Tupla.h"

template <class V>
class ComparacionTuplaVV : public Comparacion<Tupla<V,V>>
{
public:
	ComparacionTuplaVV(Comparador<V> compV);
	~ComparacionTuplaVV(){}

	CompRetorno Comparar(const Tupla<V, V>& t1, const Tupla<V, V>& t2) const override;
private:
	Comparador<V> comp;	
};


#include "ComparacionTuplaVV.cpp"
