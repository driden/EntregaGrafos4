#pragma once
#include "Grafo.h"
#include "CostoArco.h"

template <class V,class A, class Costo >
class Funciones
{
public:
	Funciones(){}
	~Funciones(){}
	CostoArco CalcularCostoArco(Puntero <Grafo<V, Costo>> grafo, int vO, int vD);
};

template <class V, class A,class Costo>
CostoArco Funciones<V,A, Costo>::CalcularCostoArco(Puntero<Grafo<V, Costo>> grafo, int vO, int vD)
{
	V origen = grafo->GetVertice(vO);
	V destino = grafo->GetPosVertice(vD);
	Tupla<TipoTransporte, nat, nat, nat> arco = grafo->ObtenerArco(origen, destino);
	int aviones = arco.Dato1 == AVION ? 1 : 0;
	int bus = aviones == 0 ? 1 : 0;
	return CostoArco(aviones, bus, arco.Dato2, arco.Dato3, arco.Dato4);
}

