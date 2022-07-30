#include "Predicado.h"

/**
 * @brief Constructor por omision
**/
void Predicado::init()
{
	_cantidadPalabras = 0;
	_palabras = 0;
	_objetivo = "";
	_pares = vector<pair<string,string>>();
}

/**
 * @brief Constructor con parametros
**/
void Predicado::setup(int cantidadPalabras, string * palabras, vector<pair<string,string>> pares)
{
	_cantidadPalabras = cantidadPalabras;
	_palabras = palabras;
	_pares = pares;
	_objetivo = "";
}
/**
 * @brief Determina si la palabra se encuentra como llave en el vector
 *
 * @return bool que indica si se encuentra
**/
bool Predicado::existe(const pair<string,string>& parejaValor)
{return (_objetivo == parejaValor.first);}

/**
 * @brief Metodo set de objetivo
 *
 *@param string objetivo String que se le asigna a objetivo
**/
void Predicado::setObjetivo(string objetivo)
{_objetivo = objetivo;}