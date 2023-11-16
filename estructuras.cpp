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
    }else{
      if (puntero->pos.x == nuevoVertice->pos.x && puntero->pos.y == nuevoVertice->pos.y && puntero->pos.z == nuevoVertice->pos.z){
        delete nuevoVertice;
        return puntero->id;
      }else if(puntero->siguiente == nullptr){
        nuevoVertice->id = contadorVer;
        verticeFinal->siguiente = nuevoVertice;
        verticeFinal=nuevoVertice;
        contadorVer++;
        return nuevoVertice->id;
      }
    }
    puntero = puntero->siguiente;
  }while(puntero != nullptr);
}

bool Mazacota::verificarTriangulo(Vector3 v1, Vector3 v2, Vector3 v3){
  Vector3 temp = Vector3CrossProduct(v2,v3);
  Vector3 res = Vector3CrossProduct(v1,temp);
  if(res.z>=0){
    return true;
  }else{
    return false;
  }
  
  
  //Vector3 P={(v2.y*v3.z-v2.z*v3.y),(v2.z*v3.x-v2.x*v3.z),(v2.x*v3.y-v2.y*v3.x)};
  //Vector3 R ={(v1.y*P.y+v1.z*P.z),(v1.z*P.z-v1.x*P.y),(v1.x*-P.z+v1.y*P.y)};
  //if(R.z>0){
  //  return true;
  //}else{
  //  return false;
  //}


  /*float vec1x = v2.x - v1.x;
  float vec1y = v2.y - v1.y;
  float vec1z = v2.z - v1.z;

  float vec2x = v3.x - v1.x;
  float vec2y = v3.y - v1.y;
  float vec2z = v3.z - v1.z;

  // Calcular el producto cruz entre los vectores
  float productoCruzZ = vec1x * vec2y - vec1y * vec2x;
  if(productoCruzZ>0.0f){
      return true;
    }else{
      return false;
    }*/
}

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

bool Mazacota::verificarMesh(Mazacota *mesh)
{
  Triangulo* triActual=mesh->trianguloIni;
  Triangulo* triComparador=mesh->trianguloIni;
  bool valido = false;
  while (triActual != nullptr){
    while (triComparador != nullptr){ 
      if (triActual == triComparador){
        break;
      }else if((triComparador->vertice1 == triActual->vertice1 && (triComparador->vertice2 == triActual->vertice2 || triComparador->vertice3 == triActual->vertice3)) ||
               (triComparador->vertice1 == triActual->vertice2 && (triComparador->vertice2 == triActual->vertice3 || triComparador->vertice3 == triActual->vertice1)) ||
               (triComparador->vertice1 == triActual->vertice3 && (triComparador->vertice2 == triActual->vertice1 || triComparador->vertice3 == triActual->vertice2))){
        valido = true;
        break;
      }
      triComparador = triComparador->siguiente;
    } 
    triActual = triActual->siguiente;
    triComparador=mesh->trianguloIni;
  } 
  return valido; 
}

Mazacota* Mazacota::crearRectangulo(int ancho, int alto, Vector3 posicion, int plano)
{
  Mazacota* rectangulo = new Mazacota();
  if (plano==1) //1 es xy
  {
    Vector3 v1 = {posicion.x,posicion.y,posicion.z};
    Vector3 v2 = {posicion.x+ancho,posicion.y,posicion.z};
    Vector3 v3 = {posicion.x,posicion.y+alto,posicion.z};
    Vector3 v4 = {posicion.x+ancho,posicion.y+alto,posicion.z};
    rectangulo->anadirVertice(v1);
    rectangulo->anadirVertice(v2);
    rectangulo->anadirVertice(v3);
    rectangulo->anadirVertice(v4);
    rectangulo->anadirTriangulo (v1, v2, v3);
    rectangulo->anadirTriangulo (v4, v3, v2);
    return  rectangulo;
  }
  else if (plano==2) // 2 es xz
  {
    Vector3 v1 = {posicion.x,posicion.y,posicion.z};
    Vector3 v2 = {posicion.x+ancho,posicion.y,posicion.z};
    Vector3 v3 = {posicion.x,posicion.y,posicion.z+alto};
    Vector3 v4 = {posicion.x+ancho,posicion.y,posicion.z+alto};
    rectangulo->anadirVertice(v1);
    rectangulo->anadirVertice(v2);
    rectangulo->anadirVertice(v3);
    rectangulo->anadirVertice(v4);
    rectangulo->anadirTriangulo (v1, v2, v3);
    rectangulo->anadirTriangulo (v4, v3, v2);
    return  rectangulo;
  }
  else if(plano==3) //3 es yz
  {
    Vector3 v1 = {posicion.x,posicion.y,posicion.z};
    Vector3 v2 = {posicion.x,posicion.y+ancho,posicion.z};
    Vector3 v3 = {posicion.x,posicion.y,posicion.z+alto};
    Vector3 v4 = {posicion.x,posicion.y+ancho,posicion.z+alto};
    rectangulo->anadirVertice(v1);
    rectangulo->anadirVertice(v2);
    rectangulo->anadirVertice(v3);
    rectangulo->anadirVertice(v4);
    rectangulo->anadirTriangulo (v1, v2, v3);
    rectangulo->anadirTriangulo (v4, v3, v2);
    return  rectangulo;
  }
     
}

void Mazacota::PintarRectangulo(Mazacota* mesh)
{
  Triangulo* temp = mesh->trianguloIni;
  while (temp != nullptr){
    Vector3 vertice1 = getVertice(temp->vertice1);
    Vector3 vertice2 = getVertice(temp->vertice2);
    Vector3 vertice3 = getVertice(temp->vertice3);
    DrawTriangle3D(vertice1, vertice2, vertice3, BLUE);

    //Pasar estas funciones a la funcion pintar triangulo
    DrawLine3D(vertice1, vertice2, WHITE);
    DrawLine3D(vertice1, vertice3, WHITE);
    DrawLine3D(vertice2, vertice3, WHITE);
    //Pasar estas funciones a la funcion pintar triangulo

    temp = temp->siguiente;
  }

}

void Mazacota::crearCubo(int largo, Vector3 posicion) {
  Vector3 v1 = {posicion.x,posicion.y,posicion.z};
  Vector3 v2 = {posicion.x+largo,posicion.y,posicion.z};
  Vector3 v3 = {posicion.x,posicion.y+largo,posicion.z};
  Vector3 v4 = {posicion.x+largo,posicion.y+largo,posicion.z};
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

