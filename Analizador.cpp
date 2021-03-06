/*
 * Analizador.cpp
 *
 *  Created on: 24/11/2014
 *      Author: caito
 */

#include "Analizador.h"
#include <ctime>

Analizador::Analizador(ContenedorDePalabras* diccionario) {
	// TODO Auto-generated constructor stub
	this->diccionario = diccionario;
}

Analizador::~Analizador() {
	// TODO Auto-generated destructor stub
}

/*
 * Abre el archivo y lo recorre linea a linea analizando sus oraciones
 */
void Analizador::analizar(string nombreArchEntrada, string nombreArchSalida)
{
	string linea;
	ifstream myfile (nombreArchEntrada.c_str());
	ofstream salida;
	int cont = 0;
	int cont_lineas = 1;
	if (myfile.is_open())
	{
		salida.open(nombreArchSalida.c_str());
		salida << "id,\"sentence\"\n";
		while ( getline (myfile,linea) )
		{
			if (cont > 0) //La primera linea tiene la cabecera y no se procesa
			{
				salida << cont_lineas << ",\"" << analizarOracion(linea) << "\"\n";
				cont_lineas++;
				cout << cont_lineas << endl;
			}
			else cont++;
		}
		myfile.close();
		salida.close();
	}
	else cout << "No se pudo abrir el archivo.";
}

/*
 * Obtener cada palabra, con su precedencia, en una oracion, y buscar si esa precedencia tiene sentido
 */
string Analizador::analizarOracion(const string& linea)
{
	string salida = "";

	string precedenciaActual = "endl";
	double probabilidadAux = 1;
	Palabra* palabraAux;
	string precedenciaAux = "";
	bool faltaPalabra = false;
	int posCandidata;
	size_t pos1, pos2;

	pos1 = linea.find_first_of('"');
	pos2 = linea.find_last_of('"');
	string oracion(linea, pos1+1, (pos2-pos1)-1);

	//Obtengo las palabras de la oracion
	split_vector_type palabrasDeOraciones;
	boost::split(palabrasDeOraciones, oracion, boost::is_any_of(" "), boost::token_compress_on);
	int contadorPalabras = 0;
	int contadorPalabrasNoEncontradas = 0;
	//TODO: Necesito que se agregue los endl al contenedor de palabras con sus precedencias, para poder resolver los casos que
	//la palabra que falte sea la ultima
	palabrasDeOraciones.push_back("endl");

	std::clock_t start;
	double duration;

	start = std::clock();

	for (vector<string>::iterator palabra = palabrasDeOraciones.begin(); ((palabra != palabrasDeOraciones.end()) && !faltaPalabra); ++palabra)
	{
		if (*palabra == "endl")
			contadorPalabrasNoEncontradas--;

		//Si la palabra esta definida en el diccionario, busco cuales son sus precedencias
		if (diccionario->existePalabra(*palabra))
		{
			Palabra* palabraActual = diccionario->getPalabra(*palabra);
			double probabilidadActual = analizarPrecedencias(palabraActual, precedenciaActual);
			//Si no encuento entre las precedencias de la palabraActual a precedenciaActual => probabilidadActual = 0
			if (probabilidadActual > 0)
			{
				//Si la encuentro, guardo cual es su probabilidad (para proteger el caso que no se detecte que falten palabras)
				if (probabilidadActual <= probabilidadAux)
				{
					probabilidadAux = probabilidadActual;
					palabraAux = palabraActual;
					precedenciaAux = precedenciaActual;
					posCandidata = contadorPalabras;
				}
			}
			else
			{
				//Si no la encuentro, recorro las precedencias de la palabra actual, y por cada una de ellas veo si entre sus
				//precedencias encuentro a precedencia actual
				faltaPalabra = true;
				duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
				cout<<"encuentro hueco:  " <<  duration <<'\n';

				string oracionSalida = obtenerOracion(palabraActual, precedenciaActual, palabrasDeOraciones, contadorPalabras + contadorPalabrasNoEncontradas);
				salida = oracionSalida;
			}

			precedenciaActual = *palabra;
			contadorPalabras++;
		}
		else contadorPalabrasNoEncontradas++;
	}

	if (!faltaPalabra)
	{
		duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
		cout<<"no encuentro hueco:  " <<  duration <<'\n';
		string oracionSalida = obtenerOracion(palabraAux, precedenciaAux, palabrasDeOraciones, posCandidata + contadorPalabrasNoEncontradas);
		salida = oracionSalida;
	}

	return salida;
}

