#include "ArbolRojoNegro.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int main()
{
    string *arrayString = new string[39151187];
    string nombreArchivo = "datos.txt";
    lector(arrayString, nombreArchivo);

    //llenar arbolRojoNegro nuestro

    //llenar arbolRojoNegro STL

    //llenar vector STL

    //guardamos en archivo de texto

    delete[] arrayString;
    return 0;
}

void lector(string *arrayString, string nombreArchivo)
{
    string word;
    ifstream file;
    file.open(nombreArchivo);
    unsigned int counter = 0;
    while(!file.eof())
    {
        file>>word;
        arrayString[counter] = word;
        ++counter;
    }
}
