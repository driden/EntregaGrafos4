#ifndef CP_BINARY_HEAP_CPP
#define CP_BINARY_HEAP_CPP

#include "CPBinaryHeap.h"

template <class T, class P>
CPBinaryHeap<T, P>::CPBinaryHeap(const Comparador<T>& compElementos, const Comparador<P>& compPrioridades,
	Puntero<FuncionHash<T>> fHashElementos) :
	compElementos(compElementos),
	compPrioridades(compPrioridades)
{
	this->fHash = fHashElementos;
	this->heap = Array<Tupla<T, P>>(100000);
	this->tope = 0;
	this->copia = Array<Tupla<T, P>>(0);
}

template <class T, class P>
void CPBinaryHeap<T, P>::SwapHeap(const nat pos1, const nat pos2)
{
	Tupla<T, P> aux = heap[pos2];
	heap[pos2] = heap[pos1];
	heap[pos1] = aux;
}

template <class T, class P>
void CPBinaryHeap<T, P>::InsertarConPrioridad(const T& e, const P& p)
{
	Tupla<T, P>tupla(e, p);

	// Primer paso, va al final
	heap[++tope] = tupla;

	// Cuidado con el heap, si llega al tamanio maximo, puedo tratar de acceder a tope*2 +1

	if (heap.Largo < tope*2+1)
	{
		// Resizing
		Array<Tupla<T, P>> heapMasLargo(tope * 2 + 1);
		Array<Tupla<T, P >>::Copiar(heap, heapMasLargo);
		heap = heapMasLargo;
	}

	// Flotar tupla y 
	for (nat hole = tope; hole > 1 && compPrioridades.EsMenor(heap[hole].Dato2, heap[hole / 2].Dato2); hole /= 2)
	{
		// hundir los menores
		SwapHeap(hole, hole / 2);
	}

}

template <class T, class P>
T CPBinaryHeap<T, P>::EliminarElementoMayorPrioridad()
{
	nat posMin = 0;
	SwapHeap(1, tope);
	tope--;

	for (nat i = 1; compPrioridades.EsMayor(heap[i].Dato2, heap[i * 2].Dato2) && i <= tope / 2; i *= 2)
	{
		posMin = i * 2;

		// busco el hijo mas chico
		if (compPrioridades.EsMenor(heap[i * 2 + 1].Dato2, heap[i * 2].Dato2))
			posMin = i * 2 + 1;

		SwapHeap(i, posMin);
	}

	return heap[tope + 1].Dato1;
}

template <class T, class P>
const T& CPBinaryHeap<T, P>::ObtenerElementoMayorPrioridad() const
{
	return heap[1].Dato1;
}

template <class T, class P>
nat CPBinaryHeap<T, P>::IndexOf(const T& e) const
{
	nat i = 0;
	for (; i < heap.Largo + 1 && compElementos.SonDistintos(e, heap[i].Dato1); i++)
	{

	}
	return i;
}

template <class T, class P>
Tupla<T, P> CPBinaryHeap<T, P>::ObtenerElementoYPrioridad(const T& e)
{
	nat i = IndexOf(e);
	return heap[i];
}

template <class T, class P>
nat CPBinaryHeap<T, P>::Largo() const
{
	return tope;
}

template <class T, class P>
bool CPBinaryHeap<T, P>::Pertenece(const T& e) const
{
	nat index = 0;
	index = this->IndexOf(e);
	return index != 0;
}

template <class T, class P>
void CPBinaryHeap<T, P>::EliminarPosicion(nat index)
{
	nat posMin = 0;
	SwapHeap(index, tope);
	tope--;

	for (nat i = 1; compPrioridades.EsMayor(heap[i].Dato2, heap[i * 2].Dato2) && i < heap.Largo / 2; i *= 2)
	{
		posMin = i * 2;

		// busco el hijo mas chico
		if (compPrioridades.EsMenor(heap[i * 2 + 1].Dato2, heap[i * 2].Dato2))
			posMin = i * 2 + 1;

		SwapHeap(i, posMin);
	}
}

template <class T, class P>
void CPBinaryHeap<T, P>::EliminarElemento(T& e)
{
	nat index = IndexOf(e);
	EliminarPosicion(index);
}

template <class T, class P>
void CPBinaryHeap<T, P>::CambiarPrioridad(const T& e, const P& p)
{
	nat index = IndexOf(e);
	Tupla<T, P> elem = heap[index];

	EliminarPosicion(index);

	elem.Dato2 = p;

	InsertarConPrioridad(e, p);
}

template <class T, class P>
bool CPBinaryHeap<T, P>::EstaVacia() const
{
	return tope == 0;
}

template <class T, class P>
bool CPBinaryHeap<T, P>::EstaLlena() const
{
	return heap.Largo == tope + 1;
}

template <class T, class P>
void CPBinaryHeap<T, P>::Vaciar()
{
	tope = 0;
}

template <class T, class P>
Puntero<ColaPrioridadExtendida<T, P>> CPBinaryHeap<T, P>::Clon() const
{
	return nullptr;
}

template <class T, class P>
Iterador<Tupla<T, P>> CPBinaryHeap<T, P>::ObtenerIterador() const
{
	//this->copia = Array<Tupla<T, P>>(0);
	//Array<Tupla<T, P>>::Copiar(heap, copia,1);
	Array<Tupla<T, P>> iter(tope);
	Array<Tupla<T, P>>::Copiar(heap, 1, tope, iter, 0);

	return iter.ObtenerIterador();

}
#endif
