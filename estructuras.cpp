#include "estructuras.h"

Mazacota::Mazacota(){
  this->trianguloIni = nullptr;
  this->verticeIni = nullptr;
  this->trianguloFinal = nullptr;
  this->verticeFinal = nullptr;
  this->contadorTri = 0;
  this->contadorVer = 0;
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

//================Métodos de Mazacueta=====================
int Mazacota::anadirVertice(Vector3 vertice){
  Vertice* nuevoVertice = new Vertice(vertice);
  Vertice* puntero = this->verticeIni;
  do{
    if(this->verticeIni==nullptr){
      verticeIni=nuevoVertice;
      verticeFinal=nuevoVertice;
      contadorVer++;
      return contadorVer-1;
    }else{
      if (puntero->pos.x == nuevoVertice->pos.x && puntero->pos.y == nuevoVertice->pos.y && puntero->pos.z == nuevoVertice->pos.z){
        
      }else if(puntero == nullptr){
        nuevoVertice->id = contadorVer;
        verticeFinal->siguiente = nuevoVertice;
        verticeFinal=nuevoVertice;
        contadorVer++;
      }
    }
    if(puntero != nullptr){
      puntero = puntero->siguiente;
    }
  }while(puntero != nullptr);
}

bool Mazacota::verificarTriangulo(Vector3 v1, Vector3 v2, Vector3 v3){
  if((triangulo->vertice2->pos.x < triangulo->vertice1->pos.x && triangulo->vertice3->pos.y < triangulo->vertice1->pos.y)||
    (triangulo->vertice2->pos.x > triangulo->vertice1->pos.x && triangulo->vertice3->pos.y > triangulo->vertice1->pos.y)||
    (triangulo->vertice2->pos.y < triangulo->vertice1->pos.x && triangulo->vertice3->pos.x > triangulo->vertice1->pos.y)||
    (triangulo->vertice2->pos.y > triangulo->vertice1->pos.x && triangulo->vertice3->pos.x < triangulo->vertice1->pos.y)){
      return true;
    }else{
      return false;
    }
}

void Mazacota::anadirTriangulo(Vector3 v1, Vector3 v2, Vector3 v3){
  Triangulo* nuevoTriangulo = new Triangulo(v1,v2,v3);
  if(verificarTriangulo(nuevoTriangulo)){
    if(trianguloIni==nullptr){
      trianguloIni=nuevoTriangulo;
      trianguloFinal=nuevoTriangulo;
    }else{
      trianguloFinal->siguiente = nuevoTriangulo;
      trianguloFinal=nuevoTriangulo;
    }
  }else{
    std::cout<<"Coloca los vertices bonito p"<<std::endl;
  }

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


// anadir de Sebas
void Mazacota::anadirTriangulo(Vector3 v1, Vector3 v2, Vector3 v3){

  if(this->verificarTriangulo(v1, v2, v3)){
    int indice1 = -1;
    int indice2 = -1;
    int indice3 = -1;
    
    Vertice* temporal = new Vertice(v1);
    temporal->siguiente = new Vertice(v2);
    temporal->siguiente->siguiente = new Vertice(v3);
    Vertice* anterior = nullptr; 
    
    //Ingreso de vertices
    while (temporal != nullptr){ 
      //Primer vertice
      if (this->verticeIni == nullptr){ 
        indice1 = 0;
        this->contadorVer++;
        this->verticeIni = temporal;
        temporal = temporal->siguiente;
        this->verticeIni->siguiente = nullptr;
      }
      //Los demas vertices
      else{
        //Posicionar puntero hasta completar la lista de vertices actuales o hasta encontrar un vertice igual
        Vertice* listaFija = this->verticeIni; 
        while (listaFija != nullptr){
          if (listaFija->pos.x == temporal->pos.x && listaFija->pos.y == temporal->pos.y && listaFija->pos.z == temporal->pos.z){
            if (indice1 == -1){
              indice1 = listaFija->id;
            }else if(indice2 == -1){
              indice2 = listaFija->id;
            }else{
              indice3 = listaFija->id;
            }
            anterior = temporal;
            temporal = temporal->siguiente;
            delete anterior;
            break;
          }
          anterior = listaFija;
          listaFija = listaFija->siguiente;
        }
        if (listaFija == nullptr){
          if (indice1 == -1){
            indice1 = this->contadorVer;
          }else if(indice2 == -1){
            indice2 = this->contadorVer;
          }else{
            indice3 = this->contadorVer;
          }
          this->contadorVer++;
          anterior->siguiente = temporal;
          temporal = temporal->siguiente;
          listaFija->siguiente = nullptr;
        }
      }
    }
    Triangulo* nuevoTriangulo = new Triangulo(indice1, indice2, indice3);
    if (this->trianguloIni == nullptr){
      this->trianguloIni = nuevoTriangulo;
      this->contadorTri++;
    }else{
      Triangulo* temp = this->trianguloIni;
      while (temp->siguiente != nullptr){
        temp = temp->siguiente;
      }
      nuevoTriangulo->id = this->contadorTri;
      temp->siguiente = nuevoTriangulo;
      this->contadorTri++;
    }
  }else{
    std::cout<<"Coloca los vertices bonito pe, no seas mongol"<<std::endl;
  }
}
