#ifndef _ARBOLROJONEGRO_
#define _ARBOLROJONEGRO_

class ArbolRojoNegro{
    //friend ArbolRojoNegro;
    private:

        class Connector{
            public:
                static const char negro = 1;
                static const char rojo = 0;
                int llave;
                ~Connector();
                static const char tipoNodo = 1;
                static const char tipoHoja = 0;
                char tipo;  	//differenciar si es nodo o hoja --> nodo = 0, hoja = 1
        };

        class Nodo:public Connector{
            public:
                Connector* hijos[2];   //0 es izquierda, 1 es derecha 
                char color;
                void colorFlip();
                Nodo(Nodo*);
                static const char ladoIzquierdo = 0;
                static const char ladoDerecho = 1;
                Nodo(Connector*, Connector*, char color, int llaveTemporal);
        };

        class Hoja:public Connector{
            public:
                int valor;
                Hoja(int, int);
        };

        class Iterador{
            public:
                Iterador(Connector*);
                Iterador(const Iterador&);
                Iterador operator=(const Iterador&);
                void operator==(const Iterador&);
                Connector* actual;
                Iterador operator++();
                Iterador operator--();
                Hoja* operator*();
        };

        Connector* raiz;
        //pila -> mejor O

        void CCR(Nodo*);     //Cambio Color Raiz Roja a Negra
        void CF(Nodo*);      //Color-Flip
        void RSI(Nodo*);     //Rotación Simple Izquierda
        void RSD(Nodo*);     //Rotación simple derecha
        void RDI(Nodo*);     //Rotación doble Izquierda
        void RDD(Nodo*);     //Rotación doble derecha
        void RC(Nodo*);      //Re-Coloreo
        void IH(Hoja*);      //Insertar Hoja
        int insertarDatoRecursivo(Hoja*, Connector*);
    public:
        ArbolRojoNegro();    //constructor
        ~ArbolRojoNegro();   //desctructor 
        int insertarDato(int,int);
        Iterador begin();
        Iterador end();
};

#endif