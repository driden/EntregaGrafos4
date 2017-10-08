#pragma once

unsigned int typedef nat;
template <class V, class A>
class NodoGrafo
{
public:
	NodoGrafo();
	NodoGrafo(const V &v1,const V &v2, const A &arista, const nat peso );
	NodoGrafo(const V &v1, const V &v2);
	~NodoGrafo() {}

//private:
	V v1;
	V v2;
	A arista;
	nat costo;
};
#include "NodoGrafo.cpp"

