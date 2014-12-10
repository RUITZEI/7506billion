/*
 * Analizador.h
 *
 *  Created on: 24/11/2014
 *      Author: caito
 */

#include "ContenedorDePalabras.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <string.h>
#include <utility>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>

using namespace std;

typedef vector< string > split_vector_type;
typedef boost::unordered_map<string, int> Mapa;

const int CANTIDAD_DE_PALABRAS = 151153;

#ifndef ANALIZADOR_H_
#define ANALIZADOR_H_

class Analizador {
private:
	ContenedorDePalabras* diccionario;

	string analizarOracion(const string& linea);
	double analizarPrecedencias(Palabra* palabra, string precedencia);
	string armarOracion(split_vector_type& palabras, const string& palabraInsertar, int posInsertar);
	string obtenerOracion(Palabra* palabraActual, const string& precedenciaActual, split_vector_type& palabrasDeOraciones, int pos);
public:
	Analizador(ContenedorDePalabras* diccionario);
	virtual ~Analizador();

	void analizar(string nombreArchEntrada, string nombreArchSalida);
};

#endif /* ANALIZADOR_H_ */
