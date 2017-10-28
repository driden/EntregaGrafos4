#pragma once
#include "CostoArco.h"

class ComparacionCostoMasBarato : public Comparacion<CostoArco>
{
public:
	ComparacionCostoMasBarato();
	~ComparacionCostoMasBarato();

	CompRetorno Comparar(const CostoArco& t1, const CostoArco& t2) const override;
};

