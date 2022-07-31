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
 * @brief El metodo promediarTiempos permite obtener el promedio de un vector de tiempos
 * @param tiempos Es el vector<double> de los tiempos de busqueda que se desean promediar
 * @return El metodo devuelve el promedio de los valores existentes en el vector de tiempos
 */
double promediarTiempos(const vector<double>& tiempos)
{
	double promedio = 0;
	unsigned long long cantidadTiempos = tiempos.size();
	for(vector<double>::const_iterator i = tiempos.begin(); i != tiempos.end(); ++i) promedio += *i;

	return (promedio / cantidadTiempos);
}

/**
 * @brief El metodo probarArbol permite realizar las pruebas con el arbol rojo y negro
 * @param arrayString arrayString es un array que contiene todas las palabras del archivo de texto de input
 * @param cantidadElementosLectura  cantidadElementosLectura es la cantidad de elementos que hay que leer de arraystring y guardar en el arbol rojo y negro
 * @param pasoPrueba pasoPrueba es la cantidad de elementos por prueba
 * @param cantidadPruebas cantidadPruebas es la cantidad de pruebas que hay que realizar
 * @return El metodo devuelve un vector<double> que contiene los cantitdadPruebas tiempos de ejecucion, nos permitiran graficar la evolucion del tiempo
 */
vector<double> probarArbol(const ArbolRojoNegro<string, string>& arbolRojoNegro, string* arrayString, int cantidadElementosLectura, int tamanoBatch, int cantidadBatches)
{
	std::cout << "["; // Mostrar progreso (lado izquierdo de barra de progreso)

	vector<double> tiemposEjecuciones; bool overflowPosible = false;
	for(unsigned int counter1 = 0; counter1 < cantidadBatches && !overflowPosible; ++counter1)
	{
		if(tamanoBatch > (cantidadElementosLectura - (counter1 * tamanoBatch)))  overflowPosible = true;
		else
		{
			auto start = chrono::steady_clock::now();
			for(int counter2 = 0; counter2 < tamanoBatch; ++counter2)
			{
				arbolRojoNegro.find(arrayString[(counter1 * tamanoBatch) + counter2]);
				arbolRojoNegro.find(arrayString[(counter1 * tamanoBatch) + counter2] + string("NoIsE"));
			}
			auto end = chrono::steady_clock::now();

			double tiempoEjecucion = double (chrono::duration_cast<chrono::microseconds>(end-start).count());
			tiemposEjecuciones.push_back(tiempoEjecucion);	//agregar el tiempo al vector de tiempo
		}

		std::cout << "#"; // Mostrar progreso (bloquecito de prueba)
	}

	std::cout << "]" << std::endl; // Mostrar progreso (lado derecho de barra de progreso)

	return tiemposEjecuciones;
}

/**
 * @brief El metodo robarMapSTL permite realizar las pruebas con el map de la STL
 * @param arrayString arrayString es un array que contiene todas las palabras del archivo de texto de input
 * @param cantidadElementosLectura  cantidadElementosLectura es la cantidad de elementos que hay que leer de arraystring y guardar en el map de la STL
 * @param pasoPrueba pasoPrueba es la cantidad de elementos por prueba
 * @param cantidadPruebas cantidadPruebas es la cantidad de pruebas que hay que realizar
 * @return El metodo devuelve un vector<double> que contiene los cantitdadPruebas tiempos de ejecucion, nos permitiran graficar la evolucion del tiempo
 */
