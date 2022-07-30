#include "ArbolRojoNegro.h"
#include <iostream>
#include <fstream>

#include <algorithm>
#include <vector>
#include <map>
#include <string>

#include <chrono>						//para medir tiempo
#include <utility>						//para usar move semantics y evitar copias largas
#include <iomanip>						//para notacion cientifica y decimales arbitrarios
#include "Predicado.h"					//para el prueba vector

using namespace std;

/**
 * @brief El metodo existe permite verificar si un pair ya existe en el vector con la llave dada
 * @param arrayString El string que hay que buscar en el vector
 * @param palabras Es un vector<pair<string,string,>> 
 * @return El metodo devuelve un int, si el elemento existe devuelve un 1, sino devuelve un 0
 */
int existe(string palabraBuscada, vector<pair<string,string>> palabras){
	int existe = 0;
	for(auto i = palabras.begin(); i != palabras.end() && existe == 0; ++i){
		if(palabraBuscada == i->first){
			existe = 1; //Sí esta en el vector
		}
	}

	return existe;
}

/**
 * @brief El metodo probarArbol permite realizar las pruebas con el arbol rojo y negro
 * @param arrayString arrayString es un array que contiene todas las palabras del archivo de texto de input
 * @param cantidadElementosLectura  cantidadElementosLectura es la cantidad de elementos que hay que leer de arraystring y guardar en el arbol rojo y negro
 * @param pasoPrueba pasoPrueba es la cantidad de elementos por prueba
 * @param cantidadPruebas cantidadPruebas es la cantidad de pruebas que hay que realizar
 * @return El metodo devuelve un vector<double> que contiene los cantitdadPruebas tiempos de ejecucion, nos permitiran graficar la evolucion del tiempo
 */
vector<double> probarArbol(string* arrayString, int cantidadElementosLectura, int pasoPrueba, int cantidadPruebas)
{
}

/**
 * @brief El metodo robarMapSTL permite realizar las pruebas con el map de la STL
 * @param arrayString arrayString es un array que contiene todas las palabras del archivo de texto de input
 * @param cantidadElementosLectura  cantidadElementosLectura es la cantidad de elementos que hay que leer de arraystring y guardar en el map de la STL
 * @param pasoPrueba pasoPrueba es la cantidad de elementos por prueba
 * @param cantidadPruebas cantidadPruebas es la cantidad de pruebas que hay que realizar
 * @return El metodo devuelve un vector<double> que contiene los cantitdadPruebas tiempos de ejecucion, nos permitiran graficar la evolucion del tiempo
 */
vector<double> probarMapSTL(string* arrayString, int cantidadElementosLectura, int pasoPrueba, int cantidadPruebas)
{
	map <string,string> mapSTL;
	int counter0=0;
	//llenar el mapa, investigando parejas hasta la penúltima palabra con la última
	while(counter0<cantidadElementosLectura-1){
		if(mapSTL.find(arrayString[counter0]) == mapSTL.end()){		// la llave aun no existe en el map
			mapSTL[arrayString[counter0]] = arrayString[counter0+1];
		}														// la llave ya existe en el map
		++counter0;	//que la palabra ya existe o no en el map de toda manera se incrementa el contador
	}

	// el caso de la última palabra es especial. si no existe previamente en el mapa, se asocia con una palabra vacía
	if(mapSTL.find(arrayString[cantidadElementosLectura-1]) == mapSTL.end())
	mapSTL[arrayString[cantidadElementosLectura-1]] = string("");
	
	vector<double> tiemposEjecuciones;
	
	int counter1 = 0;
	while(counter1< cantidadPruebas*pasoPrueba && counter1 < cantidadElementosLectura){
		counter0 = 0;

		auto start = chrono::steady_clock::now();
		while(counter0<pasoPrueba)
		{
			mapSTL.find(arrayString[counter1]);
			mapSTL.find(arrayString[counter1] + string("NoIsE"));
			++counter0;
			++counter1;
		}
		auto end = chrono::steady_clock::now();

		double tiempoEjecucion = double (chrono::duration_cast<chrono::microseconds>(end-start).count());
		tiemposEjecuciones.push_back(tiempoEjecucion);	//agregar el tiempo al vector de tiempo
	}

	return tiemposEjecuciones;
}

/**
 * @brief El metodo probarVectorSTL permite realizar las pruebas con el vector de la STL, esun vector de pair<key, value>
 * @param arrayString arrayString es un array que contiene todas las palabras del archivo de texto de input
 * @param cantidadElementosLectura  cantidadElementosLectura es la cantidad de elementos que hay que leer de arraystring y guardar en el vector de la STL
 * @param pasoPrueba pasoPrueba es la cantidad de elementos por prueba
 * @param cantidadPruebas cantidadPruebas es la cantidad de pruebas que hay que realizar
 * @return El metodo devuelve un vector<double> que contiene los cantitdadPruebas tiempos de ejecucion, nos permitiran graficar la evolucion del tiempo
 */
