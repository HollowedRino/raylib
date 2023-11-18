#include "estructuras.h"
#include <iostream>

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

int main(){

    
  // Initialization
  //--------------------------------------------------------------------------------------
  const int screenWidth = 800;
  const int screenHeight = 450;

  InitWindow(screenWidth, screenHeight, "raylib [core] example - 3d camera free");

  // Define the camera to look into our 3d world
  Camera3D camera = { 0 };
  camera.position = (Vector3){ 10.0f, 10.0f, 10.0f }; // Camera position
  camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };      // Camera looking at point
  camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };          // Camera up vector (rotation towards target)
  camera.fovy = 45.0f;                                // Camera field-of-view Y
  camera.projection = CAMERA_PERSPECTIVE;             // Camera projection type

  Vector3 v1 = { 1.0f, 1.0f, 1.0f };
  Vector3 v2 = { 1.0f, 1.0f, 9.0f };
  Vector3 v3 = { 9.0f, 1.0f, 1.0f };
  Vector3 v4 = { 1.0f, 9.0f, 1.0f };
  Vector3 v5 = { -9.0f, 9.0f, 1.0f };
  Vector3 v6 = { 7.0f, 0.0f, -3.0f};
  Vector3 pruebaMover= {0.0f,0.0f,10.0f};
  Vector3 prueba = { 0.0f, 0.0f, 0.0f };

//=============VerificarMesh============================
  Mazacota* mesh = new Mazacota();
  mesh->anadirTriangulo(v1,v2,v3);
  mesh->anadirTriangulo(v2,v3,v4); 
  mesh->anadirTriangulo(v2,v4,v1);
  mesh->anadirTriangulo(v4,v2,v5);
  //mesh->anadirTriangulo(v3,v6,v5);
  //mesh->anadirTriangulo(v5,v6,v1);
  std::cout << mesh->verificarMesh(mesh) << std::endl;
//=============VerificarMesh============================
//=============PintarTriangulo============================
  Mazacota* triangulo = new Mazacota();
  triangulo->anadirTriangulo(v1,v2,v3);
//=============PintarTriangulo============================
//=============CrearRectangulo============================ 
  Mazacota* rectangulo;
  rectangulo = rectangulo->crearRectangulo(6,4,v1,1);
//=============CrearRectangulo============================
//=============CrearCubo============================
  Mazacota* cubo;
  cubo = cubo->crearCubo(6,v1);
//=============CrearCubo============================


  //mesh->crearRectangulo(3,2,v1);
  //Mazacota* rectangulo = mesh->crearRectangulo(5,3,v1,3);
  //rectangulo->MoverMesh(rectangulo,pruebaMover);
  //std::cout << rectangulo->compartenAristas(rectangulo->trianguloIni,rectangulo->trianguloIni->siguiente)<<std::endl;
  //crear cubo
  //Mazacota* cubo = mesh->crearCubo(5,v1);

  // std::cout << v2.x << ", " << v2.y << ", " << v2.z << std::endl;

  DisableCursor();                    // Limit cursor to relative movement inside the window
  bool pause = 0;
  SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------
  int esperar = 0;
  int cambiar = 0;
  // Main game loop
  while (!WindowShouldClose())        // Detect window close button or ESC key
  {
      // Update
      //----------------------------------------------------------------------------------
      UpdateCamera(&camera,CAMERA_FREE);

      if (IsKeyDown('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
      //=============AnimarMesh============================
      if (IsKeyPressed(KEY_ENTER)){
        cambiar += 1;
        std::cout << cambiar << std::endl;
      }
      if(cambiar == 7){
        if (IsKeyPressed(KEY_Q)) pause = !pause;
        

        if(!pause)
        {
            mesh->MoverMesh(mesh,prueba);
            prueba.x+=0.05f;
        }
      }
      //=============AnimarMesh============================
      //----------------------------------------------------------------------------------

      // Draw
      //----------------------------------------------------------------------------------
      BeginDrawing();
      // x mas importante que eje z
      // eje X va de izquirda superior a derecha inferior, Z va de izquierda inferior a derecha superior
          ClearBackground(RAYWHITE);

          BeginMode3D(camera);
              if (cambiar == 0){
                DrawGrid(20, 1.0f);
              }else if (cambiar == 1){
                mesh->dibujarMesh();
              }else if(cambiar == 2){
                triangulo->dibujarMesh();
                triangulo->PintarTriangulo(triangulo);
              }else if (cambiar == 3){
                rectangulo->dibujarMesh();
              }else if(cambiar == 4){
                cubo->dibujarMesh();
              }else if (cambiar == 5){
                rectangulo->dibujarMesh();
                rectangulo->PintarRectangulo(rectangulo);
              }else if (cambiar == 6){
                mesh->dibujarMesh();
                if (esperar < 15){
                  esperar++;
                }else if (esperar == 15){
                  mesh->MoverMesh(mesh,pruebaMover);
                  esperar++;
                }
              }else if (cambiar == 7) {
                mesh->dibujarMesh();
              }else{
                cambiar = 0;
              }
              
              
              
              
              
              

              //=============VerificarMesh============================
              //mesh->dibujarMesh();
              //=============VerificarMesh============================
              //=============PintarTriangulo============================              
              //triangulo->dibujarMesh();
              //triangulo->PintarTriangulo(triangulo);
              //=============PintarTriangulo============================ 
              //=============CrearRectangulo============================
              //rectangulo->dibujarMesh();
              //=============CrearRectangulo============================
              //=============CrearCubo============================
              //cubo->dibujarMesh();
              //=============CrearCubo============================
              //=============PintarRectangulo============================
              //rectangulo->PintarRectangulo(rectangulo);
              //=============PintarRectangulo============================
              //=============MoverMesh============================
              /*if (esperar < 15){
                esperar++;
              }else if (esperar == 15){
                mesh->MoverMesh(mesh,pruebaMover);
                esperar++;
              }*/
              //=============MoverMesh============================

              //DrawLine3D(v1,v2,ORANGE);
              //DrawLine3D(v1,v3,GREEN);
              //DrawLine3D(v1,v4,RED);

              //DrawGrid(20, 1.0f);

          EndMode3D();

          DrawRectangle( 10, 10, 320, 93, Fade(SKYBLUE, 0.5f));
          DrawRectangleLines( 10, 10, 320, 93, BLUE);

          DrawText("Free camera default controls:", 20, 20, 10, BLACK);
          DrawText("- Mouse Wheel to Zoom in-out", 40, 40, 10, DARKGRAY);
          DrawText("- Mouse Wheel Pressed to Pan", 40, 60, 10, DARKGRAY);
          DrawText("- Z to zoom to (0, 0, 0)", 40, 80, 10, DARKGRAY);

      EndDrawing();
      //----------------------------------------------------------------------------------
  }

  // De-Initialization
  //--------------------------------------------------------------------------------------
  CloseWindow();        // Close window and OpenGL context
  //--------------------------------------------------------------------------------------
    

    
  return 0;
}