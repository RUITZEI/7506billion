/*
 * Palabra.cpp
 *
 *  Created on: Oct 31, 2014
 *      Author: manuel
 */

#include "Palabra.h"
#include <algorithm>
#include <boost/lexical_cast.hpp>

/*
 * PRIVADOS !!!
 */
IteradorMapa& Palabra::getIteradorMapa(){
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

Mapa& Palabra::getPrecedencias(){
	return (this->precedencias);
}


/*
 * El metodo chequea que exista o no en las precedencias.
 *
 * Al agregarle una nueva precedencia a la palabra asume que tiene
 * que haber aparecido en el texto, por lo que le aumento el contador
 * a la propia palabra.
 * Chequear que tenga length 1 al menos para evitar que se agregue algun espacio.
 */
void Palabra::agregarPrecedencia(string unString){
	if (unString.length() > 0){
		this->incrementarApariciones();

		//Precedencia en lower case
		transform(unString.begin(), unString.end(), unString.begin(), ::tolower);

		if (this->existePalabraEnPrecedencias(unString)){
			this->precedencias[unString] ++;
		} else {
			this->precedencias[unString] = 1;
		}
	}
}

void Palabra::mostrarPrecedencias(){
	IteradorMapa it = this->getIteradorMapa();
	std::cout << this->nombre <<"["<< this->getApariciones()<<" apariciones] = ";
	for (it = this->precedencias.begin(); it!=this->precedencias.end(); ++it)
			std::cout << "{" << it->first << " : " << it->second <<"}"<< "  ";
	std::cout << "\n";
}

std::size_t hash_value(Palabra const& p)
{
  std::size_t seed = 0;
  boost::hash_combine(seed, p.nombre);
  boost::hash_combine(seed, p.apariciones);
  return seed;
}

bool operator==(const Palabra &p, const Palabra &p1)
{
  return p.nombre == p1.nombre;
}

void Palabra::eliminarPrecedencia(string unString){
	if (this -> existePalabraEnPrecedencias(unString)){
		this->apariciones -= this->precedencias[unString];
		this->getPrecedencias().erase(unString);

	}
}

string Palabra::serializarPrecedencias(){
	IteradorMapa it = this->getIteradorMapa();
	string output = "";

	for (it = this->precedencias.begin(); it!=this->precedencias.end(); ++it){
		//Si tiene menos de 100 apariciones no lo agrego en las precedencias
		if (it->second > 100){
			output.append(it->first);
			output.append(",");
			output.append(boost::lexical_cast<std::string>(it->second));
			output.append(",");
		}else {
			//Y le bajo la cantidad de apariciones
			this->apariciones -= it->second;
		}
	}

	if (output.length() < 1) return "";

	//Elimino la ultima coma.
	output = output.substr(0,output.length()-1);

	return output;
}

//Crea el string para introducir una linea en el archivo del indice. Falta agregarle el offset del archivo.
string Palabra::serializarParaIndice(long offsetInicial, long bytesALeer){
	string output = "";
	output.append(this->nombre);
	output.append(",");
	output.append(boost::lexical_cast<std::string>(this->apariciones));
	output.append(",");
	output.append(boost::lexical_cast<std::string>(offsetInicial));
	output.append(",");
	output.append(boost::lexical_cast<std::string>(bytesALeer));

	return output;
}

/*
 * No realizo chequeos porque ya se que la palabra viene en minuscula y que no existe de antes.
 * Tampoco incremento la cantidad de apariciones de la palabra pues ya la levanto del indicie.
 */
void Palabra::agregarPrecedencia(const string& unString, int cantidadDeApariciones){
	this->precedencias[unString] = cantidadDeApariciones;
}

Palabra::Palabra(const string& unNombre, int cantidadDeApariciones) {
	this->nombre = unNombre;
	this->apariciones = cantidadDeApariciones;
}

Mapa Palabra::getPrecedencias(int valorMinimo){
	Mapa mapaAux;

	IteradorMapa it = this->getIteradorMapa();
	for (it = this->precedencias.begin(); it!=this->precedencias.end(); ++it){
		if (it->second > valorMinimo) mapaAux[it->first] = it->second;
	}

	return mapaAux;
}


Palabra::~Palabra() {

}

