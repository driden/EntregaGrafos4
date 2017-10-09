#pragma once
template <class V, class A = int>
class TablaDijkstra
{
public:
	TablaDijkstra(const V &vengoDe,const A &arco);
	TablaDijkstra();
	~TablaDijkstra(){}

	A costo;
	V vengo;
	bool conocido;
};

#include "TablaDijkstra.cpp"