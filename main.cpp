/*
 * main.cpp
 *
 *  Created on: Sep 29, 2014
 *      Author: manuel
 */
#include "Foo.h"
#include "LectorDeArchivo.h"
#include "Palabra.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <vector>

using namespace std;


int main(int argc, char **argv) {

	/*
	 * LA IDEA ES LA SIGUIENTE:
	 * tendriamos una LISTA de PALABRAS (o cualquier estructura que nos convenga)
	 * e iriamos leyendo de a 2 palabras del texto en cuestion.
	 * Verificariamos si esta la palabra o no en esta "LISTA". Si no esta, se la
	 * agrega y luego se agrega la palabra que la precide, y si esta,
	 * simplemente se accede a la posicion en la "LISTA" y se le agrega la
	 * palabra que precede a la lista de precedencias.
	 *
	 *
	 * Usemos un set de entrenamiento bien reducido para ir probando las cosas.
	 *
	 * Lo que falta:
	 * + Una vez cargado esto en memoria hay que poder serializarlo. (arch en disco)
	 * + Deserializar el arch en disco.
	 *
	 * Hago enfasis en que usemos archivos peque;os para testear, si algo
	 * funciona para 100 palabras, va a funcionar para 10000000000000000.
	 * (recemos)
	 *
	 */




	/*
	 * Practice.txt es un archivo de prueba, tamanio bastante menor que el set posta
	 *
	 */
	string palabras = LectorDeArchivo::leerArchivo("practice.txt");
	cout << "Longitud del string: " << palabras.length() << endl;

	//Deberia mostrar "The Adventure", que son los primeros 13 digitos del txt
	for (int i = 0; i < 13; i++) {
		cout << palabras[i];
	}
	cout << endl;



	/*
	 * Cosas de la libreria de boost. Splitea todas las palabras del string y las deja
	 * en el el vector en el mismo orden en el que aparecieron.
	 */
    typedef vector< string > split_vector_type;
    split_vector_type SplitVec;
    //Is Any Of: caracteres por los que splitea palabra.
    boost::split(SplitVec, palabras, boost::is_any_of(" .,?!\"-"), boost::token_compress_on);

    //Muestra por consola todas las palabras del archivo de arriba, es super eficiente.
    /*for (std::vector<std::string>::iterator pos = SplitVec.begin(); pos != SplitVec.end(); ++pos) {
          cout << *pos << endl;
      }
	/*


	/* FALTA
	 * Ir iterando de a 2 elementos e ir agregandolos en la lista con sus precedencias.
	 */






    /*
     * Pruebas sobre la clase PALABRA.
     */
	Palabra *unaPalabra = new Palabra("PERRO");
	unaPalabra->agregarPrecedencia("mi");

	//3 agregadas para ver lo bien que funciona.
	unaPalabra->agregarPrecedencia("EL");
	unaPalabra->agregarPrecedencia("el");
	unaPalabra->agregarPrecedencia("El");

	unaPalabra->agregarPrecedencia("los");
	unaPalabra->agregarPrecedencia("la");
	unaPalabra->agregarPrecedencia("las");

	unaPalabra->mostrarPrecedencias();

	Palabra *otraPalabra = new Palabra("amigos");

	otraPalabra->agregarPrecedencia("somos");
	otraPalabra->agregarPrecedencia("mis");
	otraPalabra->agregarPrecedencia("tenemos");
	otraPalabra->agregarPrecedencia("somos");
	otraPalabra->agregarPrecedencia("somos");
	otraPalabra->agregarPrecedencia("los");
	otraPalabra->agregarPrecedencia("son");
	otraPalabra->agregarPrecedencia("mis");

	otraPalabra->mostrarPrecedencias();


	Foo *unFoo = new Foo();
	unFoo->doFoo();
	return 0;
}