vector<double> probarVectorSTL(string* arrayString, int cantidadElementosLectura, int pasoPrueba, int cantidadPruebas)
{
	vector<pair<string,string>> palabras;

    Predicado::init();
    Predicado::setup(pasoPrueba, arrayString, palabras);

	//Llenar el vector palabras
	for(int i=0; i< cantidadElementosLectura-1; ++i){ //Se revisa si la palabra ya esta en el vector
		if(!existe(arrayString[i], palabras)){
			palabras.push_back(pair<string,string>(arrayString[i],arrayString[i+1]));
		}
	}
	if(!existe(arrayString[cantidadElementosLectura-1], palabras)){ //La ultima palabra se añade junto con una palabra nula
		palabras.push_back(pair<string,string>(arrayString[cantidadElementosLectura-1],string("")));
	}
	//Hacer la busqueda
	vector<double> tiempos; bool posibleOverflow = false;
	for(int i=0; i < cantidadPruebas && !posibleOverflow; ++i)
    {
		if((cantidadElementosLectura - (i * pasoPrueba)) >= pasoPrueba)
		{
			auto start = chrono::steady_clock::now();
			for(int j = 0; j < pasoPrueba; ++j)
			{	
				string palabraBuscada = arrayString[j + i*pasoPrueba];

				Predicado::setObjetivo(palabraBuscada);
				find_if(palabras.begin(), palabras.end(), Predicado::existe);

				Predicado::setObjetivo(palabraBuscada + string("NoIsE"));
				find_if(palabras.begin(), palabras.end(), Predicado::existe);
			}
			auto end = chrono::steady_clock::now();

			double tiempoEjecucion = double(chrono::duration_cast<chrono::microseconds>(end-start).count());
			tiempos.push_back(tiempoEjecucion);
		}
		else posibleOverflow = true;
	}

	return tiempos;
}

/**
 * @brief El metodo lector permite leer el archivo de texto y guarda el contenido en arrayString
 * @param arrayString arrayString es un array en el cual hay que guardar todas las palabras del archivo nombreArchivo
 * @param nombreArchivo nombreArchivo es un string que contiene el nombre del archivo que hay que leer y del cual queremos guardar el contenido en arrayString
 */
void lector(string* arrayString, string nombreArchivo, unsigned int cantidadPalabras)
{
    string word;
    ifstream file;

    file.open(nombreArchivo);
    unsigned int counter = 0;

    while(!file.eof() && counter < cantidadPalabras)
    {
        file >> word;
        arrayString[counter] = word;
        ++counter;
    }

	file.close();
	return;
}

/**
 * @brief El metodo main maneja todo el programa y llama los metodos necesarios para el buen desarrollo del programa
 */
int main()
{

    // probarArbol_s();

	int cantidadElementosLectura;		// cantidad de palabras que hay que leer del archivo y guardar en la data structures
	cin>>cantidadElementosLectura;		
	int pasoPrueba;						// cantidad de palabras que hay que probar por pruebas
	cin>>pasoPrueba;
	int cantidadPruebas;				// cantidad de pruebas que hay que hacer 
	cin>>cantidadPruebas;
	string nombreArchivo;  				//"datos.txt"	--> nombre del archivo que hay que leer 
	cin>>nombreArchivo;

	cout << "PARAMETROS : " << endl
	<< "cantidadElementosLectura = " << cantidadElementosLectura << endl
	<< "pasoPrueba = " << pasoPrueba << endl
	<< "cantidadPruebas = " << cantidadPruebas << endl
	<< "nombreArchivo = " << nombreArchivo << endl;
	
    string *arrayString = new string[cantidadElementosLectura];
    lector(arrayString, nombreArchivo, cantidadElementosLectura);

	//se guarda todos los tiempos de ejecución en vectores
	// vector<double> resultadoArbolRojoNegro = move(probarArbol(arrayString,cantidadElementosLectura, pasoPrueba, cantidadPruebas));
	vector<double> resultadoMapSTL = move(probarMapSTL(arrayString,cantidadElementosLectura, pasoPrueba, cantidadPruebas));
	vector<double> resultadoVectorSTL = move(probarVectorSTL(arrayString,cantidadElementosLectura, pasoPrueba, cantidadPruebas));

	cout << scientific;
	cout << setprecision(5);

	//guardamos los resultados en una .txt
	cout << "TIEMPOS DE BUSQUEDA EN MAP STL" << endl;
	unsigned long long tamanoResultadoMapSTL = resultadoMapSTL.size();
	for(unsigned long long i = 0; i < tamanoResultadoMapSTL; ++i) cout << i << " " << resultadoMapSTL[i] << endl;

	cout << "TIEMPOS DE BUSQUEDA EN VECTOR STL" << endl;
	unsigned long long tamanoResultadoVectorSTL = resultadoVectorSTL.size();
	for(unsigned long long i = 0; i < tamanoResultadoVectorSTL; ++i) cout << i << " " << resultadoVectorSTL[i] << endl;
	
    delete[] arrayString;
    return 0;
}