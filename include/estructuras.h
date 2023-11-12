#pragma once
#include "raylib.h"

class Mesh{
    private:
    public:
        Triangulo* trianguloIni;
        Vertice* verticeIni;

        Mesh();
        Triangulo* getTriangulo(int num);
        void setTrianguloIni(Triangulo* trianguloIni);
        Vertice* getVertice(int num);
        void setVertice(Vertice* vertice);
        //xdxdxdxjgnsgkjdbfsakgjbndf
};

class Triangulo{
    private:
    public:
        int vertice1;
        int vertice2;
        int vertice3;
        Triangulo* siguiente;
};

class Vertice{
    private:
    public:
        Vector3 pos;
        Vertice* siguiente;
};