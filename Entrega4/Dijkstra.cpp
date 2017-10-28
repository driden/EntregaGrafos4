#ifndef DIJKSTRA_CPP
#define DIJKSTRA_CPP
#include "Dijkstra.h"

template <class V, class Costo>
TablaAlgoritmo<V, Costo>::TablaAlgoritmo(const V& vengoDe, const Costo costoArco)
{
	vengo = vengoDe;
	costo = costoArco;
	conocido = false;
}

template <class V, class Costo>
TablaAlgoritmo<V, Costo>::TablaAlgoritmo()
{
	vengo = V();
	costo = Costo();
	conocido = false;
}

template <class V, class A, class Costo>
void Dijkstra<V, A, Costo>::InicializarTabla(V origen)
{
	tabla = Array<TablaAlgoritmo<V, Costo>>(grafo->CantidadVertices());
	Costo costo = Costo();
	const nat iVO = grafo->GetPosVertice(origen);
	tabla[iVO].conocido = true;
	tabla[iVO].costo = costo.Cero();
}


template <class V, class A, class Costo>
void Dijkstra<V, A, Costo>::AlgoritmoDijkstra(V origen)
{
	Puntero<ColaPrioridadExtendida<V, Costo>> pq = new CPBinaryHeap<V, Costo>(compVertice, compCosto, fHash);
	Costo costo = Costo();

	pq->InsertarConPrioridad(origen, costo.Cero());

	while (!pq->EstaVacia())
	{
		const V vActual = pq->ObtenerElementoMayorPrioridad();
		pq->EliminarElementoMayorPrioridad();

		nat posicion = grafo->GetPosVertice(vActual);
		tabla[posicion].conocido = true;

		Iterador<V> iterAdy = grafo->Adyacentes(vActual);

		while (iterAdy.HayElemento())
		{
			V w = iterAdy.ElementoActual();
			iterAdy.Avanzar();

			const nat posW = grafo->GetPosVertice(w);
			if (tabla[posW].conocido) continue;

			int actual = grafo->GetPosVertice(vActual);
			int ady = grafo->GetPosVertice(w);
			Costo costoEntrevertices = CalcularCosto(grafo, actual, ady);


			//Usar comparador
			if (compCosto.EsMayor(tabla[posW].costo, tabla[posicion].costo + costoEntrevertices))
			{
				tabla[posW].costo = tabla[posicion].costo + costoEntrevertices;
				tabla[posW].vengo = vActual;
			}

			pq->InsertarConPrioridad(w, costoEntrevertices);
		}
	}
}

template <class V, class A, class Costo>
Iterador<V> Dijkstra<V, A, Costo>::CaminoMasCorto(V origen, V destino)
{
	AlgoritmoDijkstra(origen);

	nat posDes = grafo->GetPosVertice(destino);

	assert(tabla[posDes].conocido);

	Array<V> caminoInvertido(grafo->CantidadVertices());
	caminoInvertido[0] = destino;
	int tope = 1;
	
	for(;tope<caminoInvertido.Largo -1; tope++)
	{
		V vVengo = tabla[tope].vengo;
		caminoInvertido[tope] = vVengo;
		if (compVertice.SonIguales(origen, vVengo)) break;
	}

	Array<V> caminoMasCorto(tope + 1);

	for (int i = 0; i < caminoMasCorto.Largo; i++)
		caminoMasCorto[i] = caminoInvertido[tope - i];
	return caminoInvertido.ObtenerIterador();
}



#endif
