#ifndef SISTEMA_CPP
#define SISTEMA_CPP
#include "ComparacionParadas.h"
#include "Sistema.h"
#include "GrafoListaAdy.h"
#include "CadenaHash.h"
#include "ComparacionTiempo.h"
#include "ComparacionCiudades.h"
#include "ComparacionCostoMasBarato.h"
#include "Funciones.h"
#include "ComparacionOmnibus.h"
#include "ComparacionAviones.h"
#include "ComparacionBaratoOmnibus.h"

Sistema::Sistema(nat MAX_CIUDADES)
{
	max_ciudades = MAX_CIUDADES;
	fHashCadena = new CadenaHash();
	//Puntero<Grafo<Cadena, Tupla<TipoTransporte, nat, nat, nat>>> 
	grafo = new GrafoListaAdy<Cadena, Tupla<TipoTransporte, nat, nat, nat>>(max_ciudades, fHashCadena, Comparador<Cadena>::Default);
}
Sistema::~Sistema()
{
}
TipoRetorno Sistema::AltaCiudad(const Cadena &ciudadNombre)
{
	if (grafo->ExisteVertice(ciudadNombre))
		return ERROR;
	grafo->AgregarVertice(ciudadNombre);
	return OK;
}
TipoRetorno Sistema::AltaConexion(const Cadena &ciudadOrigen, const Cadena &ciudadDestino, const TipoTransporte &tipo, const nat &costo, const nat &tiempo, const nat &nroParadas)
{
	if (!grafo->ExisteVertice(ciudadOrigen)) return ERROR;
	if (!grafo->ExisteVertice(ciudadDestino)) return ERROR;
	if (costo == 0) return ERROR;
	if (tiempo == 0) return ERROR;

	grafo->AgregarArco(ciudadOrigen, ciudadDestino, Tupla<TipoTransporte, nat, nat, nat>(tipo, costo,tiempo, nroParadas));
	return OK;
}

