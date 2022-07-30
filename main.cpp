#include "ArbolRojoNegro.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>						//para medir tiempo
#include "Predicado.h"					//para el prueba vector

using namespace std;

int main()
{
	int cantidadElementosLectura;		// cantidad de palabras que hay que leer del archivo y guardar en la data structures
	cin>>cantidadElementosLectura;		
	int pasoPrueba;						// cantidad de palabras que hay que probar por pruebas
	cin>>pasoPrueba;
	int cantidadPruebas;				// cantidad de pruebas que hay que hacer 
	cin>>cantidadPruebas;
	string nombreArchivo;  				//"datos.txt"	--> nombre del archivo que hay que leer 
	cin>>nombreArchivo;
	
    string *arrayString = new string[cantidadElementosLectura];
    lector(arrayString, nombreArchivo);

	//se guarda todos los tiempos de ejecución en vectores
	vector<int> resultadoArbolRojoNegro (cantidadPruebas) = probarArbol(arrayString,cantidadElementosLectura, pasoPrueba, cantidadPruebas);
	vector<int> resultadoMapSTL (cantidadPruebas) = probarMapSTL(arrayString,cantidadElementosLectura, pasoPrueba, cantidadPruebas);
	vector<int> resultadoVectorSTL (cantidadPruebas) = probarVectorSTL(arrayString,cantidadElementosLectura, pasoPrueba, cantidadPruebas);

	//guardamos los resultados en una .txt
	
    delete[] arrayString;
    return 0;
}

//#############################################################################################################################

void lector(string* arrayString, string nombreArchivo)
{
    string word;
    ifstream file;

    file.open(nombreArchivo);
    unsigned int counter = 0;

    while(file.eof())
    {
        file >> word;
        arrayString[counter] = word;
        ++counter;
    }
}

//#############################################################################################################################

vector<int> probarArbol(string *arrayString, int cantidadElementosLectura, pasoPrueba, cantidadPruebas)
{
}

//#############################################################################################################################
	
vector<double> probarMapSTL(string *arrayString, int cantidadElementosLectura, int pasoPrueba, int cantidadPruebas)
{
	map <string,string> mapSTL;
	int counter0=0;
	//llenar el mapa
	while(counter0<cantidadElementosLectura){
		if(mapSTL.find(arrayString[counter0]) == mapSTL.end()){		// la llave aun no existe en el map
			map[arrayString[counter0]] = arrayString[counter0+1];
		} else{														// la llave ya existe en el map
		}
		counter++;	//que la palabra ya existe o no en el map de toda manera se incrementa el contador
	}
	
	vector<double> tiemposEjecuciones (cantidadPruebas);
	
	counter1 = 0;
	while(counter1< cantidadPruebas*pasoPrueba){
		auto start = chrono::steady_clock::now();
		counter0 = 0;
		while(counter0<pasoPruebas)
		{	
			mapSTL.find(arrayString[counter1]);
			string NoIsE = arrayString[counter1] + "NoIsE";
			++counter0;
			++counter1;
		}
		
		auto end = chrono::steady_clock::now();
		double tiempoEjecucion = double (chrono::duration_cast<chrono::nanoseconds>(end-start).count());
		
		tiemposEjecuciones.push_back(tiempoEjecucion);	//agregar el tiempo al vector de tiempo
	}
	return tiemposEjecuciones;
}

//#############################################################################################################################

vector<double> probarVectorSTL(string * arrayString, int cantidadElementosLectura, int pasoPrueba, int cantidadPruebas)
{
	Predicado predicado;
	vector<pair<string,string>> palabras;
	//Llenar el vector palabras
	for(int i=0; i< cantidadElementosLectura-2; ++i){ //Se revisa si la palabra ya esta en el vector
		if(!existe(arrayString, palabras)){
			palabras.push_back(pair<string,string>(arrayString[i]),arrayString[i+1]);
		}
	}
	if(!existe(arrayString[cantidadElementosLectura-1], palabras)){ //La ultima palabra se añade junto con una palabra nula
		palabras.push_back(pair<string,string>(arrayString[cantidadElementosLectura-1],0));
	}
	//Hacer la busqueda
	vector<double> tiempos;
	for(int i=0; i < cantidadPruebas; ++i){
		auto start = chrono::steady_clock::now();
		//codigo
		auto it = find_if(palabras.begin(), palabras.end(), predicado.existe);
		auto end = chrono::steady_clock::now();
		double tiempoEjecucion = double(chrono::duration_cast<chrono::nanoseconds>(end-start).count());
		tiempos.push_back(tiempoEjecucion);
	}
	return tiempos;
}

int existe(string * arrayString, vector<string,string> palabras){
	int existe = 0;
	for(auto i = palabras.begin(); i != palabras.end(); ++i){
		if(arrayString[i] == get<0>(palabras[i])){
			existe = 1; //Sí esta en el vector
		}
	}
	return existe;
}