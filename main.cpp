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

