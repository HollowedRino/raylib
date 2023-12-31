#pragma once
#include "raylib.h"
#include "raymath.h"
#include <iostream>
class Triangulo{
  private:
  public:
    int id;
    int vertice1; 
    int vertice2; 
    int vertice3; 
    Triangulo* siguiente;

    //constructor
    Triangulo(int v1, int v2, int v3);

    //getters and setters
    void setVertice1(int v1);
    void setVertice2(int v2);
    void setVertice3(int v3);
    int getId();
    int getVertice1();
    int getVertice2();
    int getVertice3();
};

class Vertice{
  private:
  public:
    int id;
    Vector3 pos;
    Vertice* siguiente;

    //constructor
    Vertice(Vector3 pos);

    //getters and setters
    void setId(int id);
    void setPos(Vector3 pos);
    int getId();
    Vector3 getPos();
    Vertice* getSiguiente();
};

class Mazacota{ //necesario cambiar nombre de clase
  private:
  public:
    Triangulo* trianguloIni;
    Triangulo* trianguloFinal; //deben ser 4 en total
    Vertice* verticeIni;
    Vertice* verticeFinal; 
    int contadorTri;
    int contadorVer;
    Mazacota();
    
    Vector3 getVertice(int id); 
    
    int anadirVertice(Vector3 vertice);
    void anadirTriangulo(Vector3 v1, Vector3 v2, Vector3 v3);
    int verificarTriangulo(Vector3 v1, Vector3 v2, Vector3 v3);
    void dibujarMesh();

    bool compartenAristas(Triangulo* t1, Triangulo* t2);
    
    bool verificarMesh(Mazacota* mesh);
    void PintarTriangulo(Mazacota* triangulo);
    Mazacota* crearCubo(int largo, Vector3 posicion);
    
    Mazacota* crearRectangulo(int ancho, int alto, Vector3 posicion, int plano);
    void PintarRectangulo(Mazacota* mesh);
    void MoverMesh(Mazacota* mesh, Vector3 destino);
    //getters and setters
    void setTrianguloIni(Triangulo* t);
    void setVerticeIni(Vertice* v);
    Triangulo* getTrianguloIni();
    Vertice* getVerticeIni();

    
};
