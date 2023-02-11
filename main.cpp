#include "raylib.h"
#include "raymath.h"

int main(){

    int windowDimension [2];
    windowDimension[0] = 384;
    windowDimension[1] = 384;

    InitWindow(windowDimension[0], windowDimension[1], "RPG");

    Texture2D worldMap = LoadTexture("textures/winter-map.png");
    Vector2 wmPos {0.0, 0.0};
    const float speed = 4.0;

    //FPS
    SetTargetFPS(60);
    //Game Loop
    while (!WindowShouldClose())
    {   
        BeginDrawing();
        ClearBackground(WHITE);

        //Puoi tenere il codice più compatto se usi gli if mettendo il codice da eseguire dopo la condizione senza
        //graffe e sulla stessa linea dell'if

        Vector2 direction {};
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;
        if (Vector2Length(direction) != 0.0){
            //set wmPos = wmPos - direction

            //sottrai la posizione della mappa con il vettore direzione normalizzato (1) scalato per la speed
            wmPos = Vector2Subtract(wmPos, Vector2Scale(Vector2Normalize(direction), speed));
        }

        DrawTextureEx(worldMap, wmPos, 0.0, 4.0, WHITE);

        EndDrawing();
    }

    CloseWindow();
    UnloadTexture(worldMap);
}