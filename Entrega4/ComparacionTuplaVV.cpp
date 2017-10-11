#ifndef  COMPARACION_TUPLA_VV_CPP
#define COMPARACION_TUPLA_VV_CPP

#include "ComparacionTuplaVV.h"

template <class V>
ComparacionTuplaVV<V>::ComparacionTuplaVV(Comparador<V> compV)
{
	comp = compV;
}

template <class V>
CompRetorno ComparacionTuplaVV<V>::Comparar(const Tupla<V, V>& t1, const Tupla<V, V>& t2) const
{
	if (comp.SonIguales(t1.Dato1, t2.Dato1) && comp.SonIguales(t1.Dato2, t2.Dato2))
		return IGUALES;
	return DISTINTOS;
}

#endif