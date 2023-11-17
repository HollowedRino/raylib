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

int Mazacota::verificarTriangulo(Vector3 v1, Vector3 v2, Vector3 v3){
  Vector3 temp = Vector3CrossProduct(v2,v3);
  Vector3 res = Vector3CrossProduct(v1,temp);
  if(res.z>0){
    return 1;
  }else if(res.z<0){
    return 0;
  }else if(res.y>0){
    return 3;
  }else if(res.y<0){
    return 2;
  }else if(res.x>0){
    return 5;
  }else if(res.x<0){
    return 4;
  }else{
    return 2;
  }
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
    DrawTriangle3D(vertice1, vertice2, vertice3, BLUE); //Esto es lo que dibuja


    //Pasar estas funciones a la funcion pintar triangulo
    DrawLine3D(vertice1, vertice2, BLACK);
    DrawLine3D(vertice1, vertice3, BLACK);
    DrawLine3D(vertice2, vertice3, BLACK);
    //Pasar estas funciones a la funcion pintar triangulo

    temp = temp->siguiente;
  }
}

bool Mazacota::compartenAristas(Triangulo* t1, Triangulo* t2){
  int vCompartidos = 0;
  if (t1->vertice1 == t2->vertice1 || t1->vertice1 == t2->vertice2 || t1->vertice1 == t2->vertice3){
    vCompartidos++;
  }
  if (t1->vertice2 == t2->vertice1 || t1->vertice2 == t2->vertice2 || t1->vertice2 == t2->vertice3){
    vCompartidos++;
  }
  if (t1->vertice3 == t2->vertice1 || t1->vertice3 == t2->vertice2 || t1->vertice3 == t2->vertice3){
    vCompartidos++;
  }

  if (vCompartidos == 2){
    return true;
  }else{
    return false;
  }
}

bool Mazacota::verificarMesh(Mazacota *mesh){
  Triangulo* triActual = mesh->trianguloIni;
  Triangulo* triComparador = mesh->trianguloIni;
  bool valido = false;

  while (triActual != nullptr){
    Vector3 vertice1 = getVertice(triActual->vertice1);
    Vector3 vertice2 = getVertice(triActual->vertice2);
    Vector3 vertice3 = getVertice(triActual->vertice3);
    int antihorario = mesh->verificarTriangulo(vertice1, vertice2, vertice3);
    
    if(antihorario%2!=0){
      valido = false;
      while (triComparador != nullptr){
        valido = compartenAristas(triActual, triComparador);
        if (valido == true){
          break;
        }
        triComparador = triComparador->siguiente;
      }
      triActual = triActual->siguiente;
      triComparador = mesh->trianguloIni;
      if (valido == false){
        break;
      }
    }else{
      break;
    }
  }
  return valido;
}

/*bool Mazacota::verificarMesh(Mazacota *mesh)
{
  Triangulo* triActual=mesh->trianguloIni;
  Triangulo* triComparador=mesh->trianguloIni;
  bool validoPrincipal = false;
  while (triActual != nullptr){
    bool valido = false;
    while (triComparador != nullptr){ 
      if (triActual == triComparador){
        break;
      }else if(triComparador->vertice1 == triActual->vertice1){
        if (triComparador->vertice2 == triActual->vertice2 || triComparador->vertice2 == triActual->vertice3 || triComparador->vertice3 == triActual->vertice2 || triComparador->vertice3 == triActual->vertice3){
          valido = true;
          break;
        } 
      }else if(triComparador->vertice1 == triActual->vertice2){
        if (triComparador->vertice2 == triActual->vertice1 || triComparador->vertice2 == triActual->vertice3 || triComparador->vertice3 == triActual->vertice1 || triComparador->vertice3 == triActual->vertice3){
          valido = true;
          break;
        } 
      }else if(triComparador->vertice1 == triActual->vertice3){
        if (triComparador->vertice2 == triActual->vertice1 || triComparador->vertice2 == triActual->vertice2 || triComparador->vertice3 == triActual->vertice1 || triComparador->vertice3 == triActual->vertice2){
          valido = true;
          break;
        } 
      }else if(triComparador->vertice2 == triActual->vertice1){
        if (triComparador->vertice1 == triActual->vertice2 || triComparador->vertice1 == triActual->vertice3 || triComparador->vertice3 == triActual->vertice2 || triComparador->vertice3 == triActual->vertice3){
          valido = true;
          break;
        } 
      }else if(triComparador->vertice2 == triActual->vertice2){
        if (triComparador->vertice1 == triActual->vertice1 || triComparador->vertice1 == triActual->vertice3 || triComparador->vertice3 == triActual->vertice1 || triComparador->vertice3 == triActual->vertice3){
          valido = true;
          break;
        } 
      }else if(triComparador->vertice2 == triActual->vertice3){
        if (triComparador->vertice1 == triActual->vertice1 || triComparador->vertice1 == triActual->vertice2 || triComparador->vertice3 == triActual->vertice1 || triComparador->vertice3 == triActual->vertice2){
          valido = true;
          break;
        } 
      }else if(triComparador->vertice3 == triActual->vertice1){
        if (triComparador->vertice1 == triActual->vertice2 || triComparador->vertice1 == triActual->vertice3 || triComparador->vertice2 == triActual->vertice2 || triComparador->vertice2 == triActual->vertice3){
          valido = true;
          break;
        } 
      }else if(triComparador->vertice3 == triActual->vertice2){
        if (triComparador->vertice2 == triActual->vertice1 || triComparador->vertice2 == triActual->vertice3 || triComparador->vertice1 == triActual->vertice1 || triComparador->vertice1 == triActual->vertice3){
          valido = true;
          break;
        } 
      }else if(triComparador->vertice3 == triActual->vertice3){
        if (triComparador->vertice2 == triActual->vertice2 || triComparador->vertice2 == triActual->vertice1 || triComparador->vertice1 == triActual->vertice1 || triComparador->vertice1 == triActual->vertice2){
          valido = true;
          break;
        } 
      }else{
        valido = false;
      }
      triComparador = triComparador->siguiente;
    } 
    validoPrincipal = valido;
    triActual = triActual->siguiente;
    triComparador=mesh->trianguloIni;
  }
  return validoPrincipal; 
}*/

