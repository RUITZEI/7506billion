/*
 * LectorDeArrchivo.h
 *
 *  Created on: Nov 1, 2014
 *      Author: manuel
 *
 *      Esta deberia ser una Clase Abstracta, creo que no existen en c++
 *
 *      No instanciar esta clase.
 */

using namespace std;
#include <fstream>
#include <iostream>
#include <string>
#include <cerrno>

#ifndef LECTORDEARCHIVO_H_
#define LECTORDEARCHIVO_H_

class LectorDeArchivo {

private:
	const char* archivo;
public:
	LectorDeArchivo();
	static string leerArchivo(const char *filename);
	virtual ~LectorDeArchivo();
};

#endif /* LECTORDEARCHIVO_H_ */
