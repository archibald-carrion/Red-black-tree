#include "ArbolRojoNegro.h"

ArbolRojoNegro::Connector::~Connector()
{
}

void ArbolRojoNegro::Nodo::colorFlip()
{
}

ArbolRojoNegro::Nodo::Nodo(Nodo *)
{
}

ArbolRojoNegro::Nodo::Nodo(Connector *losHijos[2], char color, int llaveTemporal)
{
    this->llave = llaveTemporal;
    this->tipo = tipoNodo;
    this->hijos[hijoIzquierdo] = losHijos[hijoIzquierdo];
    this->hijos[hijoDerecho] = losHijos[hijoDerecho];
    this->color = color;
}

ArbolRojoNegro::Hoja::Hoja(int valorTemporal, int llaveTemporal)
{
    this->valor = valorTemporal;
    this->llave = llaveTemporal;
    this->tipo = tipoHoja;
}

ArbolRojoNegro::Iterador::Iterador(Connector *)
{
}

ArbolRojoNegro::Iterador::Iterador(const Iterador &)
{
}

ArbolRojoNegro::Iterador ArbolRojoNegro::Iterador::operator=(const Iterador &)
{
}

void ArbolRojoNegro::Iterador::operator==(const Iterador &)
{
}

ArbolRojoNegro::Iterador ArbolRojoNegro::Iterador::operator++()
{
}

ArbolRojoNegro::Iterador ArbolRojoNegro::Iterador::operator--()
{
}
ArbolRojoNegro::Hoja *ArbolRojoNegro::Iterador::operator*()
{
}

ArbolRojoNegro::ArbolRojoNegro()
{
}

ArbolRojoNegro::~ArbolRojoNegro()
{
}

int ArbolRojoNegro::insertarDato(int valor, int llave)
{
    Hoja *dato = new Hoja(valor, llave);
    //recorrer el arbol, hacer el color flip si se occupa, sino, no
    //insertarHoja
    //verificar que sea un arbol RN
    //si no lo es entonces hacer rotacion y arreglar colores
}

void ArbolRojoNegro::CCR(Nodo *)
{
}

void ArbolRojoNegro::CF(Nodo *)
{
}

void ArbolRojoNegro::RSI(Nodo *)
{
}

void ArbolRojoNegro::RSD(Nodo *)
{
}

void ArbolRojoNegro::RDI(Nodo *)
{
}

void ArbolRojoNegro::RDD(Nodo *)
{
}

void ArbolRojoNegro::RC(Nodo *)
{
}

void ArbolRojoNegro::IH(Hoja *)
{
}

ArbolRojoNegro::Iterador ArbolRojoNegro::begin()
{
}

ArbolRojoNegro::Iterador ArbolRojoNegro::end()
{
}