#include "CostoArco.h"


CostoArco::CostoArco(int avion, int bus, int costo, int tiempo, int paradas)
{
	aviones = avion;
	omnibuses = bus;
	this->costo = costo;
	this->tiempo = tiempo;
	this->paradas = paradas;
}

CostoArco::~CostoArco()
{
}

CostoArco CostoArco::Cero() 
{
	return CostoArco(0, 0, 0, 0, 0);
}

CostoArco CostoArco::Infinito()
{
	return CostoArco(INFINITO, INFINITO, INFINITO, INFINITO, INFINITO);
}