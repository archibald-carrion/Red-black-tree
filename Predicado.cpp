#include "Predicado.h"

/**
 * @brief Constructor por omision
**/
Predicado::Predicado(){
	cantidadPalabras = 0;
	palabras = 0;
	objetivo = "";
	pares = 0;
}
/**
 * @brief Constructor con parametros
**/
Predicado::Predicado(int cantidadPalabras, string * palabras, vector<pair<string,string>> pares){
	this->cantidadPalabras = cantidadPalabras;
	this->palabras = palabras;
	this->pares = pares;
	objetivo = "";
}
/**
 * @brief Determina si la palabra se encuentra como llave en el vector
 *
 * @return bool que indica si se encuentra
**/
bool Predicado::existe(pair<string,string> llaveValor){
	return objetivo == get<0>(llaveValor);
}
/**
 * @brief Metodo set de objetivo
 *
 *@param string objetivo String que se le asigna a objetivo
**/
void setObjetivo(string objetivo){
	this->objetivo = objetivo;
}