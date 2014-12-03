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
 * Dada una ruta al archivo de texto, copia todo el contenido en un String.
 */
string LectorDeArchivo::leerArchivo(const char *filename){
  std::ifstream in(filename, std::ios::in | std::ios::binary);
  if (in){
    std::string contents;
    in.seekg(0, std::ios::end);
    contents.resize(in.tellg());
    in.seekg(0, std::ios::beg);
    in.read(&contents[0], contents.size());
    in.close();
    return(contents);
  }
  throw(errno);
}
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
	size_t limiteSuperior = 1000000000;

	for (int i = 0; i<1; i++){
		cout << "Pasada = " << i << endl;

		// allocate memory to contain the whole file:
		buffer = (char*) malloc (sizeof(char)*1000000000);
		if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

		result = fread (buffer,limiteInferior,limiteSuperior,pFile);
		//if (result != lSize) {fputs ("Reading error",stderr); exit (3);}

		Tokenizer::tokenizeAux(diccionario, buffer);
		free (buffer);
		cout << "Buffer freed" << endl;
		limiteInferior += limiteSuperior;
		limiteSuperior += 1000000000;
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


void LectorDeArchivo::leerArchivoAuxAux(const char* filename, ContenedorDePalabras* diccionario){
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

	cout << "Antes del while" << endl;

	//Modificar este para leer de a X oraciones.
	//*while (std::getline(infile, line) && (i<500000))
	while (std::getline(infile, line))
	{
		//cout << line<< endl;
		Tokenizer::tokenizeAux(diccionario, line);
		i++;

		//if (i==1) exit(0);
		// process pair (a,b)
	}

	cout << "Proceso OK!" << endl;
}

LectorDeArchivo::LectorDeArchivo() {
	//No se debe instanciar esta clase.
}

LectorDeArchivo::~LectorDeArchivo() {
	// TODO Auto-generated destructor stub
}

