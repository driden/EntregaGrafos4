#pragma once
template <class V, class A>
class TablaDijkstra
{
public:
	TablaDijkstra(const V &vengoDe, const V &actual, const A &arco);
	TablaDijkstra();
	~TablaDijkstra(){}

	A arco;
	V v1;
	V v2;
	bool conocido;
};

#include "TablaDijkstra.cpp"