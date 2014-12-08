/*
 * ContenedorDePalabras.h
 *
 *  Created on: Nov 2, 2014
 *      Author: manuel
 */

#include "Palabra.h"
#include <algorithm>
#include <boost/unordered_map.hpp>


using namespace std;

//Map -> Busqueda log N
typedef boost::unordered_map<string, Palabra*> Lista;


#ifndef CONTENEDORDEPALABRAS_H_
#define CONTENEDORDEPALABRAS_H_

class ContenedorDePalabras {

private:
	/*
	 * Podria ser cualquier otro tipo de estructura, el fin de esta clase es crear
	 * una interfaz unica que no dependa de la implementacion. (se modificarian
	 * la implementacion pero no la interfaz de esta clase)
	 */
	Lista lista;

public:
	ContenedorDePalabras();
	virtual ~ContenedorDePalabras();
	void agregarPalabra(Palabra* unaPalabra);
	bool existePalabra(string unString);
	Palabra* getPalabra(string unString);
	void eliminarPalabra(string unString);
	void eliminarPrecedencia(string unString);
	Lista& getListaDePalabras();

};

#endif /* CONTENEDORDEPALABRAS_H_ */
