#ifndef GRAFO_MATRIZ_ADY_CPP
#define GRAFO_MATRIZ_ADY_CPP

#include "GrafoListaAdy.h"
#include "ListaEncadenada.h"
#include "HashAbiertoImpl.h"
#include "ComparacionNodoGrafo.h"
#include <locale>
#include "TablaDijkstra.h"
#include "CPBinaryHeap.h"
template <class V, class A>
GrafoListaAdy<V, A>::GrafoListaAdy(nat maxVertices, Puntero<FuncionHash<V>> func, const Comparador<V>& comp)
	:compVertice(comp)
{
	tope = -1;
	
	lGrafo = Array<Tupla<V,Puntero<Lista<NodoGrafo<V, A>>>>>(maxVertices);
	hashVertices = new HashAbiertoImpl<V, nat>(func,maxVertices * 2,comp);
	arrVertices = Array<V>(maxVertices, V());	
}

template <class V, class A>
const nat GrafoListaAdy<V, A>::GetPosVertice(const V& v) const
{
	return hashVertices->Obtener(v);
}

template <class V, class A>
const V& GrafoListaAdy<V, A>::GetVertice(const nat pos) const
{
	return arrVertices[pos];
}

template <class V, class A>
Puntero<Lista<NodoGrafo<V, A>>> GrafoListaAdy<V, A>::GetListaAdyacencias(const V& v) const
{
	const nat posV1 = GetPosVertice(v);

	Tupla<V, Puntero<Lista<NodoGrafo<V, A>>>> tupla = lGrafo[posV1];
	return tupla.Dato2;
}

template <class V, class A>
Puntero<Lista<NodoGrafo<V, A>>> GrafoListaAdy<V, A>::GetListaAdyacencias(const nat pos) const
{
	Tupla<V, Puntero<Lista<NodoGrafo<V, A>>>> tupla = lGrafo[pos];
	return tupla.Dato2;
}

template <class V, class A>
void GrafoListaAdy<V, A>::AgregarVertice(const V& v)
{
	tope++;
	arrVertices[tope] = v;
	hashVertices->Agregar(v,tope);
	Puntero<Lista<NodoGrafo<V, A>>> lista = nullptr;
	Tupla<V, Puntero<Lista<NodoGrafo<V, A>>>>t(v, lista);
	lGrafo[tope] = t;
}

template<class T>
void BorrarDeArray(Array<T> &arr, const nat pos, const nat tope)
{
	for (nat i = pos; i < tope; i++)
	{
		arr[i] = arr[i + 1];
	}
}

template <class V, class A>
void GrafoListaAdy<V, A>::BorrarVertice(const V& v)
{
	nat posV = GetPosVertice(v);

	//Sacarlo del grafo
	BorrarDeArray(lGrafo, posV, tope);
	
	//Sacarlo del array de vertices
	BorrarDeArray(arrVertices, posV, tope);

	//Sacarlo del hash
	hashVertices->Borrar(v);

	tope--;
}

template <class V, class A>
void GrafoListaAdy<V, A>::AgregarArco(const V& v1, const V& v2, const A& arco)
{
	// Arco de v1 a v2.
	// adyacencias de v1
	Puntero<Lista<NodoGrafo<V, A>>> adyacencias = GetListaAdyacencias(v1);

	if (adyacencias == nullptr)
	{
		Puntero<ComparacionNodoGrafo<V, A>> comparacion = new ComparacionNodoGrafo<V, A>(compVertice);
		Comparador<NodoGrafo<V, A>> comp = Comparador<NodoGrafo<V, A>>(comparacion);
		Puntero<Lista<NodoGrafo<V,A>>> lAdy = new ListaEncadenada<NodoGrafo<V, A>>(comp);
		
		nat posV = GetPosVertice(v1);
		lGrafo[posV].Dato2 = lAdy;

		adyacencias = lGrafo[posV].Dato2;
	}

	adyacencias->Insertar(NodoGrafo<V, A>(v1, v2, arco, 0));
}

template <class V, class A>
void GrafoListaAdy<V, A>::BorrarArco(const V& v1, const V& v2)
{
	Puntero<Lista<NodoGrafo<V, A>>> adyacencias = GetListaAdyacencias(v1);
	NodoGrafo<V, A> aBorrar(v1, v2);
	adyacencias->Eliminar(aBorrar);
}

template <class V, class A>
Iterador<V> GrafoListaAdy<V, A>::Vertices() const
{
	arrVertices.ObtenerIterador();
	Array<V> arrIteracion(tope + 1);

	Array<V>::Copiar(arrVertices, 0, tope + 1, arrIteracion, 0);
	return arrIteracion.ObtenerIterador();
}

template <class V, class A>
Iterador<V> GrafoListaAdy<V, A>::Adyacentes(const V& v) const
{
	Puntero<Lista<NodoGrafo<V, A>>> adyacencias = GetListaAdyacencias(v);
	Array<V> ady(arrVertices.Largo - 1);
	int tope = -1;

	if (!adyacencias) return ListaEncadenada<V>(compVertice).ObtenerIterador();

	Iterador<NodoGrafo<V, A>> itNodos = adyacencias->ObtenerIterador();

	while (itNodos.HayElemento())
	{
		NodoGrafo<V, A> nodo = itNodos.ElementoActual();
		ady[++tope] = nodo.v2;
		itNodos.Avanzar();
	}

	Array<V> arrayAdyacentes(tope + 1);
	Array<V>::Copiar(ady,0,tope+1, arrayAdyacentes,0);

	return arrayAdyacentes.ObtenerIterador();
}

