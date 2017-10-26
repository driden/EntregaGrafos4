#pragma once
typedef unsigned int nat;
#define INFINITO 100000

class CostoNat
{

public:
	CostoNat(nat num);
	CostoNat();
	~CostoNat();

	static CostoNat Cero();

	static CostoNat Infinito();

	CostoNat operator+(const CostoNat& c) const;

private:
	nat numero;
};

