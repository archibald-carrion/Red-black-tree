#include "ArbolRojoNegro.h"
#include <iostream>
// NODO

void ArbolRojoNegro::Nodo::colorFlipLocal()
{
    if(this->color == (char)0) this->color = (char)1;
    else this->color = (char)0; 

    return;
}

ArbolRojoNegro::Nodo::Nodo(Hoja* hoja_A, Hoja* hoja_B, char color)
{
    this->tipo = tipoNodo;
    this->color = color;

    if(hoja_A == 0 || hoja_B == 0) this->llave = int();
    else if(hoja_A->llave < hoja_B->llave) 
    {
        this->llave = hoja_A->llave;

        this->hijos[ladoIzquierdo] = hoja_A;
        this->hijos[ladoDerecho] = hoja_B;

        hoja_A->previous = hoja_B->previous;
        if(hoja_B->previous != 0) hoja_B->previous->next = hoja_A;

        hoja_A->next = hoja_B;
        hoja_B->previous = hoja_A;
    }
    else 
    {
        this->llave = hoja_B->llave;

        this->hijos[ladoDerecho] = hoja_A;
        this->hijos[ladoIzquierdo] = hoja_B;

        hoja_B->previous = hoja_A->previous;
        if(hoja_A->previous != 0) hoja_A->previous->next = hoja_B;
        
        hoja_A->previous = hoja_B;
        hoja_B->next = hoja_A;
    }
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

ArbolRojoNegro::Iterador& ArbolRojoNegro::Iterador::operator=(const Iterador& iteradorCopiable)
{
    this->actual = iteradorCopiable.actual;
    return *this;
}

bool ArbolRojoNegro::Iterador::operator==(const Iterador& iteradorComparable)
{return (this->actual == iteradorComparable.actual);}

bool ArbolRojoNegro::Iterador::operator!=(const Iterador& iteradorComparable)
{return (this->actual != iteradorComparable.actual);}

ArbolRojoNegro::Iterador& ArbolRojoNegro::Iterador::operator++()
{
    actual = actual->next;
    return *this;
}

ArbolRojoNegro::Iterador ArbolRojoNegro::Iterador::operator++(int x)
{
    Iterador copia(*this);
    actual = actual->next;
    return copia;
}

ArbolRojoNegro::Iterador& ArbolRojoNegro::Iterador::operator--()
{
    actual = actual->previous;
    return *this;
}

ArbolRojoNegro::Iterador ArbolRojoNegro::Iterador::operator--(int x)
{
    Iterador copia(*this);
    actual = actual->previous;
    return copia;
}

const int& ArbolRojoNegro::Iterador::operator*()
{return this->actual->valor;}

// ARBOL ROJO-NEGRO

ArbolRojoNegro::Iterador ArbolRojoNegro::begin()
{return Iterador(hojaMinima);}

ArbolRojoNegro::Iterador ArbolRojoNegro::end()
{return Iterador(0);}

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
        Hoja* nuevaHoja = new Hoja(valor, llave);

        raiz = (Connector*) nuevaHoja;
        hojaMinima = nuevaHoja;

        return 1;
    }

    // Caso trivial 2 -> Llave ya existe en la raiz. Comparacion es segura porque raiz no es nula (caso trivial 1)
    if(raiz->llave == llave) return 0;
    
    // Caso trivial 3 -> Arbol solo tiene 1 hoja. 
    // Comparacion es necesaria porque raiz tiene llave distinta (caso trivial 2), y es segura porque raiz no es nula (caso trivial 1)
    if(raiz->tipo == Connector::tipoHoja)
    {
        Hoja* nuevaHoja = new Hoja(valor, llave);
        Hoja* raizComoHoja = dynamic_cast<Hoja*>(raiz); // Casting es seguro porque raiz era una Hoja
        Nodo* nuevoNodo;

        // En ambos casos el nuevo nodo raíz será negro de una vez
        nuevoNodo = new Nodo(nuevaHoja, raizComoHoja, Connector::negro);

        if(llave < raiz->llave) hojaMinima = nuevaHoja;
        else hojaMinima = raizComoHoja;

        raiz = (Connector*) nuevoNodo;
        return 1;
    }

    // Casting es seguro, confirmamos que raiz no es nula (caso trivial 1) y es nodo (caso trivial 3)
    Nodo* nodoActual = dynamic_cast<Nodo*>(raiz);
    char ladoActual = 0;
    
    // Conocemos si debemos mover a la izquierda o derecha. La comparación es segura porque porque raíz no es nula (caso trivial 1)
    // Confirmamos que si no es mayor entonces es menor. No puede ser igual (caso trivial 2)
    if(llave < raiz->llave) ladoActual = Nodo::ladoIzquierdo;
    else ladoActual = Nodo::ladoDerecho;

    // Por estructura del árbol, se garantiza que los hijos de un nodo jamás serán nulos
    // Quizás deberíamos poner código defensivo aquí, por si acaso
    Connector* connectorHijoActual = nodoActual->hijos[ladoActual];

    // Caso semi-trivial -> Connector siguiente es Hoja
    if(connectorHijoActual->tipo == Connector::tipoHoja)
    {
        // Subcaso trivial del caso semi-trivial -> Llave ya existe. 
        // Comparacion se asume segura porque el hijo connector se asume que no es nulo
        if(connectorHijoActual->llave == llave) return 0;

        Hoja* nuevaHoja = new Hoja(valor, llave);
        Hoja* hojaHijaActual = dynamic_cast<Hoja*>(connectorHijoActual);
        Nodo* nuevoNodo = new Nodo(hojaHijaActual, nuevaHoja, Connector::rojo);

        nodoActual->hijos[ladoActual] = (Connector*) nuevoNodo;
        if(llave < hojaMinima->llave) hojaMinima = nuevaHoja;

        return 1;
    }

    // Caso de solución iterativa -> Connector siguiente es un nodo
    // Casting cada ciclo es seguro, porque se garantiza que el conector siguiente es un nodo

    // Vamos a descender en el árbol hasta el hijo correspondiente al nodo actual sea una hoja
    unsigned char bandera = 0; // Existe un desfase de dos entre el nodo actual y el bisabuelo, no todas las iteraciones determinan el bisabuelo
    Connector** bis = 0; // Ubicación del bisasbuelo
    Connector** bis_desfasado = 0; // Bis desfasado 1 paso
    char lado_desfasado_1 = 0; // Lado desfasado 1 paso
    
    while(connectorHijoActual->tipo == Connector::tipoNodo)
    {
        std::cout << "Es hora de descender!" << std::endl;
        // Antes de descender, verificaremos si ambos hermanos son rojos, si acaso es necesario realizar un color flip en el nodo actual
        Connector* hermanoTemporal;
        if(ladoActual == Nodo::ladoIzquierdo) hermanoTemporal = nodoActual->hijos[Nodo::ladoDerecho];
        else hermanoTemporal = nodoActual->hijos[Nodo::ladoIzquierdo];

        if(hermanoTemporal->tipo == Connector::tipoNodo) // Comparación es segura porque la estructura del árbol evita connectores nulos
        {
            std::cout << "HAY NODO HERMANO" << std::endl;
            // Castings son seguros porque se garantizó que ambos conectores existen y son nodos
            Nodo* nodoHermano = dynamic_cast<Nodo*>(hermanoTemporal);
            Nodo* nodoHijo = dynamic_cast<Nodo*>(connectorHijoActual);

            if(nodoHermano->color == Nodo::rojo && nodoHijo->color == Nodo::rojo) 
            {
                std::cout << "Es hora de hacer color flip!" << std::endl;
                CF(nodoActual);
            }
        }

        // Ahora sí, podemos descender.
        if(bandera == 0) // El primer descenso es especial, está garantizado, y se conoce el bisabuelo, pues es la dirección de la raíz
        {
            std::cout << "-> bandera es 0" << std::endl;
            bis = &raiz;
            lado_desfasado_1 = ladoActual;

            bandera += 1;
        }
        else // El resto de descensos son fácilmente iterables
        {
            std::cout << "-> bandera es > 0" << std::endl;
            bis_desfasado = bis;
            bis = &(dynamic_cast<Nodo*>(*bis_desfasado)->hijos[lado_desfasado_1]);

            lado_desfasado_1 = ladoActual;
        }

        nodoActual = dynamic_cast<Nodo*>(connectorHijoActual);

        std::cout << "-> raiz apunta a " << (*raiz).llave << std::endl;
        std::cout << "-> bis apunta a " << (*bis)->llave << std::endl;
        std::cout << "-> nodo actual es " << nodoActual->llave << std::endl;
        std::cout << "-> hijo izq es " << nodoActual->hijos[Nodo::ladoIzquierdo]->llave << std::endl;
        std::cout << "-> hijo der es " << nodoActual->hijos[Nodo::ladoDerecho]->llave << std::endl;

        if(llave == nodoActual->llave) return 0; // Llave preexistente, no vale la pena seguir bajando

        if(llave < nodoActual->llave) ladoActual = Nodo::ladoIzquierdo;
        else ladoActual = Nodo::ladoDerecho;

        connectorHijoActual = nodoActual->hijos[ladoActual];

        std::cout << "-> hijo actual ahora es " << connectorHijoActual->llave << std::endl;
        std::cout << "-> hijo actual ahora es ";
        if(connectorHijoActual->tipo == Connector::tipoHoja) std::cout << "UNA HOJA" << std::endl;
        else std::cout << "UN NODO" << std::endl;
    }

    std::cout << "Es hora de insertar!" << std::endl;

    // Tenemos que el connector siguiente es una hoja, y podemos realizar una inserción
    if(llave == connectorHijoActual->llave) return 0; // Llave ya preexistente

    Hoja* hojaHijaActual = dynamic_cast<Hoja*>(connectorHijoActual);
    Hoja* nuevaHoja = new Hoja(valor, llave);
    Nodo* nuevoNodo = new Nodo(nuevaHoja, hojaHijaActual, Connector::rojo);

    nodoActual->hijos[ladoActual] = (Connector*) nuevoNodo;
    if(llave < hojaMinima->llave) hojaMinima = nuevaHoja;

    std::cout << "Es hora de verificar rotaciones!" << std::endl;

    // Realizamos la rotación necesaria, si acaso
    char codigoRotacion = verificarRotacion(bis);
    std::cout << "Rotaciones verificadas!" << std::endl;

    switch (codigoRotacion)
    {
        case char(0):
            std::cout << "NO HAY QUE HACER NADA" << std::endl;
            break;

        case char(1):
            std::cout << "-> rotacion simple izquierda" << std::endl;
            RSI(bis);
            break;

        case char(2):
            std::cout << "-> rotacion simple derecha" << std::endl;
            RSD(bis);
            break;

        case char(3):
            std::cout << "-> rotacion doble izquierda" << std::endl;
            RDI(bis);
            break;

        case char(4):
            std::cout << "-> rotacion doble derecha" << std::endl;
            RDD(bis);
            break;
        
        default:
            std::cout << "CODIGO INVALIDO" << std::endl;
            break;
    }

    return 1;
}

