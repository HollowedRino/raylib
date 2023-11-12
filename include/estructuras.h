#pragma once
#include "raylib.h"

class Mesh{
    private:
    public:
        Triangulo* trianguloIni;
        Vertice* verticeIni;

        Mesh();
        Triangulo* getTriangulo(int num);
        Vertice* getVertice(int num);
        void crearTriangulo(Vector3 v1, Vector3 v2, Vector3 v3);
        void verificarTriangulo(Vector3 v1, Vector3 v2, Vector3 v3);
        //FUnciono en el git
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