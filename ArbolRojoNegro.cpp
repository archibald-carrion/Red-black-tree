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

ArbolRojoNegro::Nodo::Nodo(Connector *hijoDerecho, Connector* hijoIzquierdo, char color, int llaveTemporal)
{
    this->llave = llaveTemporal;
    this->tipo = tipoNodo;
    this->hijos[ladoIzquierdo] = hijoIzquierdo;
    this->hijos[ladoDerecho] = hijoDerecho;
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
    raiz = 0;
}

ArbolRojoNegro::~ArbolRojoNegro()
{
    //desctructor recursivo
}

int ArbolRojoNegro::insertarDato(int valor, int llave)
{
    Hoja *dato = new Hoja(valor, llave);
    
    //recorrer el arbol, hacer el color flip si se occupa, sino, no
    //insertarHoja
    //verificar que sea un arbol RN
    //si no lo es entonces hacer rotacion y arreglar colores

    //caso trivial 1 -> arbol vacio
    if(raiz == 0){
        raiz = (Connector*)dato;
        return 1;
    }
    //caso trivial 2 -> arbol solo tiene 1 hoja
    if(raiz->tipo == Connector::tipoHoja){
        int nuevaLlave;
        Nodo* nodo ;
        if(raiz->llave > llave){
            nodo = new Nodo(dato, raiz, Connector::negro, llave);
        } else{
            nodo = new Nodo(raiz, dato, Connector::negro, raiz->llave);
        } 
        raiz = nodo;
        return 1;
    }
    //caso trivial 3 -> llave ya existe en la raiz
    

    Nodo* nodo = static_cast<Nodo*>(raiz);
    
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

int ArbolRojoNegro::insertarDatoRecursivo(Hoja*, Connector*){

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