//	0-> no rotacion
// 	1-> RSI
//	2-> RSD
//	3-> RDI
//	4-> RDD
char ArbolRojoNegro::verificarRotacion(Connector** bisabuelo)
{
    Nodo* padre = dynamic_cast<Nodo*>(*bisabuelo);

	if(padre->hijos[0] -> tipo == Connector::tipoNodo)
	{					
        Nodo* nodoHijoIzquierdo = dynamic_cast<Nodo*>(padre->hijos[0]);

        if(nodoHijoIzquierdo-> color == Connector::rojo) // Nodo hijo izquierdo es rojo
        {
            if(nodoHijoIzquierdo -> hijos[0] -> tipo == Connector::tipoNodo)
            {				
                Nodo* nietoHijoIzquierdo = dynamic_cast<Nodo*>(nodoHijoIzquierdo->hijos[0]);

                if(nietoHijoIzquierdo-> color == Connector::rojo) return char(2);	// hijo izquierdo del hijo izquierdo es rojo 
                // rotacion simple derecha
            }
            
            else if(nodoHijoIzquierdo -> hijos[1] -> tipo == Connector::tipoNodo)
            {				
                Nodo* nietoHijoDerecho = dynamic_cast<Nodo*>(nodoHijoIzquierdo->hijos[1]);

                if(nietoHijoDerecho-> color == Connector::rojo) return char(4);	// hijo derecho del hijo izquierdo es rojo 
                // rotacion doble derecha
            }
        }
	} 
    
    else if(padre->hijos[1] -> tipo == Connector::tipoNodo)
	{
		Nodo* nodoHijoDerecho = dynamic_cast<Nodo*>(padre->hijos[1]);

        if(nodoHijoDerecho-> color == Connector::rojo) // Nodo hijo derecho es rojo
        {
            if(nodoHijoDerecho -> hijos[0] -> tipo == Connector::tipoNodo)
            {				
                Nodo* nietoHijoIzquierdo = dynamic_cast<Nodo*>(nodoHijoDerecho->hijos[0]);

                if(nietoHijoIzquierdo-> color == Connector::rojo) return char(3);	// hijo izquierdo del hijo derecho es rojo 
                // rotacion doble izquierda
            }
            
            else if(nodoHijoDerecho -> hijos[1] -> tipo == Connector::tipoNodo)
            {				
                Nodo* nietoHijoDerecho = dynamic_cast<Nodo*>(nodoHijoDerecho->hijos[1]);

                if(nietoHijoDerecho-> color == Connector::rojo) return char(1);	// hijo derecho del hijo derecho es rojo 
                // rotacion simple izquierda
            }
            
            else return char(1); // hijo izquierdo es rojo pero nieto no lo es
        }
	} 
    
    // Si ninguna rotación se debe realizar (el criterio de ninguna se cumple completamente) entonces devolvemos 0
    return char(0);
}

