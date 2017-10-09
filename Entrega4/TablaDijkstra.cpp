#ifndef TABLA_DIJKSTRA_CPP
#define TABLA_DIJKSTRA_CPP

#include "TablaDijkstra.h"

template <class V, class A>
TablaDijkstra<V, A>::TablaDijkstra(const V& vengoDe, const A& arco)
{
	this->costo = arco;
	this->vengo = vengoDe;	
	this->conocido = false;
}

template <class V, class A>
TablaDijkstra<V, A>::TablaDijkstra()
{
	this->costo = 900000000;
	this->vengo = V();
	this->conocido = false;
}
#endif
