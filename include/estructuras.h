#pragma once
#include "raylib.h"

class Mesh{
  private:
  public:
    Triangulo* trianguloIni; //deben ser 4 en total
    Vertice* verticeIni; 
    int borrar;
    Mesh();
    Triangulo* getTriangulo(int id);
    Vector3 getVertice(int num); 
    //Ya no es puntero porque vertice como tiene un valoro, accedes directamente a vector3 
    void anadirTriangulo(int id, Vector3 v1, Vector3 v2, Vector3 v3);
    void verificarTriangulo(int id, Vector3 v1, Vector3 v2, Vector3 v3);

    //contarParaTriangulos
    
    //contarVertices

};

class Triangulo{
  private:
  public:
    int id;
    int vertice1; 
    int vertice2; 
    int vertice3; 
    Triangulo* siguiente;
};

class Vertice{
  private:
  public:
    int id;
    Vector3 pos;
    Vertice* siguiente;
};

//requerimiento 1
//Implementar una función llamada VerificarMesh que reciba un Mesh y devuelva un booleano
//que indique si es un Mesh válido o no.

//AAAA se logro.