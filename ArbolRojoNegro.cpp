#include "ArbolRojoNegro.h"

// NODO

void ArbolRojoNegro::Nodo::colorFlipLocal()
{
    if(this->color == (char)0) this->color = (char)1;
    else this->color = (char)0; 

    return;
}

ArbolRojoNegro::Nodo::Nodo(Connector* hijoIzquierdo, Connector *hijoDerecho, char color)
{
    this->tipo = tipoNodo;
    this->color = color;

    this->hijos[ladoIzquierdo] = hijoIzquierdo;
    this->hijos[ladoDerecho] = hijoDerecho;

    if(hijoIzquierdo == 0 || hijoDerecho == 0) this->llave = int();
    else if(hijoIzquierdo->llave < hijoDerecho->llave) this->llave = hijoIzquierdo->llave;
    else this->llave = hijoDerecho->llave;
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
        Nodo* nuevoNodo;

        // En ambos casos el nuevo nodo raíz será negro de una vez
        if(llave < raiz->llave) 
        {
            nuevoNodo = new Nodo(nuevaHoja, raiz, Connector::negro);
            hojaMinima = nuevaHoja;
        }
        else 
        {
            nuevoNodo = new Nodo(raiz, nuevaHoja, Connector::negro);
            hojaMinima = dynamic_cast<Hoja*>(raiz); // Casting es seguro porque raiz era una Hoja
        }

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
        Nodo* nuevoNodo;

        if(llave < nodoActual->llave) nuevoNodo = new Nodo(nuevaHoja, connectorHijoActual, Connector::rojo);
        else nuevoNodo = new Nodo(connectorHijoActual, nuevaHoja, Connector::rojo);

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
    char lado_desfasado_2 = 0; // Lado desfasado 2 pasos
    
    while(connectorHijoActual->tipo == Connector::tipoNodo)
    {
        if(bandera == 0) bandera += 1;
        else if(bandera == 1)
        {
            bis = &(raiz);
            lado_desfasado_1 = ladoActual;

            bandera += 1;
        }
        else
        {
            bis_desfasado = bis;
            lado_desfasado_2 = lado_desfasado_1;

            bis = &(dynamic_cast<Nodo*>(*bis_desfasado)->hijos[lado_desfasado_2]);
            lado_desfasado_1 = ladoActual;
        }

        nodoActual = dynamic_cast<Nodo*>(connectorHijoActual);

        if(llave == nodoActual->llave) return 0; // Llave preexistente, no vale la pena seguir bajando

        if(llave < nodoActual->llave) ladoActual = Nodo::ladoIzquierdo;
        else ladoActual = Nodo::ladoDerecho;

        connectorHijoActual = nodoActual->hijos[ladoActual];
    }

    // Tenemos que el connector siguiente es una hoja, y podemos realizar una inserción
    if(llave == connectorHijoActual->llave) return 0; // Llave ya preexistente

    Nodo* nuevoNodo;
    Hoja* nuevaHoja = new Hoja(valor, llave);

    if(llave < connectorHijoActual->llave) nuevoNodo = new Nodo(nuevaHoja, connectorHijoActual, Connector::rojo);
    else nuevoNodo = new Nodo(connectorHijoActual, nuevaHoja, Connector::rojo);

    nodoActual->hijos[ladoActual] = (Connector*) nuevoNodo;
    if(llave < hojaMinima->llave) hojaMinima = nuevaHoja;

    return 1;
}

//	0-> no rotacion
// 	1-> RSI
//	2-> RSD
//	3-> RDI
//	4-> RDD
char ArbolRojoNegro::verificarRotacion(Nodo**bisabuelo)
{
	Nodo* padre = **bisabuelo;
	if(padre -> hijos[0] -> tipo == Connector::tipoNodo && dynamic_cast<Nodo*>( padre -> hijos[0]) -> color == Connector::rojo)
	{					// hijo izquierdo es rojo
		if(padre -> hijos[0] -> hijos[0] -> tipo == Connector::tipoNodo &&  dynamic_cast<Nodo*>( padre -> hijos[0] -> hijos[0]) -> color == Connector::rojo)
		{				// hijo izquierdo del hijo izquierdo es rojo 
			return '2';	// rotacion simple derecha
		} else if(padre -> hijos[0] -> hijos[1] -> tipo == Connector::tipoNodo &&  dynamic_cast<Nodo*>( padre -> hijos[0] -> hijos[1]) -> color == Connector::rojo)
		{				// hijo derecho del hijo izquierdo es rojo
			return '4';	// rotacion doble derecha
		} else
		{				// hijo izquierdo es rojo pero nieto no lo es
			return '0';
		}
	} else if(padre -> hijos[1] -> tipo == Connector::tipoNodo && dynamic_cast<Nodo*>( padre -> hijos[1]) -> color == Connector::rojo)
	{					// hijo derecho es rojo
		if(padre -> hijos[1] -> hijos[0] -> tipo == Connector::tipoNodo &&  dynamic_cast<Nodo*>( padre -> hijos[1] -> hijos[0]) -> color == Connector::rojo)
		{				// hijo izquierdo del hijo derecho es rojo 
			return '3';	//rotacion doble izquierda
		} else if(padre -> hijos[1] -> hijos[1] -> tipo == Connector::tipoNodo &&  dynamic_cast<Nodo*>( padre -> hijos[1] -> hijos[1]) -> color == Connector::rojo)
		{				// hijo derecho del hijo derecho es rojo
			return '1';	// rotacion simple izquierda
		} else
		{				// hijo derecho es rojo pero nieto no lo es
			return '0';
		}
	} else {
		return '0';
	}
}

