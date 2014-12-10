/*
 * main.cpp
 *
 *  Created on: Sep 29, 2014
 *      Author: manuel
 */
#include "Foo.h"
#include "LectorDeArchivo.h"
#include "ContenedorDePalabras.h"
#include "Analizador.h"
#include "Serializador.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <vector>
#include "Tokenizer.h"

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
	/*
	string palabras = LectorDeArchivo::leerArchivo("trunk/practice.txt");
	cout << "Longitud del string: " << palabras.length() << endl;

	//Deberia mostrar "The Adventure", que son los primeros 13 digitos del txt
	for (int i = 0; i < 13; i++) {
		cout << palabras[i];
	}
	cout << endl;
	*/

    /*
     * Pruebas sobre la clase PALABRA.
     */
	/*
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
	*/


	/*
	 * Se agrega bien sin importar los uppercases y eso.
	 */
	/*
	cout <<"Pruebas de Contendor:" << endl;
	ContenedorDePalabras *contenedor = new ContenedorDePalabras();

	if (!contenedor->existePalabra("Perro")) {
		cout<<"No existe la palabra perro"<<endl;
		Palabra *unaPalabra = new Palabra("PErro");
		unaPalabra->agregarPrecedencia("mi");

		contenedor->agregarPalabra(unaPalabra);
	}
	if (contenedor->existePalabra("peRRO")) {
		cout<<"Existe la palabra Perro"<<endl;
		contenedor->getPalabra("PERRO")->agregarPrecedencia("EL");
	}

	contenedor->getPalabra("perro")->mostrarPrecedencias();
	*/



	/*
	 *
	 * Prueba de fuego
	 *
	 *
	 */
	/*Tokenizer::tokenize(contenedor, palabras);
	contenedor->getPalabra("the")->mostrarPrecedencias();


	Foo *unFoo = new Foo();
	unFoo->doFoo();*/


	//Cantidad de lineas del set de entreamiento, por si sirve.
	int numberOfLines = 30301028;

	/*ContenedorDePalabras *diccionario = new ContenedorDePalabras();

	//Ruta al archivo de texto de 5 gigas, obviamente es una ruta local.
	LectorDeArchivo::leerArchivo("/media/manuel/FE64EB6864EB225F/Downloads/train_v2.txt/train_v2.txt", diccionario);


	cout << "Antes de eliminar los puntos (.)"<< endl;
	diccionario->eliminarPalabra(".");
	diccionario->eliminarPrecedencia(".");

	cout << "My aparecio: "<< diccionario->getPalabra("my")->apariciones << endl;

	cout << "Antes de Serializar"<< endl;
	Serializador *unSerializador = new Serializador(diccionario);
	unSerializador->serializar();
	cout << "Despues de Serializar."<< endl;

*/
	//Creo otro diccionario para levantar el archivo de texto serializado y poder comparar.
	ContenedorDePalabras *otroDiccionario = new ContenedorDePalabras();

	//int dog = 1/0;

	cout << "Antes de DeSerializar"<< endl;
	Serializador *otroSerializador = new Serializador(otroDiccionario);
	otroSerializador->deserializar();
	cout << "Despues de DeSerializar."<< endl;

	cout << "My aparecio: "<< otroDiccionario->getPalabra("my")->apariciones << endl;

	std::clock_t start;
	double duration;


	start = std::clock();

	Analizador* analizador = new Analizador(otroDiccionario);
	//analizador->analizar("test.txt", "salida.txt");
	//analizador->analizar("kaggle_test.txt", "salida.txt");
	analizador->analizar("/media/manuel/FE64EB6864EB225F/Downloads/train_v2.txt/test_v2.txt", "salida.txt");

	duration = ( std::clock() - start ) / (double) CLOCKS_PER_SEC;
	cout<<"La ejecucion tardo:  " <<  duration <<'\n';

	cout << "Depsues de analizar" << endl;



	return 0;
}