template <class V, class A>
Iterador<V> GrafoListaAdy<V, A>::Incidentes(const V& v) const
{
	Puntero<Lista<V>> incidentes = new ListaEncadenada<V>(compVertice);

	for (int i = 0 ; i < tope; i++)
	{
		if (compVertice.SonIguales(lGrafo[i].Dato1, v))
			continue;

		// Busco en la lista de este vertice si aparece v como destino
		Puntero<Lista<NodoGrafo<V, A>>> adyacentes = GetListaAdyacencias(i);
		if (adyacentes == nullptr) continue;
		Iterador<NodoGrafo<V, A>> iterador = adyacentes->ObtenerIterador();

		while(iterador.HayElemento())
		{
			NodoGrafo<V, A> nodo = iterador.ElementoActual();
			if (compVertice.SonIguales(v, nodo.v2))
				incidentes->Insertar(nodo.v1);
			iterador.Avanzar();
		}
	}
	return incidentes->ObtenerIterador();
}

template <class V, class A>
const A& GrafoListaAdy<V, A>::ObtenerArco(const V& v1, const V& v2) const
{
	Puntero<Lista<NodoGrafo<V, A>>> adyacentes = GetListaAdyacencias(v1);
	Iterador<NodoGrafo<V, A>> iterador = adyacentes->ObtenerIterador();

	while (iterador.HayElemento())
	{
		NodoGrafo<V, A> nodo = iterador.ElementoActual();
		if (compVertice.SonIguales(v2, nodo.v2))
		{
			return (new NodoGrafo<V, A>(nodo.v1, nodo.v2, nodo.arista, 0))->arista;
		}

		iterador.Avanzar();
	}
	assert(false);
	return iterador.ElementoActual().arista;
}

template <class V, class A>
nat GrafoListaAdy<V, A>::CantidadVertices() const
{
	return tope + 1;
}

template <class V, class A>
nat GrafoListaAdy<V, A>::CantidadArcos() const
{
	nat total = 0;
	for(int i = 0; i < tope; i++)
	{
		Puntero<Lista<NodoGrafo<V, A>>> adyacentes = GetListaAdyacencias(i);
		if (adyacentes == nullptr) continue;

		total += adyacentes->Largo();
	}
	return total;
}

template <class V, class A>
nat GrafoListaAdy<V, A>::CantidadAdyacentes(const V& v) const
{
	Puntero<Lista<NodoGrafo<V, A>>> adyacentes = GetListaAdyacencias(v);
	const nat total = adyacentes != nullptr ? adyacentes->Largo() : 0;
	return total;
}

template <class V, class A>
nat GrafoListaAdy<V, A>::CantidadIncidentes(const V& v) const
{
	nat incidentes = 0;

	for (int i = 0; i < tope; i++)
	{
		if (compVertice.SonIguales(lGrafo[i].Dato1, v))
			continue;

		// Busco en la lista de este vertice si aparece v como destino
		Puntero<Lista<NodoGrafo<V, A>>> adyacentes = GetListaAdyacencias(i);
		if (adyacentes == nullptr) continue;
		Iterador<NodoGrafo<V, A>> iterador = adyacentes->ObtenerIterador();

		while (iterador.HayElemento())
		{
			NodoGrafo<V, A> nodo = iterador.ElementoActual();
			if (compVertice.SonIguales(v, nodo.v2))
				incidentes++;
			iterador.Avanzar();
		}
	}
	return incidentes;
}

template <class V, class A>
bool GrafoListaAdy<V, A>::ExisteVertice(const V& v) const
{
	for(int i = 0; i < tope + 1 ; i++)
	{
		if (compVertice.SonIguales(v, arrVertices[i])) return true;
	}

	return false;
}

template <class V, class A>
bool GrafoListaAdy<V, A>::ExisteArco(const V& v1, const V& v2) const
{
	Puntero<Lista<NodoGrafo<V, A>>> adyacentes = GetListaAdyacencias(v1);

	if (!adyacentes) return false;

	Iterador<NodoGrafo<V, A>> itAdyacentes = adyacentes->ObtenerIterador();

	while (itAdyacentes.HayElemento())
	{
		NodoGrafo<V, A> nodo = itAdyacentes.ElementoActual();
		itAdyacentes.Avanzar();

		if (compVertice.SonIguales(v2, nodo.v2)) return true;
	}
	return false;
}

template <class V, class A>
bool GrafoListaAdy<V, A>::EstaLleno() const
{
	return tope == arrVertices.Largo;
}

template <class V, class A>
bool GrafoListaAdy<V, A>::EstaVacio() const
{
	return tope == -1;
}

template <class V, class A>
Array<TablaDijkstra<V,A>> GrafoListaAdy<V, A>::Dijkstra(const V& vO, const V& vD) const
{
	Array<TablaDijkstra<V, A>> tabla(tope + 1);



}

template <class V, class A>
bool GrafoListaAdy<V, A>::HayCamino(const V& vO, const V& vD) const
{

	return false;
}

template <class V, class A>
TipoConexo GrafoListaAdy<V, A>::EsConexo() const
{
	return NO_CONEXO;
}

template <class V, class A>
Iterador<V> GrafoListaAdy<V, A>::OrdenTopologico() const
{
	return arrVertices.ObtenerIterador();
}

template <class V, class A>
Iterador<Tupla<V, V>> GrafoListaAdy<V, A>::ArbolCubrimientoMinimo(const FuncionCosto<V, A>& costo) const
{
	Array<Tupla<V, V>> arrVV(1);
	return arrVV.ObtenerIterador();
}

template <class V, class A>
Iterador<Iterador<V>> GrafoListaAdy<V, A>::ComponentesConexas() const
{
	return nullptr;
}

#endif
