#include "ArbolRojoNegro.h"

// NODO

void ArbolRojoNegro::Nodo::colorFlipLocal()
{
    if(this->color == (char)0) this->color = (char)1;
    else this->color = (char)0; 

    return;
}

ArbolRojoNegro::Nodo::Nodo(Hoja* hijaIzquierda, Hoja* hijaDerecha, char color)
{
    this->tipo = tipoNodo;
    this->color = color;

    this->hijos[ladoIzquierdo] = hijaIzquierda;
    this->hijos[ladoDerecho] = hijaDerecha;

    if(hijaIzquierda == 0 || hijaDerecha == 0) this->llave = int();
    else if(hijaIzquierda->llave < hijaDerecha->llave) this->llave = hijaIzquierda->llave;
    else this->llave = hijaDerecha->llave;

    hijaIzquierda->next = hijaDerecha;
    hijaDerecha->previous = hijaIzquierda;
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
        if(llave < raiz->llave) 
        {
            nuevoNodo = new Nodo(nuevaHoja, raizComoHoja, Connector::negro);
            hojaMinima = nuevaHoja;
        }
        else 
        {
            nuevoNodo = new Nodo(raizComoHoja, nuevaHoja, Connector::negro);
            hojaMinima = raizComoHoja; 
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
        Hoja* hojaHijaActual = dynamic_cast<Hoja*>(connectorHijoActual);
        Nodo* nuevoNodo;

        if(llave < nodoActual->llave) nuevoNodo = new Nodo(nuevaHoja, hojaHijaActual, Connector::rojo);
        else nuevoNodo = new Nodo(hojaHijaActual, nuevaHoja, Connector::rojo);

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
        // Antes de descender, verificaremos si ambos hermanos son rojos, si acaso es necesario realizar un color flip en el nodo actual
        Connector* hermanoTemporal;
        if(ladoActual == Nodo::ladoIzquierdo) hermanoTemporal = nodoActual->hijos[Nodo::ladoDerecho];
        else hermanoTemporal = nodoActual->hijos[Nodo::ladoIzquierdo];

        if(hermanoTemporal->tipo == Connector::tipoNodo) // Comparación es segura porque la estructura del árbol evita connectores nulos
        {
            // Castings son seguros porque se garantizó que ambos conectores existen y son nodos
            Nodo* nodoHermano = dynamic_cast<Nodo*>(hermanoTemporal);
            Nodo* nodoHijo = dynamic_cast<Nodo*>(connectorHijoActual);

            if(nodoHermano->color == Nodo::rojo && nodoHijo->color == Nodo::rojo) CF(nodoActual);
        }

        // Ahora sí, podemos descender.
        if(bandera == 0) bandera += 1; // El primer descenso es especial, está garantizado, y no se puede conocer el bisabuelo, por lo que no se calcula
        else if(bandera == 1) // El segundo descenso también es especial, pues el bisabuelo por fuerza es la raíz
        {
            bis = &(raiz);
            lado_desfasado_1 = ladoActual;

            bandera += 1;
        }
        else // El resto de descensos son fácilmente iterables
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
    Hoja* hojaHijaActual = dynamic_cast<Hoja*>(connectorHijoActual);
    Hoja* nuevaHoja = new Hoja(valor, llave);

    if(llave < connectorHijoActual->llave) nuevoNodo = new Nodo(nuevaHoja, hojaHijaActual, Connector::rojo);
    else nuevoNodo = new Nodo(hojaHijaActual, nuevaHoja, Connector::rojo);

    nodoActual->hijos[ladoActual] = (Connector*) nuevoNodo;
    if(llave < hojaMinima->llave) hojaMinima = nuevaHoja;

    // Realizamos la rotación necesaria, si acaso
    switch (verificarRotacion(bis))
    {
        case char(0):
            /* code */
            break;

        case char(1):
            RSI(bis);
            break;

        case char(2):
            RSD(bis);
            break;

        case char(3):
            RDI(bis);
            break;

        case char(4):
            RDD(bis);
            break;
        
        default:
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
    if(padre = 0) return; // Código defensivo

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
    Nodo* nuevoPadre = dynamic_cast<Nodo *>(nodoBis->hijos[1]);

    // Se asume que la cadena de nodos existe, y ningulo es nulo
    nodoBis->hijos[1] = nuevoPadre->hijos[0];
    nuevoPadre->hijos[0] = (* bis);

    (* bis) = nuevoPadre;
    RC(nodoBis);

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
    RC(nodoBis);

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
    RC(nodoBis);

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
    RC(nodoBis);

    return;
}

// Se cambia color padre para negro, y el color de los hijos para rojo
void ArbolRojoNegro::RC(Nodo* padre)
{
    if(padre = 0) return; // Código defensivo
    padre -> color = Connector::negro;

    // Se asume que los castings son seguros porque se asume que ambos hijos existen, y son nodos
    dynamic_cast<Nodo*>(padre->hijos[0]) -> color = Connector::rojo;
    dynamic_cast<Nodo*>(padre->hijos[1]) -> color = Connector::rojo;
}