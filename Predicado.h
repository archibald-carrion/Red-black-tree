#ifndef _PREDICADO
#define _PREDICADO
#include <string>
#include <vector>
#include <utility>

using namespace std;

class Predicado{
	private: 
		inline static int _cantidadPalabras;
		inline static string* _palabras;
		inline static string _objetivo;
		inline static vector<pair<string,string>> _pares;
		
	public:
		static void init();
		static void setup(int, string *,vector<pair<string,string>>);
		static bool existe(const pair<string,string>& llaveValor);
		static void setObjetivo(string);
};

#endif