#ifndef _PREDICADO
#define _PREDICADO
#include <string>
#include <vector>
#include <utility>

using namespace std;

class Predicado{
	private: 
		int cantidadPalabras;
		string * palabras;
		string objetivo;
		vector<pair<string,string>> pares;
	public:
		Predicado();
		Predicado(int, string *,vector<pair<string,string>>);
		bool existe(pair<string,string>);
		void setObjetivo(string);
}

#endif