CostoArco CalcularCostoArco(Puntero<Grafo<Cadena, Tupla<TipoTransporte, nat, nat, nat>>> grafo, int vO, int vD)
{
	Cadena origen = grafo->GetVertice(vO);
	Cadena destino = grafo->GetVertice(vD);
	Tupla<TipoTransporte, nat, nat, nat> arco = grafo->ObtenerArco(origen, destino);
	int aviones = arco.Dato1 == AVION ? 1 : 0;
	int bus = aviones == 0 ? 1 : 0;
	return CostoArco(aviones, bus, arco.Dato2, arco.Dato3, arco.Dato4,1);
}

Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMasBarato(const Cadena &ciudadOrigen, const Cadena &ciudadDestino)
{
	if (!grafo->ExisteVertice(ciudadOrigen)) return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR,nullptr);
	if (!grafo->ExisteVertice(ciudadDestino)) return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR,nullptr);
	if (!grafo->HayCamino(ciudadOrigen,ciudadDestino)) return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);

	Puntero<Comparacion<CostoArco>> comparacion = new ComparacionCostoMasBarato();
	Comparador<CostoArco> comparador(comparacion);
	
	Dijkstra<Cadena, Tupla<TipoTransporte, nat, nat, nat>, CostoArco>
		dijkstra(
			grafo, 
			comparador, Comparador<Cadena>::Default, fHashCadena, &CalcularCostoArco);
	
	return Tupla<TipoRetorno, Iterador<Cadena>>(OK, dijkstra.CaminoMasCorto(ciudadOrigen,ciudadDestino));
}
Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMenorTiempo(const Cadena &ciudadOrigen, const Cadena &ciudadDestino)
{
	if (!grafo->ExisteVertice(ciudadOrigen)) return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	if (!grafo->ExisteVertice(ciudadDestino)) return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	if (!grafo->HayCamino(ciudadOrigen, ciudadDestino)) return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);

	Puntero<Comparacion<CostoArco>> comparacion = new ComparacionTiempo();
	Comparador<CostoArco> comparador(comparacion);

	Dijkstra<Cadena, Tupla<TipoTransporte, nat, nat, nat>, CostoArco>
		dijkstra(
			grafo,
			comparador, Comparador<Cadena>::Default, fHashCadena, &CalcularCostoArco);

	return Tupla<TipoRetorno, Iterador<Cadena>>(OK, dijkstra.CaminoMasCorto(ciudadOrigen, ciudadDestino));
}
Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMenosCiudades(const Cadena &ciudadOrigen, const Cadena &ciudadDestino)
{
	if (!grafo->ExisteVertice(ciudadOrigen)) return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	if (!grafo->ExisteVertice(ciudadDestino)) return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	if (!grafo->HayCamino(ciudadOrigen, ciudadDestino)) return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);

	Puntero<Comparacion<CostoArco>> comparacion = new ComparacionCiudades();
	Comparador<CostoArco> comparador(comparacion);

	Dijkstra<Cadena, Tupla<TipoTransporte, nat, nat, nat>, CostoArco>
		dijkstra(
			grafo,
			comparador, Comparador<Cadena>::Default, fHashCadena, &CalcularCostoArco);

	return Tupla<TipoRetorno, Iterador<Cadena>>(OK, dijkstra.CaminoMasCorto(ciudadOrigen, ciudadDestino));
}
Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMenosTrayectosOmnibus(const Cadena &ciudadOrigen, const Cadena &ciudadDestino)
{
	if (!grafo->ExisteVertice(ciudadOrigen)) return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	if (!grafo->ExisteVertice(ciudadDestino)) return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	if (!grafo->HayCamino(ciudadOrigen, ciudadDestino)) return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);

	Puntero<Comparacion<CostoArco>> comparacion = new ComparacionOmnibus();
	Comparador<CostoArco> comparador(comparacion);

	Dijkstra<Cadena, Tupla<TipoTransporte, nat, nat, nat>, CostoArco>
		dijkstra(
			grafo,
			comparador, Comparador<Cadena>::Default, fHashCadena, &CalcularCostoArco);

	return Tupla<TipoRetorno, Iterador<Cadena>>(OK, dijkstra.CaminoMasCorto(ciudadOrigen, ciudadDestino));
}
Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMenosTrayectosAvion(const Cadena &ciudadOrigen, const Cadena &ciudadDestino)
{
	if (!grafo->ExisteVertice(ciudadOrigen)) return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	if (!grafo->ExisteVertice(ciudadDestino)) return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	if (!grafo->HayCamino(ciudadOrigen, ciudadDestino)) return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);

	Puntero<Comparacion<CostoArco>> comparacion = new ComparacionAviones();
	Comparador<CostoArco> comparador(comparacion);

	Dijkstra<Cadena, Tupla<TipoTransporte, nat, nat, nat>, CostoArco>
		dijkstra(
			grafo,
			comparador, Comparador<Cadena>::Default, fHashCadena, &CalcularCostoArco);

	return Tupla<TipoRetorno, Iterador<Cadena>>(OK, dijkstra.CaminoMasCorto(ciudadOrigen, ciudadDestino));
}
Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMenosParadasIntermedias(const Cadena &ciudadOrigen, const Cadena &ciudadDestino)
{
	if (!grafo->ExisteVertice(ciudadOrigen)) return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	if (!grafo->ExisteVertice(ciudadDestino)) return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	if (!grafo->HayCamino(ciudadOrigen, ciudadDestino)) return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);

	Puntero<Comparacion<CostoArco>> comparacion = new ComparacionParadas();
	Comparador<CostoArco> comparador(comparacion);

	Dijkstra<Cadena, Tupla<TipoTransporte, nat, nat, nat>, CostoArco>
		dijkstra(
			grafo,
			comparador, Comparador<Cadena>::Default, fHashCadena, &CalcularCostoArco);

	return Tupla<TipoRetorno, Iterador<Cadena>>(OK, dijkstra.CaminoMasCorto(ciudadOrigen, ciudadDestino));
}
Tupla<TipoRetorno, Iterador<Cadena>> Sistema::CaminoMasBaratoOminbus(const Cadena &ciudadOrigen, const Cadena &ciudadDestino)
{
	if (!grafo->ExisteVertice(ciudadOrigen)) return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	if (!grafo->ExisteVertice(ciudadDestino)) return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);
	if (!grafo->HayCamino(ciudadOrigen, ciudadDestino)) return Tupla<TipoRetorno, Iterador<Cadena>>(ERROR, nullptr);

	Puntero<Comparacion<CostoArco>> comparacion = new ComparacionBaratoOmnibus();
	Comparador<CostoArco> comparador(comparacion);

	Dijkstra<Cadena, Tupla<TipoTransporte, nat, nat, nat>, CostoArco>
		dijkstra(
			grafo,
			comparador, Comparador<Cadena>::Default, fHashCadena, &CalcularCostoArco);

	return Tupla<TipoRetorno, Iterador<Cadena>>(OK, dijkstra.CaminoMasCorto(ciudadOrigen, ciudadDestino));
}
#endif