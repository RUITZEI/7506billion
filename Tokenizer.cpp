/*
 * Tokenizer.cpp
 *
 *  Created on: Nov 16, 2014
 *      Author: manuel
 */

#include "Tokenizer.h"
#include <ctype.h>

Tokenizer::Tokenizer() {
	// TODO Auto-generated constructor stub

}

Tokenizer::~Tokenizer() {
	// TODO Auto-generated destructor stub
}


/*
 * Recibo de a 1 oracion esta vez...
 */
void Tokenizer::tokenize(ContenedorDePalabras *unContenedor, const string &unString){
	typedef vector< string > split_vector_type;

	split_vector_type palabrasDeOracion;

	if (unString.length() == 1473) {return;}

	//Separo todo el texto en oraciones.
	boost::split(palabrasDeOracion, unString, boost::is_any_of(" ()&:!?\"\n\t,"), boost::token_compress_on);

	//cout << "La casa esta en orden"<< endl;
	//cout << palabrasDeOracion.size()<< " ->";
	//if (!palabrasDeOracion.empty()) return;

	//Precedencia apunta a la primer palabra de la oracion.
	vector<string>::iterator precedencia = palabrasDeOracion.begin();
	vector<string>::iterator palabraFinal = palabrasDeOracion.end()-1;

	//cout << palabrasDeOracion.size()<<endl;

	/*
	 * Ignorar oraciones con menos de 5 palabras, no aportan nada y molestan.
	 */
	if ((palabrasDeOracion.size() > 5) ){
		/*
		 * Si hay mas de una palabra en la oracion, debo agregar la palabra
		 * 'ENDL' con precedencia la ultima palabra de la oracion.
		 */

		//  Nos aseguramos de que la palabra final sea realmente una palabra
		//  Una oracion NUNCA terminaria con una palabra de un solo caracter.
		while ((*palabraFinal).length() <= 1) {
			if ( isalnum((*palabraFinal)[0])) break;
			palabraFinal--;
		}

		if (unContenedor->existePalabra("ENDL")){
			unContenedor->getPalabra("ENDL")->agregarPrecedencia(*palabraFinal);
			//cout<<*palabraFinal<<"->  ENDL"<<endl;
		} else {
			Palabra *palabraPorAgregar = new Palabra("ENDL");
			palabraPorAgregar->agregarPrecedencia(*palabraFinal);
			unContenedor->agregarPalabra(palabraPorAgregar);
			//cout<<*palabraFinal<<"->  ENDL"<<endl;
		}

		//Nos aseguramos de que sea una palabra y no un espacio o algo por el estilo.
		while ((*precedencia).length() <= 1) {
			if (isalnum((*precedencia)[0])) break;
			precedencia ++;
		}

		//A la primer palabra le agrego ENDL como precedencia.
		if (unContenedor->existePalabra(*precedencia)){
			unContenedor->getPalabra(*precedencia)->agregarPrecedencia("ENDL");
			//cout <<"ENDL ->"<< *precedencia <<endl;
			//cout<<"existia la palabra en el diccionario"<<endl;
		} else {
			Palabra *palabraPorAgregar = new Palabra(*precedencia);
			palabraPorAgregar->agregarPrecedencia("ENDL");
			unContenedor->agregarPalabra(palabraPorAgregar);
			//cout <<"ENDL ->"<< *precedencia <<endl;
		}


		/*
		 * Voy iterando por todas las palabras del Palabras De Oraciones
		 * y le agrego sus precedencias como antes.
		 */
		for (vector<string>::iterator palabra = precedencia + 1; palabra <= palabraFinal; ++palabra) {
			//cout << "For Loop" << endl;
			if (unContenedor->existePalabra(*palabra)){
				unContenedor->getPalabra(*palabra)->agregarPrecedencia(*precedencia);
				//cout << *precedencia << "->" << *palabra <<endl;
			} else {
				Palabra *palabraPorAgregar = new Palabra(*palabra);
				palabraPorAgregar->agregarPrecedencia(*precedencia);
				unContenedor->agregarPalabra(palabraPorAgregar);
				//cout << *precedencia << "->" << *palabra <<endl;
			}

			precedencia ++;
		}
	}

		//cout << "Todo en orden"<< endl;
}

/*
 * Recibo de a 1 oracion esta vez...
 */
void Tokenizer::tokenizeAux(ContenedorDePalabras *unContenedor, string& unString){
	typedef vector< string > split_vector_type;

	split_vector_type vectorOraciones;
	split_vector_type palabrasDeOracion;

	//cout << "antes del split" << endl;

	//Separo todo el texto en oraciones.
	boost::trim_if(unString, boost::is_any_of(" "));
	boost::split(palabrasDeOracion, unString, boost::is_any_of(" ()!?\"\n\t,"), boost::token_compress_on);

	//Precedencia apunta a la primer palabra de la oracion.
	vector<string>::iterator precedencia = palabrasDeOracion.begin();

	if ((palabrasDeOracion.size() > 1) ){
		/*
		* Si hay mas de una palabra en la oracion, debo agregar la palabra
		* 'ENDL' con precedencia la ultima palabra de la oracion.
		*/
		 vector<string>::iterator palabraFinal = palabrasDeOracion.end() -2;
		 if((*palabraFinal).length() > 0){
			 if (unContenedor->existePalabra("ENDL")){
				 unContenedor->getPalabra("ENDL")->agregarPrecedencia(*palabraFinal);
				 //cout<<*palabraFinal<< "-> ENDL" << endl;
			 } else {
				 Palabra *palabraPorAgregar = new Palabra("ENDL");
				 palabraPorAgregar->agregarPrecedencia(*palabraFinal);
				 unContenedor->agregarPalabra(palabraPorAgregar);
				// cout<<*palabraFinal<< "-> ENDL" << endl;
			 }
		 }

		 if ((*precedencia).length() > 0){
			 //A la primer palabra le agrego ENDL como precedencia.
			 if (unContenedor->existePalabra(*precedencia)){
				 unContenedor->getPalabra(*precedencia)->agregarPrecedencia("ENDL");
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


