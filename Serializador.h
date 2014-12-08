/*
 * Serializador.h
 *
 *  Created on: Dec 7, 2014
 *      Author: manuel
 */

#include "ContenedorDePalabras.h"
#include <iostream>
#include <fstream>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <vector>
#include <boost/lexical_cast.hpp>

using namespace std;

#ifndef SERIALIZADOR_H_
#define SERIALIZADOR_H_

class Serializador {

private:
	ContenedorDePalabras* diccionario;

public:
	Serializador(ContenedorDePalabras *unDiccionario);
	void serializar();
	void deserializar();
	virtual ~Serializador();
};

#endif /* SERIALIZADOR_H_ */
