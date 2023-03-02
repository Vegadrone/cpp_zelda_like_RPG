
#ifndef BASE_CHARACTER_H //Per la compilazione condizionale. non compila di nuovo la classe se è già definita
#define BASE_CHARACTER_H //Definisce la classe
#include "raylib.h"

class BaseCharacter
{
    public:
        BaseCharacter(/* args */);
        Vector2 getWolrdPos(){
            return worldPos;
        }
        virtual void tick(float deltaTime);
        void undoMovement();
        Rectangle getCollisionRec();
        virtual Vector2 getScreenPos() = 0; // Pure Virtual Function. si dichiarano con = 0 Questo rende BaseCharacter una classe astratta
                                            //e ciò siginifica che non possiamo fare istanze di questa classe ma solo istanze di classi figlie
        bool getAlive(){ return alive;}
        void setAlive(bool isAlive){alive = isAlive;}

    protected:
        Texture2D texture{LoadTexture("textures/knight_idle_spritesheet.png")};
        Texture2D idle{LoadTexture("textures/knight_idle_spritesheet.png")};
        Texture2D run{LoadTexture("textures/knight_run_spritesheet.png")};
        Vector2 worldPos{};
        Vector2 worldPosLastFrame{};
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
        Vector2 velocity {};

    private:
        bool alive{true};
};
#endif //chiude la compilazione condizionale
