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

  Vector3 v1 = { 0.0f, 0.0f, 0.0f };
  Vector3 v2 = { 0.0f, 0.0f, 9.0f };
  Vector3 v3 = { 9.0f, 0.0f, 0.0f };
  Vector3 v4 = { 0.0f, 9.0f, 0.0f };
  Vector3 v5 = { -9.0f, 9.0f, 0.0f };
  Vector3 pruebaMover= {1.0f,1.0f,1.0f};

  Mazacota* mesh = new Mazacota();
  mesh->anadirTriangulo(v1,v2,v3);
  mesh->anadirTriangulo(v2,v3,v4);
  std::cout<<mesh->verificarTriangulo(v1,v2,v3)<<std::endl;
  std::cout<<mesh->verificarTriangulo(v1,v3,v2)<<std::endl;
  std::cout << mesh->verificarMesh(mesh) << std::endl;
  //mesh->crearRectangulo(3,2,v1);
  Mazacota* rectangulo = mesh->crearRectangulo(5,3,v1,3);
  //rectangulo->MoverMesh(rectangulo,pruebaMover);
  
  // std::cout << v2.x << ", " << v2.y << ", " << v2.z << std::endl;

  DisableCursor();                    // Limit cursor to relative movement inside the window

  SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
  //--------------------------------------------------------------------------------------

  // Main game loop
  while (!WindowShouldClose())        // Detect window close button or ESC key
  {
      // Update
      //----------------------------------------------------------------------------------
      UpdateCamera(&camera, CAMERA_FREE); //<------------------Esto hace que la camara sea de movimiento libre

      if (IsKeyDown('Z')) camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
      //----------------------------------------------------------------------------------

      // Draw
      //----------------------------------------------------------------------------------
      BeginDrawing();
      // x mas importante que eje z
      // eje X va de izquirda superior a derecha inferior, Z va de izquierda inferior a derecha superior
          ClearBackground(RAYWHITE);

          BeginMode3D(camera);
              rectangulo->PintarRectangulo(rectangulo);
              mesh->dibujarMesh();

              DrawLine3D(v1,v2,ORANGE);
              DrawLine3D(v1,v3,GREEN);
              DrawLine3D(v1,v4,RED);

              DrawGrid(20, 1.0f);

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