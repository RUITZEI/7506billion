/*
 * Tokenizer.cpp
 *
 *  Created on: Nov 16, 2014
 *      Author: manuel
 */

#include "Tokenizer.h"

Tokenizer::Tokenizer() {
	// TODO Auto-generated constructor stub

}

Tokenizer::~Tokenizer() {
	// TODO Auto-generated destructor stub
}

void Tokenizer::tokenize(ContenedorDePalabras *unContenedor, const string &unString){
	typedef vector< string > split_vector_type;

	split_vector_type vectorOraciones;
	split_vector_type palabrasDeOraciones;

	//Separo todo el texto en oraciones.
	boost::split(vectorOraciones, unString, boost::is_any_of("."), boost::token_compress_on);
	cout << vectorOraciones.size()<< endl;

	//Por cada oracion, separo la misma en palabras.
	for (size_t i = 0; i < vectorOraciones.size(); i++) {
		boost::split(palabrasDeOraciones, vectorOraciones[i], boost::is_any_of(" -!?\"\n\t,"), boost::token_compress_on);
		vector<string>::iterator precedencia = palabrasDeOraciones.begin();

		if ((palabrasDeOraciones.size() > 1) ){
			/*
			 * Si hay mas de una palabra en la oracion, debo agregar la palabra 'ENDL' con precedencia
			 * 'ENDL' con precedencia la ultima palabra de la oracion.
			 */
			/// -2 porque la ultima es un punto.
			vector<string>::iterator palabraFinal = palabrasDeOraciones.end() -1;
			if (unContenedor->existePalabra("ENDL")){
				unContenedor->getPalabra("ENDL")->agregarPrecedencia(*palabraFinal);
				//cout<<"existia la palabra en el diccionario"<<endl;
			} else {
				Palabra *palabraPorAgregar = new Palabra("ENDL");
				palabraPorAgregar->agregarPrecedencia(*palabraFinal);
				unContenedor->agregarPalabra(palabraPorAgregar);
			}

			//Si no es la primer iteracion siempre me deja un espacio en blanco en la primer posicion.
			if (!i == 0){
				vector<string>::iterator precedenciaAux = precedencia + 1;
				if (unContenedor->existePalabra(*precedenciaAux)){
					unContenedor->getPalabra(*precedenciaAux)->agregarPrecedencia("ENDL");
					//cout<<"existia la palabra en el diccionario"<<endl;
				} else {
					Palabra *palabraPorAgregar = new Palabra(*precedenciaAux);
					palabraPorAgregar->agregarPrecedencia("ENDL");
					unContenedor->agregarPalabra(palabraPorAgregar);
				}
			//Si es la primera iteracion, tengo que agregarle el ENDL de precedencia a la primer palabra
			}else {
				if (unContenedor->existePalabra(*precedencia)){
					unContenedor->getPalabra(*precedencia)->agregarPrecedencia("ENDL");
					//cout<<"existia la palabra en el diccionario"<<endl;
				} else {
					Palabra *palabraPorAgregar = new Palabra(*precedencia);
					palabraPorAgregar->agregarPrecedencia("ENDL");
					unContenedor->agregarPalabra(palabraPorAgregar);
				}
			}
		}

		/*
		 * Voy iterando por todas las palabras del Palabras De Oraciones
		 * y le agrego sus precedencias como antes.
		 */
		for (vector<string>::iterator palabra = palabrasDeOraciones.begin() + 1; palabra != palabrasDeOraciones.end() ; ++palabra) {
			if (unContenedor->existePalabra(*palabra)){
				unContenedor->getPalabra(*palabra)->agregarPrecedencia(*precedencia);
			} else {
				Palabra *palabraPorAgregar = new Palabra(*palabra);
				palabraPorAgregar->agregarPrecedencia(*precedencia);
				unContenedor->agregarPalabra(palabraPorAgregar);
			}

			precedencia ++;
		}
	}
}

/*
 * Recibo de a 1 oracion esta vez...
 */
void Tokenizer::tokenizeAux(ContenedorDePalabras *unContenedor, const string &unString){
	typedef vector< string > split_vector_type;

	split_vector_type vectorOraciones;
	split_vector_type palabrasDeOracion;

	//cout << "antes del split" << endl;

	//Separo todo el texto en oraciones.
	boost::split(palabrasDeOracion, unString, boost::is_any_of(" ()-!?\"\n\t,"), boost::token_compress_on);
	//cout << "despues del split" << endl;

		//Precedencia apunta a la primer palabra de la oracion.
		vector<string>::iterator precedencia = palabrasDeOracion.begin();

		if ((palabrasDeOracion.size() > 1) ){
			/*
			 * Si hay mas de una palabra en la oracion, debo agregar la palabra
			 * 'ENDL' con precedencia la ultima palabra de la oracion.
			 */
			vector<string>::iterator palabraFinal = palabrasDeOracion.end() -2;
			if((*palabraFinal).length() > 1){
				if (unContenedor->existePalabra("ENDL")){
					unContenedor->getPalabra("ENDL")->agregarPrecedencia(*palabraFinal);
					//cout<<*palabraFinal<<endl;
				} else {
					Palabra *palabraPorAgregar = new Palabra("ENDL");
					palabraPorAgregar->agregarPrecedencia(*palabraFinal);
					unContenedor->agregarPalabra(palabraPorAgregar);
					//cout<<*palabraFinal<<endl;
				}


			//A la primer palabra le agrego ENDL como precedencia.
			if (unContenedor->existePalabra(*precedencia)){
				unContenedor->getPalabra(*precedencia)->agregarPrecedencia("ENDL");
				//cout<<"existia la palabra en el diccionario"<<endl;
			} else {
				Palabra *palabraPorAgregar = new Palabra(*precedencia);
				palabraPorAgregar->agregarPrecedencia("ENDL");
				unContenedor->agregarPalabra(palabraPorAgregar);
			}
		}

		/*
		 * Voy iterando por todas las palabras del Palabras De Oraciones
		 * y le agrego sus precedencias como antes.
		 */
			for (vector<string>::iterator palabra = palabrasDeOracion.begin() + 1; palabra != palabrasDeOracion.end() - 1; ++palabra) {
				//cout << "For Loop" << endl;
				if (unContenedor->existePalabra(*palabra)){
					unContenedor->getPalabra(*palabra)->agregarPrecedencia(*precedencia);
				} else {
					Palabra *palabraPorAgregar = new Palabra(*palabra);
					palabraPorAgregar->agregarPrecedencia(*precedencia);
					unContenedor->agregarPalabra(palabraPorAgregar);
				}

				precedencia ++;
			}
	}

		//cout << "Todo en orden"<< endl;
}


