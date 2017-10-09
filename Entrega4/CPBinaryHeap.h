#pragma once

#include "ColaPrioridadExtendida.h"
#include "Array.h"
#include "FuncionHash.h"

template <class T, class P>
class CPBinaryHeap : public ColaPrioridadExtendida<T, P>
{
private:
	nat tope;
	Array<Tupla<T,P>> heap;
	Array<Tupla<T, P>> copia;
	Comparador<T> compElementos;
	Comparador<P> compPrioridades;
	Puntero<FuncionHash<T>> fHash;	

	// PRE: -
	// POS: Devuelve la posicion en el heap de e, o 0 si no esta
	nat IndexOf(const T& e) const;
	
	// PRE: Existen elementos en el heap en pos1 y pos2
	// POS: El elemento que estaba en pos1 ahora esta en pos2 y viceversa
	void SwapHeap(const nat pos1, const nat pos2);

	// PRE: Existe un elemento en la posicion index
	// POS: Se elimina el elemento en la posicion index del heap
	void EliminarPosicion(nat index);
public:
	~CPBinaryHeap() { fHash = nullptr; }
	CPBinaryHeap(const Comparador<T>& compElementos, const Comparador<P>& compPrioridades, Puntero<FuncionHash<T>> fHashElementos);
	
	// PRE: -
	// POS: Inserta el elemento e con prioridad p
	void InsertarConPrioridad(const T& e, const P& p) override;

	// PRE: La cola de prioridad no está vacía
	// POS: Retorna el elemento de mayor prioridad en la cola eliminándolo
	T EliminarElementoMayorPrioridad() override;

	// PRE: La cola no está vacía
	// POS: Retorna el elemento de mayor prioridad en la cola sin eliminarlo
	const T& ObtenerElementoMayorPrioridad() const override;

	// PRE: El elemento e pertenece a la cola.
	// POS: Retorna una tupla que contiene al elemento e y su prioridad.
	Tupla<T, P> ObtenerElementoYPrioridad(const  T& e) override;

	// PRE: -
	// POS: Retorna el largo de la cola de prioridad
	nat Largo() const override;

	// PRE: -
	// POS: Retorna true si y solo si el elemento e pertenece a la cola.
	bool Pertenece(const T& e) const override;	

	// PRE: El elemento e pertenece a la cola.
	// POS: El elemento e tiene una nueva prioridad p.
	void CambiarPrioridad(const T& e, const P& p) override;

	// PRE: El elemento e pertenece a la cola.
	// POS: El elemento e no pertenece a la cola.
	void EliminarElemento(T& e) override;

	// PRE: -
	// POS: Retorna true si y solo si la cola esta vacia
	bool EstaVacia() const override;

	// PRE: -
	// POS: Retorna true si y solo si la cola esta llena
	bool EstaLlena() const override;

	// PRE: -
	// POS: La cola esta vacía
	void Vaciar() override;

	// PRE: -
	// POS: Retorna un clon de la cola que no comparte memoria con ella
	Puntero<ColaPrioridadExtendida<T, P>> Clon() const override;

	// Retorna un nuevo iterador sobre la estructura
	// Postcondición: El iterador se encuentra reiniciado
	Iterador<Tupla<T,P>> ObtenerIterador() const override;

};
#include "CPBinaryHeap.cpp"