//se cambia color padre rojo y hijos a negro
void ArbolRojoNegro::CF(Nodo* padre)
{
    if(padre == 0) return; // Código defensivo

    // Casting se asume seguro porque padre debe ser un nodo
	if(padre != raiz) padre -> colorFlipLocal();

    // Se asume que el árbol minimal de nodos existe, y ningulo de los dos hijos es nulo u hoja
    dynamic_cast<Nodo*>(padre->hijos[0]) -> colorFlipLocal();
    dynamic_cast<Nodo*>(padre->hijos[1]) -> colorFlipLocal();
}

// Rotaciones simples
void ArbolRojoNegro::RSI(Connector** bis)
{
    if(bis == 0) return; // Código defensivo
    Nodo* nodoBis = dynamic_cast<Nodo*>(*bis);

    // Casting se asume seguro porque bisabuelo debe apuntar a un nodo
    Nodo* nuevoPadre = dynamic_cast<Nodo *>(nodoBis->hijos[Nodo::ladoDerecho]);

    // Se asume que la cadena de nodos existe, y ningulo es nulo
    nodoBis->hijos[Nodo::ladoDerecho] = nuevoPadre->hijos[Nodo::ladoIzquierdo];
    nuevoPadre->hijos[0] = (* bis);

    (* bis) = nuevoPadre; std::cout << "RSI EXITOSA" << std::endl;
    RC(nuevoPadre);

    return;
}

