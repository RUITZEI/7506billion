/*
 * Palabra.cpp
 *
 *  Created on: Oct 31, 2014
 *      Author: manuel
 */

#include "Palabra.h"
#include <algorithm>

/*
 * PRIVADOS !!!
 */
IteradorMapa Palabra::getIteradorMapa(){
	return this->iterador;
}
/*
 * El metodo FIND de MAP garantiza que la busqueda sea log(N).
 */
bool Palabra::existePalabraEnPrecedencias(string unString){
	return (this->getPrecedencias().find(unString) != this->getPrecedencias().end());
}



/*
 * Publicos
 */
Palabra::Palabra(){
	//No deberia llamarse nunca.
}


/*
 * Apariciones en 0 porque se incrementa automaticamente al agregar
 * precedencias.
 */
Palabra::Palabra(string unNombre) {
	//Lowercase...
	transform(unNombre.begin(), unNombre.end(), unNombre.begin(), ::tolower);
	this->nombre = unNombre;
	this->apariciones = 0;
}

string Palabra::getNombre(){
	return this->nombre;
}

int Palabra::getApariciones(){
	return this->apariciones;
}

void Palabra::incrementarApariciones(){
	this->apariciones ++;
}

Mapa Palabra::getPrecedencias(){
	return (this->precedencias);
}


/*
 * El metodo chequea que exista o no en las precedencias.
 *
 * Al agregarle una nueva precedencia a la palabra asume que tiene
 * que haber aparecido en el texto, por lo que le aumento el contador
 * a la propia palabra.
 */
void Palabra::agregarPrecedencia(string unString){
	this->incrementarApariciones();

	//Precedencia en lower case
	transform(unString.begin(), unString.end(), unString.begin(), ::tolower);

	if (this->existePalabraEnPrecedencias(unString)){
		this->precedencias[unString] ++;
	} else {
		this->precedencias[unString] = 1;
	}
}

void Palabra::mostrarPrecedencias(){
	IteradorMapa it = this->getIteradorMapa();
	std::cout << this->nombre <<" = ";
	for (it = this->precedencias.begin(); it!=this->precedencias.end(); ++it)
			std::cout << "{" << it->first << " : " << it->second <<"}"<< "  ";
	std::cout << "\n";
}

Palabra::~Palabra() {

}

