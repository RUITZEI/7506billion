/*
 * Palabra.h
 *
 *  Created on: Oct 31, 2014
 *      Author: manuel
 *
 *  Una Palabra es un objeto que consta de los siguientes atributos:
 *    + Nombre: El string que la representa propiamente como palabra.
 *    + Apariciones : Cantidad de apariciones que tuvo en el texto.
 *    + Precedencias: Sera implementado como un MAP<string,int> y
 *    contendra "La lista de precedencias"
 *
 */

#include <stdio.h>
#include <iostream>
#include <map>
#include <string.h>
#include <utility>
#include <boost/unordered_map.hpp>

using namespace std;

typedef boost::unordered_map<string, int> Mapa;
typedef boost::unordered_map<string, int>::const_iterator IteradorMapa;


#ifndef PALABRA_H_
#define PALABRA_H_

class Palabra {

private:
	Mapa precedencias;
	IteradorMapa iterador;
	IteradorMapa getIteradorMapa();
	bool existePalabraEnPrecedencias(string unString);

public:
	string nombre;
	int apariciones;
	Palabra(string unString);
	virtual ~Palabra();
	string getNombre();
	int getApariciones();
	Mapa& getPrecedencias();
	void incrementarApariciones();
	//Se le pasa directamente el string, no confundir con la clase Palabra.
	void agregarPrecedencia(string unString);

	//Imprime por consola las precedencias como si fuera un {} de python.
	void mostrarPrecedencias();


};

#endif /* PALABRA_H_ */
