#include "estructuras.h"

Mesh::Mesh(){
  this->trianguloIni = nullptr;
  this->verticeIni = nullptr;
  this->contadorTri = 0;
  this->contadorVer = 0;
}

void Mesh::verificarTriangulo(Vector3 v1, Vector3 v2, Vector3 v3){

}

void Mesh::anadirTriangulo(Vector3 v1, Vector3 v2, Vector3 v3){
  if (verticeIni == nullptr){
    Vertice* nuevoVertice = new Vertice(v1);
    nuevoVertice->id = 0;
    nuevoVertice->siguiente = new Vertice(v2);
    nuevoVertice->siguiente->id = 1;
    nuevoVertice->siguiente->siguiente = new Vertice(v3);
    nuevoVertice->siguiente->siguiente->id = 2;
    this->verticeIni = nuevoVertice;
    this->contadorVer = 3;
  } else{
    
  }
}

//=======================Triangulo=============================
Triangulo::Triangulo(int v1, int v2, int v3){
  this->vertice1 = v1;
  this->vertice2 = v2;
  this->vertice3 = v3;
  this->siguiente = nullptr;
  this->id = 0;
}

//=======================Vertice==============================

Vertice::Vertice(Vector3 pos){
  this->pos = pos;
  this->siguiente = nullptr;
  this->id = 0;
}