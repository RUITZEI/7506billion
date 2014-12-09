/*
 * LectorDeArrchivo.cpp
 *
 *  Created on: Nov 1, 2014
 *      Author: manuel
 */

#include <stdio.h>
#include <stdlib.h>
#include "LectorDeArchivo.h"
#include "Tokenizer.h"

/*
 * Leer archivo por bytes.
 */
void LectorDeArchivo::leerArchivoAux(const char* filename, ContenedorDePalabras* diccionario){
	FILE * pFile;
	long lSize;
	char * buffer;
	size_t result;

	pFile = fopen ( filename , "rb" );
	if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	std::cout << lSize << endl;
	rewind (pFile);



	// copy the file into the buffer:
	//result = fread (buffer,1,lSize,pFile);
	size_t limiteInferior = 1;
	size_t limiteSuperior = 500000000;

	for (int i = 0; i<1; i++){
		cout << "Pasada = " << i << endl;

		// allocate memory to contain the whole file:
		buffer = (char*) malloc (sizeof(char)*500000000);
		if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

		result = fread (buffer,limiteInferior,limiteSuperior,pFile);
		//if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

		Tokenizer::tokenize(diccionario, buffer);
		free (buffer);
		cout << "Buffer freed" << endl;
		limiteInferior += limiteSuperior;
		limiteSuperior += 500000000;
	}

	cout<< "Chau FOR grande"<< endl;

	//result = fread (buffer,1,100000000,pFile);
	//if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

	//Tokenizer::tokenizeAux(diccionaro, buffer);


	/*for (int i = 0;  i < 12; ++ i) {
		cout<<buffer[i];
	}*/

	/* the whole file is now loaded in the memory buffer. */

	// terminate
	fclose (pFile);

	//free (buffer);

	//return buffer;
}

/*
 * Leo archivo por lineas, voy tokenizando y cargando la estructura.
 */
void LectorDeArchivo::leerArchivo(const char* filename, ContenedorDePalabras* diccionario){
	FILE * pFile;
	long lSize;
	size_t result;
	std::string line;
	int i = 0;

	pFile = fopen ( filename , "rb" );
	if (pFile==NULL) {fputs ("File error",stderr); exit (1);}

	// obtain file size:
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	std::cout << lSize << endl;
	rewind (pFile);

	fclose(pFile);

	std::ifstream infile(filename);
	int numberOfLines = 30301028;

	/* Modificar el de arriba para leer de a X oraciones.
	 * Usar el de abajo para leer todo el texto.
	 */
	//while (std::getline(infile, line) && (i< numberOfLines/32))
	while (std::getline(infile, line))
	{
		//cout << line<< endl;
		//cout << line.length() << endl;
		Tokenizer::tokenize(diccionario, line);
		i++;
	}

	//string a = "% & * # !";
	//Tokenizer::tokenize(diccionario, a);
	cout << i << endl;
}

LectorDeArchivo::LectorDeArchivo() {
	//No se debe instanciar esta clase.
}

LectorDeArchivo::~LectorDeArchivo() {
	// TODO Auto-generated destructor stub
}

