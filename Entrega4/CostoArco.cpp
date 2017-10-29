#include "CostoArco.h"


CostoArco::CostoArco()
{
	aviones = INFINITO;
	omnibuses = INFINITO;
	this->costo = INFINITO;
	this->tiempo = INFINITO;
	this->paradas = INFINITO;
	this->ciudades = INFINITO;
}

CostoArco::CostoArco(int avion, int bus, int costo, int tiempo, int paradas,int ciudades)
{
	aviones = avion;
	omnibuses = bus;
	this->costo = costo;
	this->tiempo = tiempo;
	this->paradas = paradas;
	this->ciudades = ciudades;
}

CostoArco::~CostoArco()
{
}

CostoArco CostoArco::Cero() 
{
	return CostoArco(0, 0, 0, 0, 0,0);
}

CostoArco CostoArco::Infinito()
{
	return CostoArco(INFINITO, INFINITO, INFINITO, INFINITO, INFINITO,INFINITO);
}