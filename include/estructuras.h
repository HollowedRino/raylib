#pragma once
#include "raylib.h"
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
    //Triangulo* getTriangulo(int id);
    Vector3 getVertice(int id); 
    //Ya no es puntero porque vertice como tiene un valoro, accedes directamente a vector3 
    int anadirVertice(Vector3 vertice);
    void anadirTriangulo(Vector3 v1, Vector3 v2, Vector3 v3);
    bool verificarTriangulo(Vector3 v1, Vector3 v2, Vector3 v3);
    void dibujarMesh();

    //requisitos (por el momento los pondre aquí, pero si quieren mejorar el orden despues podemos
    // moverlos a otros .h)
    void crearRectangulo(int ancho, int alto, Vector3 posicion);    
    //getters and setters
    void setTrianguloIni(Triangulo* t);
    void setVerticeIni(Vertice* v);
    Triangulo* getTrianguloIni();
    Vertice* getVerticeIni();
};




//requerimiento 1
//Implementar una función llamada VerificarMazacota que reciba un Mazacota y devuelva un booleano
//que indique si es un Mazacota válido o no.