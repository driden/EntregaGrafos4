#include "ComparacionAviones.h"

CompRetorno ComparacionAviones::Comparar(const CostoArco& t1, const CostoArco& t2) const
{
	if (t1.aviones > t2.aviones) return MAYOR;
	if (t1.aviones < t2.aviones) return MENOR;

	if (t1.tiempo > t2.tiempo) return MAYOR;
	if (t1.tiempo < t2.tiempo) return MENOR;

	return IGUALES;
}
