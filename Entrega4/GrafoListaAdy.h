#pragma once

#include "Grafo.h"
#include "NodoGrafo.h"
#include "ListaEncadenada.h"
#include "Tabla.h"
#include "TablaDijkstra.h"
template <class V, class A>
class GrafoListaAdy : public Grafo<V, A>
{
public:

	GrafoListaAdy(nat maxVertices, Puntero<FuncionHash<V>> func, const Comparador<V>& comp);
	~GrafoListaAdy() {}

	void AgregarVertice(const V& v) override;
	void BorrarVertice(const V& v) override;
	void AgregarArco(const V& v1, const V& v2, const A& arco) override;
	void BorrarArco(const V& v1, const V& v2) override;

	// SELECTORAS y PREDICADOS

	Iterador<V> Vertices() const override;
	Iterador<V> Adyacentes(const V& v) const override;
	Iterador<V> Incidentes(const V& v) const override;

	const A& ObtenerArco(const V& v1, const V& v2) const override;
	nat CantidadVertices() const override;
	nat CantidadArcos() const override;
	nat CantidadAdyacentes(const V& v) const override;
	nat CantidadIncidentes(const V& v) const override;

	bool ExisteVertice(const V& v) const override;
	bool ExisteArco(const V& v1, const V& v2) const override;
	bool EstaLleno() const override;
	bool EstaVacio() const override;


	bool HayCamino(const V& vO, const V& vD) const override;
	TipoConexo EsConexo() const override;
	Iterador<V> OrdenTopologico() const override;
	Iterador<Tupla<V, V>> ArbolCubrimientoMinimo(const FuncionCosto<V, A>& costo = FuncionCosto<V, A>::Default) const override;
	Iterador<Iterador<V>> ComponentesConexas() const override;

private:
	//Estructuras
	Array<Tupla<V, Puntero<Lista<NodoGrafo<V, A>>>>> lGrafo; // Lista de adyacencias
	Puntero<Tabla<V, nat>> hashVertices; // para acceder al mappeo vertice -> nat 
	Array<V> arrVertices;// Para acceder nat -> vertice
	Puntero<FuncionHash<V>> fHash;
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

	Puntero<Lista<NodoGrafo<V, A>>> GetListaAdyacencias(const V &v) const;
	Puntero<Lista<NodoGrafo<V, A>>> GetListaAdyacencias(const nat pos) const;
	Array<TablaDijkstra<V,A>> Dijkstra(const V& vO, const V& vD, Array<TablaDijkstra<V, A>> tabla) const;
};
#include "GrafoListaAdy.cpp"

