#pragma once
#include "Sistema.h"

#ifndef INFINITO
#define INFINITO 100000
#endif
class CostoArco
{
public:
	CostoArco();
	CostoArco(int avion,int bus, int costo, int tiempo, int paradas,int ciudades);
	~CostoArco();

	static CostoArco Cero();

	static CostoArco Infinito();

	CostoArco operator+(const CostoArco& c) const
	{
		CostoArco ret(aviones + c.aviones, omnibuses + c.omnibuses, costo + c.costo, tiempo + c.tiempo, paradas + c.paradas,ciudades+1);
		return ret;
	}
	
	int costo, tiempo, paradas,aviones,omnibuses, ciudades;
	
};

inline ostream& operator<<(ostream& out, const CostoArco& c)
{
	return out;
}