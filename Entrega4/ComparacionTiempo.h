#pragma once
#include "CostoArco.h"


class ComparacionTiempo : public Comparacion<CostoArco>
{
public:
	ComparacionTiempo() {}
	~ComparacionTiempo() {}

	CompRetorno Comparar(const CostoArco& t1, const CostoArco& t2) const override;
};
