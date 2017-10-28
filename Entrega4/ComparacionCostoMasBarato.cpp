#include "ComparacionCostoMasBarato.h"



ComparacionCostoMasBarato::ComparacionCostoMasBarato()
{
}


ComparacionCostoMasBarato::~ComparacionCostoMasBarato()
{
}

CompRetorno ComparacionCostoMasBarato::Comparar(const CostoArco& t1, const CostoArco& t2) const
{
	nat costo1, costo2, tiempo1, tiempo2, paradas1, paradas2;
	costo1 = t1.costo;
	costo2 = t2.costo;

	tiempo1 = t1.tiempo;
	tiempo2 = t2.tiempo;

	paradas1 = t1.paradas;
	paradas2 = t2.paradas;

	if (costo1 == costo2)
	{
		if (tiempo1 == tiempo2)
		{
			if (paradas1 == paradas2) return IGUALES;
			if (paradas1 > paradas2) return MAYOR;
			return MENOR;
		}
		else
		{
			if (tiempo1 > tiempo2) return MAYOR;
			return MENOR;
		}
	}
	else
	{
		if (costo1 > costo2) return MAYOR;
		return MENOR;
	}
}