void Mazacota::PintarTriangulo(Mazacota *triangulo)
{
  Triangulo* temp = triangulo->trianguloIni;
  while (temp != nullptr){
    Vector3 vertice1 = getVertice(temp->vertice1);
    Vector3 vertice2 = getVertice(temp->vertice2);
    Vector3 vertice3 = getVertice(temp->vertice3);
    //Pasar estas funciones a la funcion pintar triangulo
    DrawLine3D(vertice1, vertice2, BLACK);
    DrawLine3D(vertice1, vertice3, BLACK);
    DrawLine3D(vertice2, vertice3, BLACK);

    temp = temp->siguiente;
  }
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

void Mazacota::MoverMesh(Mazacota *mesh, Vector3 destino)
{
  Vertice* vertice = mesh->verticeIni;
  float diferenciaX = destino.x - vertice->pos.x;
  float diferenciaY = destino.y - vertice->pos.y;
  float diferenciaZ = destino.z - vertice->pos.z;
  while (vertice!=nullptr)
  {
    vertice->pos.x = vertice->pos.x + diferenciaX;
    vertice->pos.y = vertice->pos.y + diferenciaY;
    vertice->pos.z = vertice->pos.z + diferenciaZ;

    vertice=vertice->siguiente;
  }
}

/*void Mazacota::Animar(Mazacota* mesh,)
{
  if (IsKeyPressed(KEY_SPACE)) pause = !pause;

    if(!pause)
    {
        mesh->MoverMesh(mesh,prueba);
        prueba.x+=0.05f;
    }
}*/

Mazacota* Mazacota::crearCubo (int largo, Vector3 posicion) {
  Mazacota* cubo = new Mazacota();

  Vector3 v1 = {posicion.x,posicion.y,posicion.z};
  Vector3 v2 = {posicion.x+largo,posicion.y,posicion.z};
  Vector3 v3 = {posicion.x,posicion.y+largo,posicion.z};
  Vector3 v4 = {posicion.x+largo,posicion.y+largo,posicion.z};


  Vector3 v5 = {posicion.x,posicion.y,posicion.z+largo};
  Vector3 v6 = {posicion.x+largo,posicion.y,posicion.z+largo};
  Vector3 v7 = {posicion.x,posicion.y+largo,posicion.z+largo};
  Vector3 v8 = {posicion.x+largo,posicion.y+largo,posicion.z+largo};

  cubo->anadirVertice(v1);
  cubo->anadirVertice(v2);
  cubo->anadirVertice(v3);
  cubo->anadirVertice(v4);
  cubo->anadirVertice(v5);
  cubo->anadirVertice(v6);
  cubo->anadirVertice(v7);
  cubo->anadirVertice(v8);


  //Bien
  cubo->anadirTriangulo(v1,v3,v2); //anda bien
  cubo->anadirTriangulo(v2,v3,v4);
  

  //arriba
  cubo->anadirTriangulo(v8,v3,v7);
  cubo->anadirTriangulo(v4,v3,v8);

  //2 Bn
  cubo->anadirTriangulo(v4,v8,v6);
  cubo->anadirTriangulo(v6,v2,v4);

  //cuidado con estos de abajo

  //3 (alr)
  cubo->anadirTriangulo(v6,v8,v7);
  cubo->anadirTriangulo(v5,v6,v7);

  //4 (bn)
  cubo->anadirTriangulo(v3,v1,v5);
  cubo->anadirTriangulo(v5,v7,v3);


  //abajo
  cubo->anadirTriangulo(v1,v2,v6);
  cubo->anadirTriangulo(v6,v5,v1);

  return cubo;
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

