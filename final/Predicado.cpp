#include "Predicado.h"

/**
 * @brief Inicializa _objetivo
**/
void Predicado::init()
{
	_objetivo = "";
}
/**
 * @brief Determina si la palabra se encuentra como primer elemento en el par
 *
 * @param parejaValor Pair que contien dos strings 
 * @return bool que indica si se encuentra
**/
bool Predicado::existe(const pair<string,string>& parejaValor)
{return (_objetivo == parejaValor.first);}

/**
 * @brief Metodo set de objetivo
 *
 * @param objetivo String que se le asigna a objetivo
**/
void Predicado::setObjetivo(string objetivo)
{_objetivo = objetivo;}