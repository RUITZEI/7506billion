/*
 * Serializador.cpp
 *
 *  Created on: Dec 7, 2014
 *      Author: manuel
 */

#include "Serializador.h"



Serializador::Serializador(ContenedorDePalabras *unDiccionario) {
	this->diccionario = unDiccionario;
}


void Serializador::serializar(){
	/*
	 * Iterador del contenedor
	 */
	typedef boost::unordered_map<string, Palabra*>::const_iterator IteradorContenedor;

	ofstream archPrecedencias;
	ofstream archIndice;

	archPrecedencias.open("precedencias.txt");
	archIndice.open("indice.txt");

	long offsetActual = 0;

	for(IteradorContenedor it = this->diccionario->getListaDePalabras().begin(); it != this->diccionario->getListaDePalabras().end(); ++it){
		//Escribo la salida de las precedencias sin el endl porque es uno atras del otro(stream de datos).
		string salidaPrecedencias = it->second->serializarPrecedencias();

		//Si la salida de las precedencias es menor a 0, lo descarto porque ninguna de sus precedencias
		//aparecio mas de 100 veces.
		if (salidaPrecedencias.length() > 0){
			archPrecedencias << salidaPrecedencias;

			//Escribo la salida del indice con un endl al final porque es 1 palabra por linea.
			long bytesAleer = salidaPrecedencias.length();
			string salidaIndice = it->second->serializarParaIndice(offsetActual, bytesAleer);
			archIndice << salidaIndice << endl;

			offsetActual += bytesAleer;
		}
	}

	archIndice.close();
	archPrecedencias.close();
}

void Serializador::deserializar(){
	typedef vector< string > split_vector_type;

	ifstream archIndice;
	ifstream archPrecedencias;

	archIndice.open("indice.txt");
	archPrecedencias.open("precedencias.txt");

	string line;
	split_vector_type valoresLinea;


	while (getline(archIndice, line)){
		//cout << line << endl;
		boost::split(valoresLinea, line, boost::is_any_of(","), boost::token_compress_on);
		/*
		 * [0] = nombre de la palabra
		 * [1] = cantidad de apariciones
		 * [2] = offset en archivo de precedencias
		 * [3] = bytes a leer
		 */
		Palabra *palabraPorAgregar = new Palabra(valoresLinea[0], boost::lexical_cast<int>(valoresLinea[1]));
		long offsetActual = boost::lexical_cast<long>(valoresLinea[2]);
		int bytesPorLeer = boost::lexical_cast<int>(valoresLinea[3]);

		if (bytesPorLeer == 0) break; //para que el Valgrind no joda.

		//Leo todo lo que necesito del archivo de precedencias.
		char* linePrecedencias = new char [(sizeof(char*) * bytesPorLeer)];
		archPrecedencias.seekg(offsetActual, ios::beg);
		archPrecedencias.read(linePrecedencias, bytesPorLeer);

		linePrecedencias[bytesPorLeer] = 0;

		split_vector_type valoresPrecedencias;
		boost::split(valoresPrecedencias, linePrecedencias, boost::is_any_of(","), boost::token_compress_off);

		size_t i = 0;
		//cout << valoresPrecedencias.size()<< endl;
		while (i < valoresPrecedencias.size()){
			/*
			 *  Voy agregando las precedencias a palabraPorAgregar para finalmente agregarlas al diccionario.
			 *  [i] = Nombre de la palabra
			 *  [i+1] = Cantidad de Apariciones
			 */
			//cout << valoresPrecedencias[i] << "    " << valoresPrecedencias[i+1]<<endl;
			palabraPorAgregar->agregarPrecedencia(valoresPrecedencias[i], boost::lexical_cast<int>(valoresPrecedencias[i+1]));
			i += 2;
		}
		diccionario->agregarPalabra(palabraPorAgregar);
		free (linePrecedencias);
	}

	archIndice.close();
	archPrecedencias.close();
}


Serializador::~Serializador() {
	// TODO Auto-generated destructor stub
}

