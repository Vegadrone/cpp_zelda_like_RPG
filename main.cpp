#include "raylib.h"
#include "raymath.h"


class Character {

    public:
        Vector2 getWolrdPos(){
            return worldPos;
        }
        void setScreenPos(int winWidth, int winHeight);
        void tick(float deltaTime);

    private:
        Texture2D texture{LoadTexture("textures/knight_idle_spritesheet.png")};
        Texture2D idle{LoadTexture("textures/knight_idle_spritesheet.png")};
        Texture2D run{LoadTexture("textures/knight_run_spritesheet.png")};
        Vector2 screenPos;
        Vector2 worldPos;
        // Direzione Sprite a sx -1, direzione sscaling prite a dx 1
        float rightLeft = 1.f;
        // animation update
        float runningTime{};
        float updateTime{1.f / 12.f};
        int frame{};
        const int maxFrames{6};
        const float speed {4.f};
        float scaling = 4.0f;
        float frameInSpriteSheet = 6.0f;
};

void Character::setScreenPos(int winWidth, int winHeight){
        screenPos = {
            (float)winWidth / 2.0f - scaling * (0.5f * (float)texture.width / frameInSpriteSheet),
            (float)winHeight / 2.0f - scaling * (0.5f * (float)texture.height)
        };
}

void Character::tick(float deltaTime){
        // Puoi tenere il codice più compatto se usi gli if mettendo il codice da eseguire dopo la condizione senza
        // graffe e sulla stessa linea dell'if

        Vector2 direction{};
        if (IsKeyDown(KEY_A)) direction.x -= 1.0;
        if (IsKeyDown(KEY_D)) direction.x += 1.0;
        if (IsKeyDown(KEY_W)) direction.y -= 1.0;
        if (IsKeyDown(KEY_S)) direction.y += 1.0;
        if (Vector2Length(direction) != 0.0){
            // set worldPos = worldPos + direction
            // sottrai la posizione della mappa con il vettore direzione normalizzato (1) scalato per la speed
            worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
            direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
            texture = run;
        } else {
            texture = idle;
        }
        // update animation frame
        runningTime += deltaTime;
        if (runningTime >= updateTime){
            frame++;
            runningTime = 0.f;
            if (frame > maxFrames) frame = 0;
        }
}

int main(){
        float scaling = 4.0f;
        float frameInSpriteSheet = 6.0f;
        int windowDimension[2];
        windowDimension[0] = 384;
        windowDimension[1] = 384;

        InitWindow(windowDimension[0], windowDimension[1], "RPG");

        Texture2D worldMap = LoadTexture("textures/winter-map.png");
        Vector2 wmPos{0.0, 0.0};
        const float speed = 4.0;

        // Idle and running spritesheets
        Texture2D knight = LoadTexture("textures/knight_idle_spritesheet.png");
        Texture2D knight_idle = LoadTexture("textures/knight_idle_spritesheet.png");
        Texture2D knight_run = LoadTexture("textures/knight_run_spritesheet.png");
        Vector2 knightPos = {
            // C style cast dove casti float
            (float)windowDimension[0] / 2.0f - scaling * (0.5f * (float)knight_idle.width / 6.0f),
            (float)windowDimension[1] / 2.0f - scaling * (0.5f * (float)knight_idle.height)};

        // Direzione Sprite a sx -1, direzione sscaling prite a dx 1
        float rightLeft = 1.f;

        // animation update
        float runningTime{};
        float updateTime{1.f / 12.f};
        int frame{};
        const int maxFrames{6};

        // FPS
        SetTargetFPS(60);
        // Game Loop
        while (!WindowShouldClose())
        {
            BeginDrawing();
            ClearBackground(WHITE);

            // Puoi tenere il codice più compatto se usi gli if mettendo il codice da eseguire dopo la condizione senza
            // graffe e sulla stessa linea dell'if

            Vector2 direction{};
            if (IsKeyDown(KEY_A))
                direction.x -= 1.0;
            if (IsKeyDown(KEY_D))
                direction.x += 1.0;
            if (IsKeyDown(KEY_W))
                direction.y -= 1.0;
            if (IsKeyDown(KEY_S))
                direction.y += 1.0;
            if (Vector2Length(direction) != 0.0)
            {
                // set wmPos = wmPos - direction

                // sottrai la posizione della mappa con il vettore direzione normalizzato (1) scalato per la speed
                wmPos = Vector2Subtract(wmPos, Vector2Scale(Vector2Normalize(direction), speed));
                direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
                knight = knight_run;
            }
            else
            {
                knight = knight_idle;
            }

            // map drawing
            DrawTextureEx(worldMap, wmPos, 0.0, 4.0, WHITE);

            // update animation frame
            runningTime += GetFrameTime();
            if (runningTime >= updateTime)
            {
                frame++;
                runningTime = 0.f;
                if (frame > maxFrames)
                    frame = 0;
            }

            Rectangle source{frame * (float)knight.width / frameInSpriteSheet, 0.f, rightLeft * (float)knight.width / frameInSpriteSheet, (float)knight.height};
            Rectangle dest{knightPos.x, knightPos.y, scaling * (float)knight.width / frameInSpriteSheet, scaling * (float)knight.height};
            DrawTexturePro(knight, source, dest, Vector2{}, 0.f, WHITE);

            // character drawing

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