#pragma once
#include "CostoArco.h"

class ComparacionBaratoOmnibus : public Comparacion<CostoArco>
{
public:
	CompRetorno Comparar(const CostoArco& t1, const CostoArco& t2) const;
};
