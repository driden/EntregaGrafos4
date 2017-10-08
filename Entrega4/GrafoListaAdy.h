#pragma once

#include "Grafo.h"
#include "NodoGrafo.h"
#include "ListaEncadenada.h"
#include "Tabla.h"

template <class V, class A>
class GrafoListaAdy : public Grafo<V, A>
{
public:

	GrafoListaAdy(nat maxVertices, Puntero<FuncionHash<V>> func, const Comparador<V>& comp);
	~GrafoListaAdy() {}

	void AgregarVertice(const V& v) override;
	void BorrarVertice(const V& v) override;
	void AgregarArco(const V& v1, const V& v2, const A& arco) override;

private:
	//Estructuras
	Array<Tupla<V, Puntero<Lista<NodoGrafo<V, A>>>>> lGrafo; // Lista de adyacencias
	Puntero<Tabla<V, nat>> hashVertices; // para acceder al mappeo vertice -> nat 
	Array<V> arrVertices;// Para acceder nat -> vertice
	
	// Puntero<FuncionHash<V>> fHash; 
	const Comparador<V> compVertice;
	int tope;
	
	// Funciones

	// Pre: existe vertice V en el grafo
	// Pos: devuelve el natural que ocupa el Vertice en el hash
	const nat GetPosVertice(const V &v) const;

	// Pre: Existe un V con posicion pos
	// Pos: Devuelve una referencia al vertice en la posicion "pos"
	const V& GetVertice(const nat pos) const;
};
#include "GrafoListaAdy.cpp"

