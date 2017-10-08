#include "ComparacionNodoGrafo.h"
#ifndef GRAFO_MATRIZ_ADY_CPP
#define GRAFO_MATRIZ_ADY_CPP

#include "GrafoListaAdy.h"
#include "ListaEncadenada.h"
#include "HashAbiertoImpl.h"

template <class V, class A>
GrafoListaAdy<V, A>::GrafoListaAdy(nat maxVertices, Puntero<FuncionHash<V>> func, const Comparador<V>& comp)
	:compVertice(comp)
{
	tope = -1;
	
	lGrafo = Array<Tupla<V,Puntero<Lista<NodoGrafo<V, A>>>>>(maxVertices);
	hashVertices = new HashAbiertoImpl<V, A>(func,maxVertices * 2,comp);
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
	hashVertices->Agregar(v);
	Puntero<Lista<NodoGrafo<V, A>>> lista = nullptr;
	Tupla<V, Puntero<Lista<NodoGrafo<V, A>>>>t(v, lista);
	lGrafo[tope] = t;
}

template <class V, class A>
void GrafoListaAdy<V, A>::BorrarVertice(const V& v)
{
	nat posV = GetPosVertice(v);

	//Sacarlo del grafo
	BorrarDeArray(lGrafo, posV, tope);
	
	//Sacarlo del array de vertices
	BorrrarDeArray(arrVertices, posV, tope);

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
		adyacencias = new ListaEncadenada<NodoGrafo<V, A>>(comp);
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

template<class T>
void BorrarDeArray(Array<T> &arr, const nat pos, const nat tope)
{
	for(nat i = pos; i < tope; i++ )
	{
		arr[i] = arr[i + 1];
	}	
}

template <class V, class A>
Iterador<V> GrafoListaAdy<V, A>::Vertices() const
{
	return arrVertices.ObtenerIterador();
}

template <class V, class A>
Iterador<V> GrafoListaAdy<V, A>::Adyacentes(const V& v) const
{
	Puntero<Lista<NodoGrafo<V, A>>> adyacencias = GetListaAdyacencias(v);
	Array<V> ady(arrVertices.Largo - 1);
	int tope = -1;

	Iterador<NodoGrafo<V, A>> itNodos = adyacencias->ObtenerIterador();

	while (itNodos.HayElemento())
	{
		NodoGrafo<V, A> nodo = itNodos.ElementoActual();
		ady[++tope] = nodo.v2;
		itNodos.Avanzar();
	}

	Array<V> arrayAdyacentes(tope + 1);
	Array<V>::Copiar(ady, arrayAdyacentes);

	return arrayAdyacentes.ObtenerIterador();
}

template <class V, class A>
Iterador<V> GrafoListaAdy<V, A>::Incidentes(const V& v) const
{
	Puntero<Lista<V>> incidentes = new ListaEncadenada<V>(compVertice);

	for (nat i = 0 ; i < tope; i++)
	{
		if (compVertice.SonIguales(lGrafo[i].Dato1, v))
			continue;

		// Busco en la lista de este vertice si aparece v como destino
		Puntero<Lista<NodoGrafo<V, A>>> adyacentes = GetListaAdyacencias(i);

		Iterador<NodoGrafo<V, A>> iterador = adyacentes->ObtenerIterador();

		while(iterador.HayElemento())
		{
			NodoGrafo<V, A> nodo = iterador.ElementoActual();
			if (compVertice(v, nodo.v2))
				incidentes->Insertar(nodo);
			iterador.Avanzar();
		}
	}
}

template <class V, class A>
const A& GrafoListaAdy<V, A>::ObtenerArco(const V& v1, const V& v2) const
{
	Puntero<Lista<NodoGrafo<V, A>>> adyacentes = GetListaAdyacencias(v1);
	Iterador<NodoGrafo<V, A>> iterador = adyacentes->ObtenerIterador();
	A arco = A();
	while (iterador.HayElemento())
	{
		NodoGrafo<V, A> nodo = iterador.ElementoActual();
		if (compVertice(v2, nodo.v2))
		{
			arco = nodo.arista;
			break;
		}
	}
	return arco;
}
#endif
