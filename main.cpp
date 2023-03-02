#include "raylib.h"
#include "raymath.h"
#include "Character.h"
#include "Prop.h"
#include "Enemy.h"
 

int main(){
      
        int windowDimension[2];
        windowDimension[0] = 384;
        windowDimension[1] = 384;

        InitWindow(windowDimension[0], windowDimension[1], "RPG");

        Texture2D worldMap = LoadTexture("textures/winter-map.png");
        Vector2 wmPos{0.0, 0.0};
        const float mapScale{4.0f};
        
        Character knight {windowDimension[0], windowDimension[1]};
        Prop props[2]{
            Prop{Vector2{300.f, 300.f}, LoadTexture("textures/Rock.png")},
            Prop{Vector2{500.f, 400.f}, LoadTexture("textures/Sign.png")},
        };

        Enemy goblin {
            Vector2{0.f, 0.f}, //posizione del mostro
            LoadTexture("textures/goblin_idle_spritesheet.png"), //Texture statica
            LoadTexture("textures/goblin_run_spritesheet.png")
        };

        goblin.setTarget(&knight);

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

            //PropRrender
            for (auto prop : props)
            {
                prop.Render(knight.getWolrdPos());
            }
            
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

            //check prop collision
            for (auto prop : props)
            {
                if (CheckCollisionRecs(prop.getCollisionRec(knight.getWolrdPos()), knight.getCollisionRec()))
                {
                    knight.undoMovement();
                };       
            }
            
            //EnemyDrawing
            goblin.tick(GetFrameTime());

            //Check Enemy Collision With Weapon
            if(IsKeyPressed(KEY_SPACE)){
               if( CheckCollisionRecs(goblin.getCollisionRec(), knight.getWeaponCollisionRec())){
                goblin.setAlive(false);
             }
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