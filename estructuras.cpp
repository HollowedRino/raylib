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
  int indice1;
  int indice2;
  int indice3;
  Vertice* listaTemporal = new Vertice(v1);
  listaTemporal->siguiente = new Vertice(v2);
  listaTemporal->siguiente->siguiente = new Vertice(v3);
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
    Vertice* temp = this->verticeIni;
    for (int i = 0; i < 3; i++){
      /* code */
    }
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










// ========== Lista de getters y setters ==========

//=======================Getters and Setters==================
//=======================Mesh=================================
void Mesh::setTrianguloIni(Triangulo* t){
  this->trianguloIni = t;
}
void Mesh::setVerticeIni(Vertice* v){
  this->verticeIni = v;
}
Triangulo* Mesh::getTrianguloIni(){
  return this->trianguloIni;
}
Vertice* Mesh::getVerticeIni(){
  return this->verticeIni;
}

//=======================Triangulo=============================
void Triangulo::setVertice1(int v1){
  this->vertice1 = v1;
}
void Triangulo::setVertice2(int v2){
  this->vertice2 = v2;
}
void Triangulo::setVertice3(int v3){
  this->vertice3 = v3;
}
int Triangulo::getId(){
  return this->id;
}
int Triangulo::getVertice1(){
  return this->vertice1;
}
int Triangulo::getVertice2(){
  return this->vertice2;
}
int Triangulo::getVertice3(){
  return this->vertice3;
}

//=======================Vertice==============================
void Vertice::setId(int id){
  this->id = id;
}
void Vertice::setPos(Vector3 pos){
  this->pos = pos;
}
int Vertice::getId(){
  return this->id;
}
Vector3 Vertice::getPos(){
  return this->pos;
}
Vertice* Vertice::getSiguiente(){
  return this->siguiente;
}
