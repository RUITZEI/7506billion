/*
 * Analizador.cpp
 *
 *  Created on: 24/11/2014
 *      Author: caito
 */

#include "Analizador.h"

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
void Analizador::analizar(string nombreArch)
{
	string linea;
	ifstream myfile (nombreArch.c_str());
	if (myfile.is_open())
	{
		while ( getline (myfile,linea) )
		{
			analizarOracion(linea);
		}
		myfile.close();
	}
	else cout << "No se pudo abrir el archivo.";
}

/*
 * Obtener cada palabra, con su precedencia, en una oracion, y buscar si esa precedencia tiene sentido
 */
void Analizador::analizarOracion(string oracion)
{
	string precedenciaActual = "endl";
	double probabilidadAux = 1;
	Palabra* palabraAux;
	string precedenciaAux = "";
	bool faltaPalabra = false;
	int posCandidata;

	//Obtengo las palabras de la oracion
	split_vector_type palabrasDeOraciones;
	boost::split(palabrasDeOraciones, oracion, boost::is_any_of(" -!?\"\n\t,."), boost::token_compress_on);
	int contadorPalabras = 0;
	//TODO: Necesito que se agregue los endl al contenedor de palabras con sus precedencias, para poder resolver los casos que
	//la palabra que falte sea la ultima
	palabrasDeOraciones.push_back("endl");

	for (vector<string>::iterator palabra = palabrasDeOraciones.begin(); ((palabra != palabrasDeOraciones.end()) && !faltaPalabra); ++palabra)
	{
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
				string oracionSalida = obtenerOracion(palabraActual, precedenciaActual, palabrasDeOraciones, contadorPalabras);
				cout << endl << endl << "ORACION ORIGINAL:" << oracion << endl << "ORACION SALIDA:" << oracionSalida << endl;
			}

			precedenciaActual = *palabra;
			contadorPalabras++;
		}
	}

	if (!faltaPalabra)
	{
		string oracionSalida = obtenerOracion(palabraAux, precedenciaAux, palabrasDeOraciones, posCandidata);
		cout << endl << endl << "ORACION ORIGINAL:" << oracion << endl << "ORACION SALIDA:" << oracionSalida << endl;
	}
}

string Analizador::obtenerOracion(Palabra* palabraActual, string precedenciaActual, split_vector_type palabrasDeOraciones, int pos)
{
	string salida = "";

	double probabilidadCandidata = 0;
	string palabraCandidata = "";
	int posCandidata = pos;
	double probabilidadCandidataError = 0;
	string palabraCandidataError = "";
	bool faltaCandidata = true;

	Mapa precedencias = palabraActual->getPrecedencias();
	for (Mapa::iterator precedencia = precedencias.begin(); precedencia != precedencias.end(); ++precedencia)
	{
		if ((*precedencia).first != "endl")
		{
			//Esta es la probabilidad que esta palabra candidata pase como precedencia de palabraActual
			double probabilidadActual = (*precedencia).second / (double)palabraActual->getApariciones();

			if (diccionario->existePalabra((*precedencia).first))
			{
				Palabra* precedenciaCandidata = diccionario->getPalabra((*precedencia).first);
				double probabilidadPrec = analizarPrecedencias(precedenciaCandidata, precedenciaActual);
				//Si no encuento entre las precedencias de la candidata a precedenciaActual => probabilidadPrec = 0
				if (probabilidadPrec > 0)
				{
					//Si la encuentro, multiplico las dos probas y me voy quedando con la candidata de > proba
					faltaCandidata = false;
					if ((probabilidadActual * probabilidadPrec) >= probabilidadCandidata)
					{
						probabilidadCandidata = probabilidadActual * probabilidadPrec;
						palabraCandidata = (*precedencia).first;
					}
				}
				else
				{
					//Si no la encuentro, me quedo en otra variable con la candidata de > probabilidadActual (para proteger
					//el caso que no encontremos ninguna candidata a llenar la palabra que falta)
					if (probabilidadActual >= probabilidadCandidataError)
					{
						probabilidadCandidataError = probabilidadActual;
						palabraCandidataError = (*precedencia).first;
					}
				}
			}
		}
	}

	if (!faltaCandidata)
		salida = armarOracion(palabrasDeOraciones, palabraCandidata, posCandidata);
	else
		salida = armarOracion(palabrasDeOraciones, palabraCandidataError, posCandidata);

	return salida;
}


/*
 *
 */
double Analizador::analizarPrecedencias(Palabra* palabra, string precedencia)
{
	Mapa precedencias = palabra->getPrecedencias();

	boost::to_lower(precedencia);
	Mapa::iterator itPrecedencia = precedencias.find(precedencia);
	if (itPrecedencia != precedencias.end())
		return itPrecedencia->second / (double)palabra->getApariciones();
	else return 0;
}

string Analizador::armarOracion(split_vector_type palabras, string palabraInsertar, int posInsertar)
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
