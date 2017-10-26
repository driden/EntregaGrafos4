#ifndef COSTO_NAT_H
#define COSTO_NAT_H

#include "CostoNat.h"

CostoNat::CostoNat()
{
	numero = INFINITO;
}
CostoNat::CostoNat(nat num)
{
	numero = num;
}

CostoNat::~CostoNat()
{
}

CostoNat CostoNat::Cero()
{
	return CostoNat(0);
}

CostoNat CostoNat::Infinito()
{
	return CostoNat(INFINITO);
}

CostoNat CostoNat::operator+(const CostoNat& c) const
{
	return CostoNat(numero + c.numero);
}
#endif
