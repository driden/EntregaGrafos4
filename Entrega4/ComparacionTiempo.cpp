#include "ComparacionTiempo.h"

CompRetorno ComparacionTiempo::Comparar(const CostoArco& t1, const CostoArco& t2) const
{
	if (t1.tiempo > t2.tiempo) return MAYOR;
	if (t1.tiempo < t2.tiempo) return MENOR;
	if (t1.tiempo == t2.tiempo)
	{
		if (t1.costo > t2.costo) return MAYOR;
		if (t1.costo < t2.costo) return MENOR;
		if(t1.costo==t2.costo)
		{
			if (t1.paradas > t2.paradas) return MAYOR;
			if (t1.paradas < t2.paradas) return MENOR;
			return IGUALES;
		}
	}
	assert(false);
	return DISTINTOS;
}
