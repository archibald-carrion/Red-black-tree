#include "ArbolRojoNegro.h"

// NODO

void ArbolRojoNegro::Nodo::colorFlipLocal()
{
    if(this->color == (char)0) this->color = (char)1;
    else this->color = (char)0; 

    return;
}

ArbolRojoNegro::Nodo::Nodo(Connector* hijoIzquierdo, Connector *hijoDerecho, char color, int llaveTemporal)
{
    this->llave = llaveTemporal;
    this->tipo = tipoNodo;
    this->hijos[ladoIzquierdo] = hijoIzquierdo;
    this->hijos[ladoDerecho] = hijoDerecho;
    this->color = color;
}

// HOJA

ArbolRojoNegro::Hoja::Hoja(const int& valorTemporal, const int& llaveTemporal, Hoja* next, Hoja* previous)
{
    this->valor = valorTemporal;
    this->llave = llaveTemporal;

    this->next = next;
    this->previous = previous;

    this->tipo = tipoHoja;
}

// ITERADOR

ArbolRojoNegro::Iterador::Iterador(Hoja* hojaIterable)
{this->actual = hojaIterable;}

ArbolRojoNegro::Iterador::Iterador(const Iterador& iteradorCopiable)
{this->actual = iteradorCopiable.actual;}

ArbolRojoNegro::Iterador ArbolRojoNegro::Iterador::operator=(const Iterador& iteradorCopiable)
{this->actual = iteradorCopiable.actual;}

bool ArbolRojoNegro::Iterador::operator==(const Iterador& iteradorComparable)
{return (this->actual == iteradorComparable.actual);}

ArbolRojoNegro::Iterador ArbolRojoNegro::Iterador::operator++()
{actual = actual->next;}

ArbolRojoNegro::Iterador ArbolRojoNegro::Iterador::operator--()
{actual = actual->previous;}

const int& ArbolRojoNegro::Iterador::operator*()
{return this->actual->valor;}

ArbolRojoNegro::Iterador ArbolRojoNegro::begin()
{return Iterador(hojaMinima);}

ArbolRojoNegro::Iterador ArbolRojoNegro::end()
{return Iterador(0);}

// ARBOL ROJO-NEGRO

ArbolRojoNegro::ArbolRojoNegro()
{
    raiz = 0;
    hojaMinima = 0;
}

ArbolRojoNegro::~ArbolRojoNegro()
{
    // Desctructor recursivo, en cadena
    if(raiz) delete raiz;
}

int ArbolRojoNegro::insertarDato(const int& valor, const int& llave)
{
    // Recorrer el arbol, hacer el color flip si se occupa, sino, no
    // InsertarHoja
    // Verificar que sea un arbol RN
    // Si no lo es entonces hacer rotacion y arreglar colores

    // Caso trivial 1 -> Arbol vacio
    if(raiz == 0)
    {
        Hoja *dato = new Hoja(valor, llave);

        raiz = (Connector*) dato;
        hojaMinima = dato;

        return 1;
    }

    // Caso trivial 2 -> Llave ya existe en la raiz. Comparacion es segura porque raiz no es nula (caso trivial 1)
    if(raiz->llave == llave) return 0;
    
    // Caso trivial 3 -> Arbol solo tiene 1 hoja. 
    // Comparacion es necesaria porque raiz tiene llave distinta (caso trivial 2), y es segura porque raiz no es nula (caso trivial 1)
    if(raiz->tipo == Connector::tipoHoja)
    {
        Hoja *dato = new Hoja(valor, llave);

        Nodo* nodo;

        if(raiz->llave > llave) 
        {
            nodo = new Nodo(dato, raiz, Connector::negro, llave);
            hojaMinima = dato;
        }
        else 
        {
            nodo = new Nodo(raiz, dato, Connector::negro, raiz->llave);
            hojaMinima = dynamic_cast<Hoja*>(raiz); // Casting es seguro porque raiz era una Hoja
        }

        raiz = (Connector*) nodo;
        return 1;
    }

    // Casting es seguro, confirmamos que raiz no es nula (caso trivial 1) y es nodo (caso trivial 3)
    Nodo* nodoActual = static_cast<Nodo*>(raiz);
    char ladoActual = 0;
    
    // Conocemos si debemos mover a la izquierda o derecha. La comparación es segura porque porque raíz no es nula (caso trivial 1)
    // Confirmamos que si no es mayor entonces es menor. No puede ser igual (caso trivial 2)
    if(llave < raiz->llave) ladoActual = Nodo::ladoIzquierdo;
    else ladoActual = Nodo::ladoDerecho;

    // Caso semi-trivial -> Connector siguiente es Hoja
    if(nodoActual->hijos[ladoActual]->tipo == Connector::tipoHoja)
    {}
    
}

int ArbolRojoNegro::IH_recursivo(const int& valor, const int& llave, Connector* actual)
{

}

//se pasa la raiz a negro
void ArbolRojoNegro::CCR()
{
	dynamic_cast<Nodo*>(raiz) -> colorFlipLocal();
}

//se cambia color padre rojo y hijos a negro
void ArbolRojoNegro::CF(Nodo **padre)
{   
    Nodo* nodoPadre = dynamic_cast<Nodo*>(*padre);
	nodoPadre -> colorFlipLocal();
    if(nodoPadre->hijos[0]->tipo == Connector::tipoNodo){
	    dynamic_cast<Nodo*>(nodoPadre->hijos[0]) -> colorFlipLocal();
    }
    if(nodoPadre->hijos[1]->tipo == Connector::tipoNodo){
	    dynamic_cast<Nodo*>(nodoPadre->hijos[1]) -> colorFlipLocal();
    }
}

void ArbolRojoNegro::RSI(Nodo ** bis)
{
}

void ArbolRojoNegro::RSD(Nodo ** bis)
{
}

void ArbolRojoNegro::RDI(Nodo ** bis)
{
}

void ArbolRojoNegro::RDD(Nodo ** bis)
{
}

//se cambia color padre para negro y colro hjijos para rojo
void ArbolRojoNegro::RC(Nodo **padre)
{
    Nodo* nodoPadre = dynamic_cast<Nodo*>(*padre);
    nodoPadre -> color = Connector::negro;
    if(nodoPadre->hijos[0]->tipo == Connector::tipoNodo){
	    dynamic_cast<Nodo*>(nodoPadre->hijos[0]) -> color = Connector::rojo;
    }
    if(nodoPadre->hijos[1]->tipo == Connector::tipoNodo){
	    dynamic_cast<Nodo*>(nodoPadre->hijos[1]) -> color = Connector::rojo;
    }
}