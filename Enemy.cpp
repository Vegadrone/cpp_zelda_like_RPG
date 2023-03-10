#include "Enemy.h"
#include "raymath.h"

Enemy::Enemy(Vector2 pos, Texture2D idle_texture, Texture2D run_texture){

    worldPos = pos;
    texture = idle_texture;
    idle = idle_texture;
    run = run_texture;

    width = texture.width / maxFrames;
    height = texture.height;
    speed = 2.f;
}

void Enemy::tick(float deltaTime)
{
    if (!getAlive()) return;
    //ottenere toTarget Vector
    velocity = Vector2Subtract(target->getScreenPos(), getScreenPos());//vettore distanza tra enemy e knight(target)
    if (Vector2Length(velocity) < radius) velocity = {}; //per non fare glitchare il nemico sul knight

    BaseCharacter::tick(deltaTime);

    if(CheckCollisionRecs(target->getCollisionRec(), getCollisionRec())){
        target->takeDamage(damagePerSec * deltaTime);
    }
}

Vector2 Enemy::getScreenPos(){
    return Vector2Subtract(worldPos, target->getWolrdPos()); // per accedere al secondo vettore da sottrarre (da prendere in Character) uso il puntatore e la ->
}
