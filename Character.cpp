#include "Character.h"
#include "raymath.h"

Character::Character( int winWidth, int winHeight) : 
    windowWidth(winWidth),
    windowHeight(winHeight)
{
    width = texture.width / maxFrames;
    height = texture.height;
}

Vector2 Character::getScreenPos(){
    return Vector2{
        static_cast<float>(windowWidth) / 2.0f - scaling * (0.5f * width),
        static_cast<float>(windowHeight) / 2.0f - scaling * (0.5f * height)};
    }

void Character::tick(float deltaTime){

    if(!getAlive()) return;
    // Puoi tenere il codice più compatto se usi gli if mettendo il codice da eseguire dopo la condizione senza
    // graffe e sulla stessa linea dell'if

    if (IsKeyDown(KEY_A)) velocity.x -= 1.0;
    if (IsKeyDown(KEY_D)) velocity.x += 1.0;
    if (IsKeyDown(KEY_W)) velocity.y -= 1.0;
    if (IsKeyDown(KEY_S))velocity.y += 1.0;  

    BaseCharacter::tick(deltaTime);

    Vector2 origin{};
    Vector2 offset {};
    float rotation{};
    // Check if facing right
    if (rightLeft > 0.f){
        origin = {0.f, weapon.height * scaling};
        offset = {45.f, 55.f};
        weaponCollisionRec = {
            getScreenPos().x + offset.x,
            getScreenPos().y + offset.y - weapon.height * scaling,
            weapon.width * scaling,
            weapon.height * scaling,
        };
       rotation = IsKeyDown(KEY_SPACE) ? 35.f : 0.f;
    }
    // Check if facing left
    else{
        origin = {weapon.width * scaling, weapon.height * scaling};
        offset = {19.f, 55.f};

        weaponCollisionRec = {
            getScreenPos().x + offset.x - weapon.width * scaling,
            getScreenPos().y + offset.y - weapon.height * scaling,
            weapon.width * scaling,
            weapon.height * scaling
            };
        rotation = IsKeyDown(KEY_SPACE) ? -35.f : 0.f;
    }
    
    //draw sword
    Rectangle source { 0.f, 0.f, static_cast<float>(weapon.width) * rightLeft, static_cast<float>(weapon.height)};
    Rectangle dest {getScreenPos().x + offset.x, getScreenPos().y + offset.y, weapon.width * scaling, weapon.height * scaling};
    DrawTexturePro(weapon, source, dest, origin, rotation, WHITE);

    DrawRectangleLines(weaponCollisionRec.x, weaponCollisionRec.y, weaponCollisionRec.width, weaponCollisionRec.height, RED);
}

void Character::takeDamage(float damage)
{
    health -= damage;
    if (health <= 0.f) setAlive(false);
}