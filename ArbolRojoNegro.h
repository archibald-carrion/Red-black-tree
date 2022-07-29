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

        class Nodo : public Connector
        {
            public:
                static const char ladoIzquierdo = 0;
                static const char ladoDerecho = 1;

                Connector* hijos[2];   //0 es izquierda, 1 es derecha 
                char color;

                Nodo();
                ~Nodo();

                Nodo(Connector*, Connector*, char color, int llaveTemporal);

                void colorFlipLocal();
        };

        class Hoja : public Connector
        {
            public:
                int valor;

                Hoja(const int&, const int&);
        };

        class Iterador
        {
            private:
                Connector* actual;

            public:
                Iterador(Connector*);
                Iterador(const Iterador&);

                Iterador operator=(const Iterador&);
                bool operator==(const Iterador&);

                Iterador operator++();
                Iterador operator++(int);

                Iterador operator--();

                const int& operator*();
        };

        Connector* raiz; //pila -> mejor O

        void CCR();     //Cambio Color Raiz Roja a Negra
        void CF(Nodo**);      //Color-Flip
        void RSI(Nodo**);     //Rotación Simple Izquierda
        void RSD(Nodo**);     //Rotación simple derecha
        void RDI(Nodo**);     //Rotación doble Izquierda
        void RDD(Nodo**);     //Rotación doble derecha
        void RC(Nodo**);      //Re-Coloreo
        void IH(Hoja*);      //Insertar Hoja
<<<<<<< HEAD

        int insertarDatoRecursivo(Hoja*, Connector*);

=======
        int insertarDatoRecursivo(Hoja*, Connector*);
>>>>>>> b6d91ec73e0955e406dfc4e07fed7f46aa0a5c8a
    public:

        ArbolRojoNegro();    //constructor
        ~ArbolRojoNegro();   //desctructor 

        int insertarDato(int,int);
<<<<<<< HEAD
        
=======
>>>>>>> b6d91ec73e0955e406dfc4e07fed7f46aa0a5c8a
        Iterador begin();
        Iterador end();
};

#endif