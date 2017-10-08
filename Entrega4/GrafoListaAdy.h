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
	void BorrarArco(const V& v1, const V& v2) override;

	// SELECTORAS y PREDICADOS

	Iterador<V> Vertices() const override;
	Iterador<V> Adyacentes(const V& v) const override;
	Iterador<V> Incidentes(const V& v) const override;

	const A& ObtenerArco(const V& v1, const V& v2) const override;
	virtual nat CantidadVertices() const abstract;
	virtual nat CantidadArcos() const abstract;
	virtual nat CantidadAdyacentes(const V& v) const abstract;
	virtual nat CantidadIncidentes(const V& v) const abstract;

	virtual bool ExisteVertice(const V& v) const abstract;
	virtual bool ExisteArco(const V& v1, const V& v2) const abstract;
	virtual bool EstaLleno() const abstract;
	virtual bool EstaVacio() const abstract;

	virtual bool HayCamino(const V& vO, const V& vD) const abstract;
	virtual	TipoConexo EsConexo() const abstract;
	virtual	Iterador<V> OrdenTopologico() const abstract;
	virtual Iterador<Tupla<V, V>> ArbolCubrimientoMinimo(const FuncionCosto<V, A>& costo = FuncionCosto<V, A>::Default) const abstract;
	virtual Iterador<Iterador<V>> ComponentesConexas() const abstract;

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

	Puntero<Lista<NodoGrafo<V, A>>> GetListaAdyacencias(const V &v) const;
	Puntero<Lista<NodoGrafo<V, A>>> GetListaAdyacencias(const nat pos) const;
};
#include "GrafoListaAdy.cpp"

