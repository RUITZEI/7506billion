/*
 * ContenedorDePalabras.cpp
 *
 *  Created on: Nov 2, 2014
 *      Author: manuel
 */

#include "ContenedorDePalabras.h"
using namespace std;


ContenedorDePalabras::ContenedorDePalabras() {
	// TODO Auto-generated constructor stub
}

bool ContenedorDePalabras::existePalabra(string unString){
	transform(unString.begin(), unString.end(), unString.begin(), ::tolower);
	return (this->lista.find(unString) != this->lista.end());
}

void ContenedorDePalabras::agregarPalabra(Palabra *unaPalabra){
	this->lista[unaPalabra->getNombre()] = unaPalabra;
}

Palabra* ContenedorDePalabras::getPalabra(string unString){
	transform(unString.begin(), unString.end(), unString.begin(), ::tolower);
	//return this->lista[unString];
	return this->lista.at(unString);
}

ContenedorDePalabras::~ContenedorDePalabras() {
	// TODO Auto-generated destructor stub
}

//Elimina una palabra de la lista. NO CHEQUEA QUE EXISTA.
void ContenedorDePalabras::eliminarPalabra(string unString){
	this->lista.erase(unString);
}

void ContenedorDePalabras::eliminarPrecedencia(string unString){
	typedef boost::unordered_map<string, Palabra*>::const_iterator IteradorContenedor;

	for(IteradorContenedor it = this->lista.begin(); it != this->lista.end(); it++){
		it->second->eliminarPrecedencia(unString);
	}

}

