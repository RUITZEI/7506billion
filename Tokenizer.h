/*
 * Tokenizer.h
 *
 *  Created on: Nov 16, 2014
 *      Author: manuel
 */

#include "ContenedorDePalabras.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <vector>

#ifndef TOKENIZER_H_
#define TOKENIZER_H_

class Tokenizer {
public:
	Tokenizer();
	virtual ~Tokenizer();

	/*
	 * Recibe el string a tokenizar y el contenedor de palabras.
	 * Deja en el contenedor de palabras la estructura ya armada con las precedencias
	 * de cada palabra.
	 */
	static void tokenize(ContenedorDePalabras *unContenedor, const string &unString);
};


#endif /* TOKENIZER_H_ */
