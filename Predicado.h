#ifndef _PREDICADO
#define _PREDICADO
#include <string>
#include <vector>
#include <utility>

using namespace std;

/**
 * @brief Clase que contiene un predicado para ser utilizado en find_if
**/
class Predicado{
	private: 
		inline static string _objetivo;	
	public:
		static void init();
		static bool existe(const pair<string,string>& llaveValor);
		static void setObjetivo(string);
};

#endif