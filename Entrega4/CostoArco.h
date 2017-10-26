#pragma once
#include "Sistema.h"

#define INFINITO 100000
class CostoArco
{
public:
	CostoArco(int avion,int bus, int costo, int tiempo, int paradas);
	~CostoArco();

	static CostoArco Cero();

	static CostoArco Infinito();

	CostoArco operator+(const CostoArco& c) const
	{
		CostoArco ret(aviones + c.aviones, omnibuses + c.omnibuses, costo + c.costo, tiempo + c.tiempo, paradas + c.paradas);
		return ret;
	}
	
private:
	int costo, tiempo, paradas,aviones,omnibuses;
	
};

inline ostream& operator<<(ostream& out, const CostoArco& c)
{
	return out;
}