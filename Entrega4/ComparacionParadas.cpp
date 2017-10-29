#include "ComparacionParadas.h"

CompRetorno ComparacionParadas::Comparar(const CostoArco& t1, const CostoArco& t2) const
{
	if (t1.paradas > t2.paradas) return MAYOR;
	if (t1.paradas < t2.paradas) return MENOR;

	if (t1.costo > t2.costo) return MAYOR;
	if (t1.costo < t2.costo) return MENOR;

	return IGUALES;
}
