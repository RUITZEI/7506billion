/*
 * LectorDeArrchivo.cpp
 *
 *  Created on: Nov 1, 2014
 *      Author: manuel
 */

#include <stdio.h>
#include "LectorDeArchivo.h"

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

LectorDeArchivo::LectorDeArchivo() {
	//No se debe instanciar esta clase.
}

LectorDeArchivo::~LectorDeArchivo() {
	// TODO Auto-generated destructor stub
}