string Analizador::obtenerOracion(Palabra* palabraActual, const string& precedenciaActual, split_vector_type& palabrasDeOraciones, int pos)
{
	string salida = "";

	double probabilidadCandidata = 0;
	string palabraCandidata = "";
	int posCandidata = pos;
	double probabilidadCandidataError = 0;
	string palabraCandidataError = "";
	bool faltaCandidata = true;

	std::clock_t start;
	double duration;

	start = std::clock();

	/*if (precedencias.size() > 20)
		precedencias = palabraActual->getPrecedencias(50);*/
	for (IteradorMapa precedencia = palabraActual->getPrecedencias().begin(); precedencia != palabraActual->getPrecedencias().end(); ++precedencia)
	{
		if (precedencia->first != "endl")
		{
			//Esta es la probabilidad que esta palabra candidata pase como precedencia de palabraActual
			int aparicionesDePrecedencia = 0;
			if (this->diccionario->existePalabra(precedencia->first)) aparicionesDePrecedencia = this->diccionario->getPalabra(precedencia->first)->getApariciones();
			double probabilidadActual = ( (precedencia->second + 1) / (double) (aparicionesDePrecedencia + CANTIDAD_DE_PALABRAS) );

			if (diccionario->existePalabra(precedencia->first))
			{
				Palabra* precedenciaCandidata = diccionario->getPalabra(precedencia->first);


				double probabilidadPrec = analizarPrecedencias(precedenciaCandidata, precedenciaActual);
				//Si no encuento entre las precedencias de la candidata a precedenciaActual => probabilidadPrec = 0
				if (probabilidadPrec > 0)
				{
					//Si la encuentro, multiplico las dos probas y me voy quedando con la candidata de > proba
					faltaCandidata = false;
					if ((probabilidadActual * probabilidadPrec) >= probabilidadCandidata)
					{
						probabilidadCandidata = probabilidadActual * probabilidadPrec;
						palabraCandidata = precedencia->first;
					}
				}
				else
				{
					//Si no la encuentro, me quedo en otra variable con la candidata de > probabilidadActual (para proteger
					//el caso que no encontremos ninguna candidata a llenar la palabra que falta)
					if (probabilidadActual >= probabilidadCandidataError)
					{
						probabilidadCandidataError = probabilidadActual;
						palabraCandidataError = precedencia->first;
					}
				}
			}
		}
	}

	if (!faltaCandidata)
		salida = armarOracion(palabrasDeOraciones, palabraCandidata, posCandidata);
	else
		salida = armarOracion(palabrasDeOraciones, palabraCandidataError, posCandidata);

	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	cout<<"Tiempo total de ejecucion: " <<  duration <<'\n';

	return salida;
}


/*
 *
 */
double Analizador::analizarPrecedencias(Palabra* palabra, string precedencia)
{
	//Mapa& precedencias = palabra->getPrecedencias();
	/*if (precedencias.size() > 20)
		precedencias = palabra->getPrecedencias(50);*/

	boost::to_lower(precedencia);
	/*Mapa::iterator itPrecedencia = precedencias.find(precedencia);
	if (itPrecedencia != precedencias.end())
		return itPrecedencia->second / (double)palabra->getApariciones();
	else return 0;*/

	int aparicionesDePrecedencia = 0;
	boost::to_lower(precedencia);
	if (palabra->existePalabraEnPrecedencias(precedencia)){
		if (this->diccionario->existePalabra(precedencia)) aparicionesDePrecedencia = this->diccionario->getPalabra(precedencia)->getApariciones();

		return ( (palabra->getPrecedencias()[precedencia] + 1) / (double) (aparicionesDePrecedencia + CANTIDAD_DE_PALABRAS) );
	}
	else return ( 1 / (double) (aparicionesDePrecedencia + CANTIDAD_DE_PALABRAS) );
}

string Analizador::armarOracion(split_vector_type& palabras, const string& palabraInsertar, int posInsertar)
{
	string salida = "";
	int contadorPalabras = 0;

	for (vector<string>::iterator palabra = palabras.begin(); (palabra != palabras.end()); ++palabra)
	{
		if (contadorPalabras == posInsertar)
		{
			if (contadorPalabras > 0)
				salida.append(" ");
			salida.append(palabraInsertar);
			if (*palabra != "endl")
			{
				salida.append(" ");
				salida.append(*palabra);
			}
		}
		else
		{
			if (*palabra != "endl")
			{
				if (contadorPalabras > 0)
					salida.append(" ");
				salida.append(*palabra);
			}
		}
		contadorPalabras++;
	}

	return salida;
}
