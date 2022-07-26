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

        class Hoja:Connector{
            public:
                int valor;
                Hoja(int);
        };

    public:
};

#endif