//se pasa la raiz a negro
void ArbolRojoNegro::CCR()
{
    dynamic_cast<Nodo*>(raiz) -> colorFlipLocal();
    return;
}

//se cambia color padre rojo y hijos a negro
void ArbolRojoNegro::CF(Nodo** padre)
{
    if(padre = 0) return; // Código defensivo

    // Casting se asume seguro porque padre debe ser un nodo
    Nodo* nodoPadre = dynamic_cast<Nodo*>(*padre);
	nodoPadre -> colorFlipLocal();

    // Se asume que el árbol minimal de nodos existe, y ningulo de los dos hijos es nulo u hoja
    dynamic_cast<Nodo*>(nodoPadre->hijos[0]) -> colorFlipLocal();
    dynamic_cast<Nodo*>(nodoPadre->hijos[1]) -> colorFlipLocal();
}

// Rotaciones simples
void ArbolRojoNegro::RSI(Nodo** bis)
{
    if(bis == 0) return; // Código defensivo

    // Casting se asume seguro porque bisabuelo debe apuntar a un nodo
    Nodo* nuevoPadre = dynamic_cast<Nodo *>((* bis)->hijos[1]);

    // Se asume que la cadena de nodos existe, y ningulo es nulo
    (* bis)->hijos[1] = nuevoPadre->hijos[0];
    nuevoPadre->hijos[0] = (* bis);
    (* bis) = nuevoPadre;

    return;
}

void ArbolRojoNegro::RSD(Nodo** bis)
{
    if(bis == 0) return; // Código defensivo

    // Casting se asume seguro porque bisabuelo debe apuntar a un nodo
    Nodo* nuevoPadre = dynamic_cast<Nodo *>((* bis)->hijos[0]);

    // Se asume que la cadena de nodos existe, y ningulo es nulo
    (* bis)->hijos[0] = nuevoPadre->hijos[1];
    nuevoPadre->hijos[1] = (* bis);
    (* bis) = nuevoPadre;

    return;
}

// Rotaciones dobles
void ArbolRojoNegro::RDI(Nodo ** bis)
{
    Nodo* antiguoPadre = dynamic_cast<Nodo * >((* bis)->hijos[1]);
    Nodo* nuevoPadre = dynamic_cast<Nodo * >(antiguoPadre->hijos[0]);

    (*bis)->hijos[1] = nuevoPadre->hijos[0];
    antiguoPadre->hijos[0] = nuevoPadre->hijos[1];
    nuevoPadre->hijos[0] = (* bis);
    nuevoPadre->hijos[1] = antiguoPadre;
    (*bis) = nuevoPadre;

    RC(*bis);
}

void ArbolRojoNegro::RDD(Nodo ** bis)
{
    Nodo * antiguoPadre = dynamic_cast<Nodo*>((*bis)->hijos[0]);
    Nodo * nuevoPadre = dynamic_cast<Nodo*>(antiguoPadre->hijos[1]);

    (*bis)->hijos[0] = nuevoPadre->hijos[1];
    antiguoPadre->hijos[1] = nuevoPadre->hijos[0];
    nuevoPadre->hijos[1] = (*bis);
    nuevoPadre->hijos[0] = antiguoPadre;
    (*bis) = nuevoPadre;

    RC(*bis);
}

// Se cambia color padre para negro, y el color de los hijos para rojo
void ArbolRojoNegro::RC(Nodo *padre)
{
    if(padre = 0) return; // Código defensivo
    padre -> color = Connector::negro;

    // Se asume que los castings son seguros porque se asume que ambos hijos existen, y son nodos
    dynamic_cast<Nodo*>(padre->hijos[0]) -> color = Connector::rojo;
    dynamic_cast<Nodo*>(padre->hijos[1]) -> color = Connector::rojo;
}