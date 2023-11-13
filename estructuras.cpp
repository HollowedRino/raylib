#include "estructuras.h"

Mazacota::Mazacota(){
  this->trianguloIni = nullptr;
  this->verticeIni = nullptr;
  this->contadorTri = 0;
  this->contadorVer = 0;
}

void Mazacota::verificarTriangulo(Vector3 v1, Vector3 v2, Vector3 v3){

}

void Mazacota::anadirTriangulo(Vector3 v1, Vector3 v2, Vector3 v3){
  int indice1 = -1;
  int indice2 = -1;
  int indice3 = -1;
  
  Vertice* temporal = new Vertice(v1);
  temporal->siguiente = new Vertice(v2);
  temporal->siguiente->siguiente = new Vertice(v3);
  Vertice* anterior = nullptr; //su unico proposito es borrar los temporal que se repitan
  
  while (temporal != nullptr){ 
    if (this->verticeIni == nullptr){ //primer vertice
      temporal->id = 0;
      indice1 = 0;
      this->contadorVer++;
      this->verticeIni = temporal;
      temporal = temporal->siguiente;
      this->verticeIni->siguiente = nullptr;
    }else{
      Vertice* listaFija = this->verticeIni; // listaFija lleva ese nombre porque es un puntero a la lista que si se queda, no porque vaya a ser una lista permanente
      while (listaFija != temporal && listaFija != nullptr){
        anterior = listaFija;
        listaFija = listaFija->siguiente;
      }

      if (listaFija->pos.x == temporal->pos.x && listaFija->pos.y == temporal->pos.y && listaFija->pos.z == temporal->pos.z){
        anterior = temporal;
        temporal = temporal->siguiente;

        delete anterior;
      }else{
        temporal->id = this->contadorVer;
        if (indice1 == -1){
          indice1 = this->contadorVer;
        }else if(indice2 == -1){                                      //asignacion de vertices
          indice2 = this->contadorVer;
        }else{
          indice3 = this->contadorVer;
        }
        this->contadorVer++;
        listaFija->siguiente = temporal;
        temporal = temporal->siguiente;
        listaFija->siguiente->siguiente = nullptr;
      }
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
//=======================Mazacota=================================
void Mazacota::setTrianguloIni(Triangulo* t){
  this->trianguloIni = t;
}
void Mazacota::setVerticeIni(Vertice* v){
  this->verticeIni = v;
}
Triangulo* Mazacota::getTrianguloIni(){
  return this->trianguloIni;
}
Vertice* Mazacota::getVerticeIni(){
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
