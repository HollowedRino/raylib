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

//================Métodos de Mazacueta======================
Vector3 Mazacota::getVertice(int id){
  Vertice* temp = this->verticeIni;
  while (temp != nullptr){
    if (temp->id == id){
      return temp->pos;
    }
    temp = temp->siguiente;
  }
}

int Mazacota::anadirVertice(Vector3 vertice){
  Vertice* nuevoVertice = new Vertice(vertice);
  Vertice* puntero = this->verticeIni;
  do{
    if(this->verticeIni==nullptr){
      verticeIni=nuevoVertice;
      verticeFinal=nuevoVertice;
      contadorVer++;
      return nuevoVertice->id;
      break;
    }else{
      if(puntero == nullptr){
        nuevoVertice->id = contadorVer;
        verticeFinal->siguiente = nuevoVertice;
        verticeFinal=nuevoVertice;
        contadorVer++;
        return nuevoVertice->id;
        break;
      }else if (puntero->pos.x == nuevoVertice->pos.x && puntero->pos.y == nuevoVertice->pos.y && puntero->pos.z == nuevoVertice->pos.z){
        delete nuevoVertice;
        return puntero->id;
        break;
      }
    }
    if(puntero != nullptr){
      puntero = puntero->siguiente;
    }
  }while(puntero != nullptr);
}

/*bool Mazacota::verificarTriangulo(Vector3 v1, Vector3 v2, Vector3 v3){
  if((triangulo->vertice2->pos.x < triangulo->vertice1->pos.x && triangulo->vertice3->pos.y < triangulo->vertice1->pos.y)||
    (triangulo->vertice2->pos.x > triangulo->vertice1->pos.x && triangulo->vertice3->pos.y > triangulo->vertice1->pos.y)||
    (triangulo->vertice2->pos.y < triangulo->vertice1->pos.x && triangulo->vertice3->pos.x > triangulo->vertice1->pos.y)||
    (triangulo->vertice2->pos.y > triangulo->vertice1->pos.x && triangulo->vertice3->pos.x < triangulo->vertice1->pos.y)){
      return true;
    }else{
      return false;
    }
}*/

void Mazacota::anadirTriangulo(Vector3 v1, Vector3 v2, Vector3 v3){
  int indice1 = anadirVertice(v1);
  int indice2 = anadirVertice(v2);
  int indice3 = anadirVertice(v3);
  
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
}

void Mazacota::dibujarMesh(){
  Triangulo* temp = this->trianguloIni;
  while (temp != nullptr){
    Vector3 vertice1 = getVertice(temp->vertice1);
    Vector3 vertice2 = getVertice(temp->vertice2);
    Vector3 vertice3 = getVertice(temp->vertice3);
    DrawTriangle3D(vertice1, vertice2, vertice3, BLUE);

    //Pasar estas funciones a la funcion pintar triangulo
    DrawLine3D(vertice1, vertice2, BLACK);
    DrawLine3D(vertice1, vertice3, BLACK);
    DrawLine3D(vertice2, vertice3, BLACK);
    //Pasar estas funciones a la funcion pintar triangulo

    temp = temp->siguiente;
  }
}

void Mazacota::crearRectangulo(int ancho, int alto, Vector3 posicion)
{
  Vector3 v1 = {posicion.x,posicion.y,posicion.z};
  Vector3 v2 = {posicion.x+ancho,posicion.y,posicion.z};
  Vector3 v3 = {posicion.x,posicion.y+alto,posicion.z};
  Vector3 v4 = {posicion.x+ancho,posicion.y+alto,posicion.z};
  anadirTriangulo (v1, v2, v3);
  anadirTriangulo (v1, v2, v3); // corregir el orden en el que estan puestos los vertices

  //Aqui solo sería llamar a la funcion de crear triangulos y ya estaría este requisito
}





// ========== Lista de getters y setters ==========

//=======================Getters and Setters==================
//=======================Mazacota================================
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