vector<double> probarMapSTL(const map<string, string>& mapaSTL, string* arrayString, int cantidadElementosLectura, int tamanoBatch, int cantidadBatches)
{
	std::cout << "["; // Mostrar progreso (lado izquierdo de barra de progreso)

	vector<double> tiemposEjecuciones; bool overflowPosible = false;
	for(unsigned int counter1 = 0; counter1 < cantidadBatches && !overflowPosible; ++counter1)
	{
		if(tamanoBatch > (cantidadElementosLectura - (counter1 * tamanoBatch)))  overflowPosible = true;
		else
		{
			auto start = chrono::steady_clock::now();
			for(int counter2 = 0; counter2 < tamanoBatch; ++counter2)
			{
				mapaSTL.find(arrayString[counter1*tamanoBatch + counter2]);
				mapaSTL.find(arrayString[counter1*tamanoBatch + counter2] + string("NoIsE"));
			}
			auto end = chrono::steady_clock::now();

			double tiempoEjecucion = double (chrono::duration_cast<chrono::microseconds>(end-start).count());
			tiemposEjecuciones.push_back(tiempoEjecucion);	//agregar el tiempo al vector de tiempo
		}

		std::cout << "#"; // Mostrar progreso (bloquecito de prueba)
	}

	std::cout << "]" << std::endl; // Mostrar progreso (lado izquierdo de barra de progreso)

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
vector<double> probarVectorSTL(const vector<pair<string, string>>& vectorSTL, string* arrayString, int cantidadElementosLectura, int tamanoBatch, int cantidadBatches)
{
	Predicado::init();

	std::cout << "["; // Mostrar progreso (lado izquierdo de barra de progreso)

	//Hacer la busqueda
	vector<double> tiempos; bool posibleOverflow = false;
	for(unsigned int i=0; i < cantidadBatches&& !posibleOverflow; ++i)
    {
		if(tamanoBatch > (cantidadElementosLectura - (i * tamanoBatch)))  posibleOverflow = true;
		else
		{
			auto start = chrono::steady_clock::now();
			for(int j = 0; j < tamanoBatch; ++j)
			{	
				string palabraBuscada = arrayString[j + i*tamanoBatch];

				Predicado::setObjetivo(palabraBuscada);
				find_if(vectorSTL.begin(), vectorSTL.end(), Predicado::existe);

				Predicado::setObjetivo(palabraBuscada + string("NoIsE"));
				find_if(vectorSTL.begin(), vectorSTL.end(), Predicado::existe);
			}
			auto end = chrono::steady_clock::now();

			double tiempoEjecucion = double(chrono::duration_cast<chrono::microseconds>(end-start).count());
			tiempos.push_back(tiempoEjecucion);
		}

		std::cout << "#"; // Mostrar progreso (bloquecito de prueba)
	}

	std::cout << "]" << std::endl; // Mostrar progreso (lado izquierdo de barra de progreso)

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

vector<pair<string,string>> generarVectorParejasString(string* arrayString, int cantidadElementosLectura)
{
	vector<pair<string,string>> vectorSTL;

	//Llenar el vector palabras
	for(int i=0; i< cantidadElementosLectura-1; ++i){ //Se revisa si la palabra ya esta en el vector
		if(!existe(arrayString[i], vectorSTL)){
			vectorSTL.push_back(pair<string,string>(arrayString[i],arrayString[i+1]));
		}
	}

	if(!existe(arrayString[cantidadElementosLectura-1], vectorSTL)){ //La ultima palabra se añade junto con una palabra nula
		vectorSTL.push_back(pair<string,string>(arrayString[cantidadElementosLectura-1],string("")));
	}

	return vectorSTL;
}

map<string, string> generarMapaParejasString(string* arrayString, int cantidadElementosLectura)
{
	map <string,string> mapSTL;
	int counter_b=0;
	//llenar el mapa, investigando parejas hasta la penúltima palabra con la última
	while(counter_b<cantidadElementosLectura-1){
		if(mapSTL.find(arrayString[counter_b]) == mapSTL.end()){		// la llave aun no existe en el map
			mapSTL[arrayString[counter_b]] = arrayString[counter_b+1];
		}														// la llave ya existe en el map
		++counter_b;	//que la palabra ya existe o no en el map de toda manera se incrementa el contador
	}

	// el caso de la última palabra es especial. si no existe previamente en el mapa, se asocia con una palabra vacía
	if(mapSTL.find(arrayString[cantidadElementosLectura-1]) == mapSTL.end())
	mapSTL[arrayString[cantidadElementosLectura-1]] = string("");

	return mapSTL;
}

ArbolRojoNegro<string, string> generarArbolRojoNegroParejasString(string* arrayString, int cantidadElementosLectura)
{
	ArbolRojoNegro<string,string> arbolRojoNegro;

	int counter0=0;
	//llenar el arbol, investigando parejas hasta la penúltima palabra con la última
	while(counter0<cantidadElementosLectura-1){
		if(arbolRojoNegro.find(arrayString[counter0]) == arbolRojoNegro.end()){        // la llave aun no existe en el map
			arbolRojoNegro.insertarDato(arrayString[counter0], arrayString[counter0+1]);
		}                                                        // la llave ya existe en el map
		++counter0;    //que la palabra ya existe o no en el map de toda manera se incrementa el contador
	}

	// el caso de la ultima palabra es especial. si no existe previamente en el arbol, se asocia con una palabra vacía
	if(arbolRojoNegro.find(arrayString[cantidadElementosLectura-1]) == arbolRojoNegro.end())
	arbolRojoNegro.insertarDato(arrayString[cantidadElementosLectura-1], string(""));

	return arbolRojoNegro;
}

void tabularPromedios(string* arrayString, int cantidadElementosLectura, int pasoPruebaInicial, int cantidadExperimentos)
{
	ArbolRojoNegro<string, string> arbolRojoNegro = move(generarArbolRojoNegroParejasString(arrayString, cantidadElementosLectura));
	map<string, string> mapSTL = move(generarMapaParejasString(arrayString, cantidadElementosLectura));
	vector<pair<string,string>> vectorSTL = move(generarVectorParejasString(arrayString, cantidadElementosLectura));

	std::cout << "VectorSTL" << '\t' << "MapaSTL" << '\t' << "ArbolRojiNegro" << std::endl << scientific << setprecision(5);
	for(unsigned long long i = 0; i < cantidadExperimentos; ++i)
	{
		int pasoPruebaActual = (i+1)*pasoPruebaInicial;
		double promedioVecSTL = promediarTiempos(probarVectorSTL(vectorSTL, arrayString, cantidadElementosLectura, pasoPruebaActual, 10));
		double promedioMapSTL = promediarTiempos(probarMapSTL(mapSTL, arrayString, cantidadElementosLectura, pasoPruebaActual, 10));
		double promedioArbolRojoNegro = promediarTiempos(probarArbol(arbolRojoNegro, arrayString, cantidadElementosLectura, pasoPruebaActual, 10));

		std::cout << promedioVecSTL << '\t' << promedioMapSTL << '\t' << promedioArbolRojoNegro << std::endl;
	}

	return;
}

/**
 * @brief El metodo main maneja todo el programa y llama los metodos necesarios para el buen desarrollo del programa
 */
int main()
{
	int cantidadElementosLectura;		// cantidad de palabras que hay que leer del archivo y guardar en la data structures
	cin>>cantidadElementosLectura;		
	int pasoPruebaInicial;						// cantidad de palabras que hay que probar por pruebas
	cin>>pasoPruebaInicial;
	int cantidadPruebas;				// cantidad de pruebas que hay que hacer 
	cin>>cantidadPruebas;
	string nombreArchivo;  				//"datos.txt"	--> nombre del archivo que hay que leer 
	cin>>nombreArchivo;

	cout << "PARAMETROS : " << endl
	<< "cantidadElementosLectura = " << cantidadElementosLectura << endl
	<< "pasoPruebaInicial = " << pasoPruebaInicial << endl
	<< "cantidadPruebas = " << cantidadPruebas << endl
	<< "nombreArchivo = " << nombreArchivo << endl;
	
    string *arrayString = new string[cantidadElementosLectura];
    lector(arrayString, nombreArchivo, cantidadElementosLectura);

	tabularPromedios(arrayString, cantidadElementosLectura, pasoPruebaInicial, cantidadPruebas);

    delete[] arrayString;
    return 0;
}