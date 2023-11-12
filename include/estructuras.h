#pragma once
#include "raylib.h"

class Mesh{
  private:
  public:
    Triangulo* trianguloIni; //deben ser 4 en total
    Vertice* verticeIni; 
    int contadorTri;
    int contadorVer;
    Mesh();
    Triangulo* getTriangulo(int id);
    Vector3 getVertice(int id); 
    //Ya no es puntero porque vertice como tiene un valoro, accedes directamente a vector3 
    void anadirTriangulo(Vector3 v1, Vector3 v2, Vector3 v3);
    void verificarTriangulo(Vector3 v1, Vector3 v2, Vector3 v3);

    //getters and setters
    void setTrianguloIni(Triangulo* t);
    void setVerticeIni(Vertice* v);
    Triangulo* getTrianguloIni();
    Vertice* getVerticeIni();
};

class Triangulo{
  private:
  public:
    int id;
    int vertice1; 
    int vertice2; 
    int vertice3; 
    Triangulo* siguiente;

    //constructor
    Triangulo(int id, int v1, int v2, int v3);

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
    Vertice(int id, Vector3 pos);

    //getters and setters
    void setId(int id);
    void setPos(Vector3 pos);
    int getId();
    Vector3 getPos();
    Vertice* getSiguiente();
};

//requerimiento 1
//Implementar una función llamada VerificarMesh que reciba un Mesh y devuelva un booleano
//que indique si es un Mesh válido o no.
