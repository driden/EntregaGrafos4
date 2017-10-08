#ifndef TABLA_DIJKSTRA_CPP
#define TABLA_DIJKSTRA_CPP

#include "TablaDijkstra.h"
template <class V, class A>
TablaDijkstra<V, A>::TablaDijkstra(const V& vengoDe, const V& actual, const A& arco)
{
	this->arco = arco;
	this->v1 = vengoDe;
	this->v2 = actual;
	this->conocido = false;
}

template <class V, class A>
TablaDijkstra<V, A>::TablaDijkstra()
{
	this->arco = A();
	this->v1 = V();
	this->v2 = V();
	this->conocido = false;
}
#endif
