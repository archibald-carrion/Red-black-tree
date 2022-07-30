#include "ArbolRojoNegro.h"
#include <iostream>
#include <fstream>

#include <algorithm>
#include <vector>
#include <map>
#include <string>

#include <chrono>						//para medir tiempo
#include "Predicado.h"					//para el prueba vector

using namespace std;

int existe(string arrayString, vector<pair<string,string>> palabras){
	int existe = 0;
	for(auto i = palabras.begin(); i != palabras.end(); ++i){
		if(arrayString == i->first){
			existe = 1; //Sí esta en el vector
		}
	}
	return existe;
}

//#############################################################################################################################

vector<double> probarArbol(string *arrayString, int cantidadElementosLectura, int pasoPrueba, int cantidadPruebas)
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
			mapSTL[arrayString[counter0]] = arrayString[counter0+1];
		} else{														// la llave ya existe en el map
		}
		++counter0;	//que la palabra ya existe o no en el map de toda manera se incrementa el contador
	}
	
	vector<double> tiemposEjecuciones (cantidadPruebas);
	
	int counter1 = 0;
	while(counter1< cantidadPruebas*pasoPrueba){
		auto start = chrono::steady_clock::now();
		counter0 = 0;
		while(counter0<pasoPrueba)
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
	vector<pair<string,string>> palabras;

    Predicado::init();
    Predicado::setup(pasoPrueba, arrayString, palabras);

	//Llenar el vector palabras
	for(int i=0; i< cantidadElementosLectura-2; ++i){ //Se revisa si la palabra ya esta en el vector
		if(!existe(arrayString[i], palabras)){
			palabras.push_back(pair<string,string>(arrayString[i],arrayString[i+1]));
		}
	}
	if(!existe(arrayString[cantidadElementosLectura-1], palabras)){ //La ultima palabra se añade junto con una palabra nula
		palabras.push_back(pair<string,string>(arrayString[cantidadElementosLectura-1],0));
	}
	//Hacer la busqueda
	vector<double> tiempos;
	for(int i=0; i < cantidadPruebas; ++i)
    {
        string palabraBuscada = arrayString[i];
        Predicado::setObjetivo(palabraBuscada);

        //codigo
		auto start = chrono::steady_clock::now();
		auto it = find_if(palabras.begin(), palabras.end(), Predicado::existe);
		auto end = chrono::steady_clock::now();
		double tiempoEjecucion = double(chrono::duration_cast<chrono::nanoseconds>(end-start).count());
		tiempos.push_back(tiempoEjecucion);
	}
	return tiempos;
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

void probarArbol_s()
{
    ArbolRojoNegro arbolito;

    for(unsigned int i = 0; i < 8; ++i)
    {
        int valor = 0;
        int llave = 0;

        std::cin>>valor;
        std::cin>>llave;

        std::cout << "Dato a insertar es " << valor << " , llave es " << llave << std::endl;
        arbolito.insertarDato(valor, llave);
    }

    std::cout << "\n";
    
    for(ArbolRojoNegro::Iterador i = arbolito.begin(); i != arbolito.end(); ++i)
    {
        std::cout << "==============" << std::endl;

        std::cout << "*I es " << *i << std::endl;

        ArbolRojoNegro::Iterador i_sig = ArbolRojoNegro::Iterador(i); ++i_sig;
        ArbolRojoNegro::Iterador i_previo = ArbolRojoNegro::Iterador(i); --i_previo;

        std::cout << "I++ es ";
        if(i_sig == arbolito.end()) std::cout << "NULO" << std::endl;
        else std::cout << *i_sig << std::endl;

        std::cout << "I-- es ";
        if(i_previo == arbolito.end()) std::cout << "NULO" << std::endl;
        else std::cout << *i_previo << std::endl;
    }

    std::cout << "///////////////////////" << std::endl;

    for(ArbolRojoNegro::Iterador i = arbolito.begin(); i != arbolito.end(); ++i)
    {std::cout << *i << " " << std::endl;}

    std::cout << "///////////////////////" << std::endl;

    for(unsigned int i = 0; i < 8; ++i)
    {
        int llaveBusqueda = 0;
        std::cin>>llaveBusqueda;

        std::cout << "Llave de busqueda es " << llaveBusqueda << std::endl;
        ArbolRojoNegro::Iterador match = arbolito.find(llaveBusqueda);

        if(match == arbolito.end()) std::cout << "No se encontro nada" << std::endl;
        else std::cout << "Se encontro! Su valor asociado es " << *match << std::endl;
    }
}

int main()
{

    probarArbol_s();

    /* PROGRAMA PRINCIPAL
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
	vector<double> resultadoArbolRojoNegro = probarArbol(arrayString,cantidadElementosLectura, pasoPrueba, cantidadPruebas);
	vector<double> resultadoMapSTL = probarMapSTL(arrayString,cantidadElementosLectura, pasoPrueba, cantidadPruebas);
	vector<double> resultadoVectorSTL = probarVectorSTL(arrayString,cantidadElementosLectura, pasoPrueba, cantidadPruebas);

	//guardamos los resultados en una .txt
	
    delete[] arrayString;
    */

    return 0;
}


//#############################################################################################################################

