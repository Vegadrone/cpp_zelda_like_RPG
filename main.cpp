#include "raylib.h"
#include "raymath.h"
#include "Character.h"
 

int main(){
      
        int windowDimension[2];
        windowDimension[0] = 384;
        windowDimension[1] = 384;

        InitWindow(windowDimension[0], windowDimension[1], "RPG");

        Texture2D worldMap = LoadTexture("textures/winter-map.png");
        Vector2 wmPos{0.0, 0.0};
        const float mapScale{4.0f};
        
        Character knight {windowDimension[0], windowDimension[1]};

        // FPS
        SetTargetFPS(60);
        // Game Loop
        while (!WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(WHITE);

            wmPos = Vector2Scale(knight.getWolrdPos(), -1.f); 

            // map drawing
            DrawTextureEx(worldMap, wmPos, 0.0, mapScale, WHITE);

            //Character Drawing
            knight.tick(GetFrameTime());
            //Hit map bound check
            if( 
                knight.getWolrdPos().x < 0.f ||
                knight.getWolrdPos().y < 0.f ||
                knight.getWolrdPos().x + windowDimension[0] > worldMap.width * mapScale ||
                knight.getWolrdPos().y + windowDimension[1] > worldMap.height * mapScale
            ){
                knight.undoMovement();
            }

            /*La mia soulzione al problema di animare il pupino

            Rectangle source{frame * (float)knight_idle.width / frameInSpriteSheet, 0.f, rightLeft * (float)knight_idle.width / frameInSpriteSheet, (float)knight_idle.height};
            Rectangle dest{knightPos.x, knightPos.y, scaling * (float)knight_idle.width / frameInSpriteSheet, scaling * (float)knight_idle.height};

            Rectangle source_run{frame * (float)knight_run.width / frameInSpriteSheet, 0.f, rightLeft * (float)knight_run.width / frameInSpriteSheet, (float)knight_run.height};
            Rectangle dest_run{knightPos.x, knightPos.y, scaling * (float)knight_run.width / frameInSpriteSheet, scaling * (float)knight_run.height};

            if (direction.x || direction.y != 0)
            {
                 DrawTexturePro(knight_run, source_run, dest_run, Vector2{}, 0.f, WHITE);
            }
            else
            {
                 DrawTexturePro(knight_idle, source, dest, Vector2{}, 0.f, WHITE);
            }*/

            EndDrawing();
    }

    CloseWindow();
    UnloadTexture(worldMap);
}