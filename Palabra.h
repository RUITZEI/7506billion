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



public:
	string nombre;
	int apariciones;
	Palabra(string unString);
	IteradorMapa& getIteradorMapa();
	virtual ~Palabra();
	string getNombre();
	int getApariciones();
	Mapa& getPrecedencias();
	void incrementarApariciones();

	bool existePalabraEnPrecedencias(string unString);
	//Se le pasa directamente el string, no confundir con la clase Palabra.
	void agregarPrecedencia(string unString);

	//Imprime por consola las precedencias como si fuera un {} de python.
	void mostrarPrecedencias();



	/*
	 * Metodos para serializar - deserializar.
	 */

	//Devuelve un string con las precedencias y cant de apariciones en formato CSV
	string serializarPrecedencias();

	//Hay que pasarle el offset de la palabra en el archivo de precedencias.
	string serializarParaIndice(long offsetInicial, long bytesALeer);

	void agregarPrecedencia(const string& unString, int cantidadDeApariciones);

	Palabra(const string& unString, int cantidadDeApariciones);

	void eliminarPrecedencia(string unString);


};

#endif /* PALABRA_H_ */
