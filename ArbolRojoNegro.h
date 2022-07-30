#ifndef _ARBOLROJONEGRO_
#define _ARBOLROJONEGRO_

class ArbolRojoNegro
{
    private:

        class Connector
        {
            public:

                int llave;
                char tipo;  	//differenciar si es nodo o hoja --> nodo = 0, hoja = 1

                static const char negro = 1;
                static const char rojo = 0;
                
                static const char tipoNodo = 1;
                static const char tipoHoja = 0;

                Connector();
                virtual ~Connector();
        };

        class Hoja : public Connector
        {
            public:

                int valor;
                Hoja* next;
                Hoja* previous;

                Hoja(const int&, const int&, Hoja* = 0, Hoja* = 0);
                ~Hoja(){};
        };

        class Nodo : public Connector
        {
            public:
                static const char ladoIzquierdo = 0;
                static const char ladoDerecho = 1;

                Connector* hijos[2];   //0 es izquierda, 1 es derecha 
                char color;

                Nodo();
                ~Nodo()
                {if(hijos[0] != 0) delete hijos[0]; if(hijos[1] != 0) delete hijos[1];};

                Nodo(Hoja*, Hoja*, char color);

                void colorFlipLocal();
        };

        class Iterador
        {
            private:
                Hoja* actual;

            public:
                Iterador(Hoja*);
                Iterador(const Iterador&);
                ~Iterador();

                Iterador& operator=(const Iterador&);
                bool operator==(const Iterador&);

                Iterador& operator++();
                Iterador operator++(int);

                Iterador& operator--();
                Iterador operator--(int);

                const int& operator*();
        };

        Connector* raiz; //pila -> mejor O
        Hoja* hojaMinima;

        void CF(Nodo*);      //Color-Flip
        void RSI(Connector**);     //Rotación Simple Izquierda
        void RSD(Connector**);     //Rotación simple derecha
        void RDI(Connector**);     //Rotación doble Izquierda
        void RDD(Connector**);     //Rotación doble derecha
        void RC(Nodo*);      //Re-Coloreo

        char verificarRotacion(Connector**);

    public:

        ArbolRojoNegro();    //constructor
        ~ArbolRojoNegro();   //desctructor 

        int insertarDato(const int&,const int&);
        
        Iterador begin();
        Iterador end();
};

#endif