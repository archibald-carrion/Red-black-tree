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

ArbolRojoNegro::Hoja::Hoja(const int& valorTemporal, const int& llaveTemporal)
{
    this->valor = valorTemporal;
    this->llave = llaveTemporal;

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
{
}

ArbolRojoNegro::Iterador ArbolRojoNegro::Iterador::operator--()
{
}

const int& ArbolRojoNegro::Iterador::operator*()
{return this->actual->valor;}

// ARBOL ROJO-NEGRO

ArbolRojoNegro::ArbolRojoNegro()
{raiz = 0;}

ArbolRojoNegro::~ArbolRojoNegro()
{
    //desctructor recursivo
}

int ArbolRojoNegro::insertarDato(const int& valor, const int& llave)
{
    //recorrer el arbol, hacer el color flip si se occupa, sino, no
    //insertarHoja
    //verificar que sea un arbol RN
    //si no lo es entonces hacer rotacion y arreglar colores

    // Caso trivial 1 -> Llave ya existe en la raiz
    if(raiz->llave == llave) return 0;

    Hoja *dato = new Hoja(valor, llave);

    // Caso trivial 2 -> Arbol vacio
    if(raiz == 0)
    {
        raiz = (Connector*) dato;
        return 1;
    }
    
    // Caso trivial 3 -> Arbol solo tiene 1 hoja
    if(raiz->tipo == Connector::tipoHoja)
    {
        Nodo* nodo;

        if(raiz->llave > llave) nodo = new Nodo(dato, raiz, Connector::negro, llave); 
        else nodo = new Nodo(raiz, dato, Connector::negro, raiz->llave);

        raiz = (Connector*) nodo;
        return 1;
    }

    Nodo* nodo = static_cast<Nodo*>(raiz); // Casting es seguro, confirmamos que raiz es nodo
    
    if(raiz->llave > llave){        //move to right
        
        if(nodo->hijos[Nodo::ladoDerecho]){
            return insertarDatoRecursivo(dato, nodo->hijos[Nodo::ladoDerecho]);
        } else{
            nodo->hijos[Nodo::ladoDerecho] = dato;
            return 1;
        }  

    } else if(raiz->llave < llave){  
                               //move to left
        if(nodo->hijos[Nodo::ladoIzquierdo]){
            return insertarDatoRecursivo(dato, nodo->hijos[Nodo::ladoIzquierdo]);
        } else{
            nodo->hijos[Nodo::ladoIzquierdo] = dato;
            return 1;
        }

    } else{
        return 0;
    }
}

int ArbolRojoNegro::insertarDatoRecursivo(Hoja* dato, Connector* actual)
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


void ArbolRojoNegro::IH(Hoja *)
{
}

ArbolRojoNegro::Iterador ArbolRojoNegro::begin()
{
}

ArbolRojoNegro::Iterador ArbolRojoNegro::end()
{
}