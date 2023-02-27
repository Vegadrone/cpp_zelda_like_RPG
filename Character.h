#include "raylib.h"

class Character
{
    public:
        //Costruttore
        Character();
        Vector2 getWolrdPos()
        {
            return worldPos;
        }
        void setScreenPos(int winWidth, int winHeight );
        void tick(float deltaTime);

    private:
        Texture2D texture{LoadTexture("textures/knight_idle_spritesheet.png")};
        Texture2D idle{LoadTexture("textures/knight_idle_spritesheet.png")};
        Texture2D run{LoadTexture("textures/knight_run_spritesheet.png")};
        Vector2 screenPos{};
        Vector2 worldPos{};
        // Direzione Sprite a sx -1, direzione sscaling prite a dx 1
        float rightLeft = 1.f;
        // animation update
        float runningTime{};
        float updateTime{1.f / 12.f};
        int frame{};
        int maxFrames{6};
        float speed{4.f};
        float scaling = 4.0f;
        float width{};
        float height{};
};