void ArbolRojoNegro::RSD(Connector** bis)
{
    if(bis == 0) return; // Código defensivo
    Nodo* nodoBis = dynamic_cast<Nodo*>(*bis);

    // Casting se asume seguro porque bisabuelo debe apuntar a un nodo
    Nodo* nuevoPadre = dynamic_cast<Nodo *>(nodoBis->hijos[0]);

    // Se asume que la cadena de nodos existe, y ningulo es nulo
    nodoBis->hijos[0] = nuevoPadre->hijos[1];
    nuevoPadre->hijos[1] = (* bis);

    (* bis) = nuevoPadre;
    RC(nuevoPadre);

    return;
}

// Rotaciones dobles
void ArbolRojoNegro::RDI(Connector** bis)
{
    if(bis == 0) return; // Código defensivo
    Nodo* nodoBis = dynamic_cast<Nodo*>(*bis);

    Nodo* antiguoPadre = dynamic_cast<Nodo * >(nodoBis->hijos[1]);
    Nodo* nuevoPadre = dynamic_cast<Nodo * >(antiguoPadre->hijos[0]);

    nodoBis->hijos[1] = nuevoPadre->hijos[0];
    antiguoPadre->hijos[0] = nuevoPadre->hijos[1];
    nuevoPadre->hijos[0] = (* bis);
    nuevoPadre->hijos[1] = antiguoPadre;
    
    (*bis) = nuevoPadre;
    RC(nuevoPadre);

    return;
}

void ArbolRojoNegro::RDD(Connector** bis)
{
    if(bis == 0) return; // Código defensivo
    Nodo* nodoBis = dynamic_cast<Nodo*>(*bis);

    Nodo * antiguoPadre = dynamic_cast<Nodo*>(nodoBis->hijos[0]);
    Nodo * nuevoPadre = dynamic_cast<Nodo*>(antiguoPadre->hijos[1]);

    nodoBis->hijos[0] = nuevoPadre->hijos[1];
    antiguoPadre->hijos[1] = nuevoPadre->hijos[0];
    nuevoPadre->hijos[1] = (*bis);
    nuevoPadre->hijos[0] = antiguoPadre;
    
    (*bis) = nuevoPadre;
    RC(nuevoPadre);

    return;
}

// Se cambia color padre para negro, y el color de los hijos para rojo
void ArbolRojoNegro::RC(Nodo* padre)
{
    std::cout << "ENTRANDO A RC" << std::endl;

    if(padre == 0) return; // Código defensivo
    padre -> color = Nodo::negro;

    // Se asume que los castings son seguros porque se asume que ambos hijos existen, y son nodos
    dynamic_cast<Nodo*>(padre->hijos[Nodo::ladoIzquierdo]) -> color = Nodo::rojo;
    dynamic_cast<Nodo*>(padre->hijos[Nodo::ladoDerecho]) -> color = Nodo::rojo;

    std::cout << "RC EXITOSO" << std::endl;
}