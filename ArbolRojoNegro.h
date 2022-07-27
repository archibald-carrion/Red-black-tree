#ifndef _ARBOLROJONEGRO_
#define _ARBOLROJONEGRO_

class ArbolRojoNegro{
    friend ArbolRojoNegro;
    private:

        class Connector{
            public:
                static const int negro = 1;
                static const int rojo = 0;
                int llave;
                ~Connector();
        };

        class Nodo:public Connector{
            public:
                Connector* hijos[2];   //0 es izquierda, 1 es derecha 
                int color;
                void colorFlip();
                Nodo(Nodo*);
                Nodo(Connector* losHijos[2], int color);
        };

        class Hoja:public Connector{
            public:
                int valor;
                Hoja(int);
        };

        class Iterador{
            public:
                Connector* actual;
                Iterador operator++();
                Iterador operator--();
                Hoja* operator*();


        };

        Connector raiz;
        //pila -> mejor O

        void CCR(Nodo*);     //Cambio Color Raiz Roja a Negra
        void CF(Nodo*);      //Color-Flip
        void RSI(Nodo*);     //Rotación Simple Izquierda
        void RSD(Nodo*);     //Rotación simple derecha
        void RDI(Nodo*);     //Rotación doble Izquierda
        void RDD(Nodo*);     //Rotación doble derecha
        void RC(Nodo*);      //Re-Coloreo
        void IH(Hoja*);      //Insertar Hoja
    public:
        ArbolRojoNegro();    //constructor
        ~ArbolRojoNegro();   //desctructor 
        int insertarDato(int,int);
        Iterador begin();
        Iterador end();
};

#endif