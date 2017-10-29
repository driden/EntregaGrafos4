#include "ComparacionOmnibus.h"

CompRetorno ComparacionOmnibus::Comparar(const CostoArco& t1, const CostoArco& t2) const
{
	if (t1.omnibuses > t2.omnibuses) return MAYOR;
	if (t1.omnibuses < t2.omnibuses) return MENOR;

	if (t1.tiempo > t2.tiempo) return MAYOR;
	if (t1.tiempo < t2.tiempo) return MENOR;

	return IGUALES;
}
