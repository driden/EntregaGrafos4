#include "ComparacionCiudades.h"

CompRetorno ComparacionCiudades::Comparar(const CostoArco& t1, const CostoArco& t2) const
{
	if (t1.ciudades > t2.ciudades) return MAYOR;
	if (t1.ciudades < t2.ciudades) return MENOR;
	
	if (t1.ciudades == t2.ciudades)
	{
		if (t1.paradas > t2.paradas) return MAYOR;
		if (t1.paradas < t2.paradas) return MENOR;
		if (t1.paradas == t2.paradas) return IGUALES;
	}
	assert(false);
	return DISTINTOS;
}
