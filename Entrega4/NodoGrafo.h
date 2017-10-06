#pragma once

unsigned int typedef nat;
template <class V, class A>
class NodoGrafo
{
public:
	NodoGrafo();
	~NodoGrafo();
private:
	V vertice;
	A arista;
	nat costo;
};

