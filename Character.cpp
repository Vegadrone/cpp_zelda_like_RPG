#include "Character.h"
#include "raymath.h"

Character::Character( int winWidth, int winHeight){
    width = texture.width / maxFrames;
    height = texture.height;
    screenPos = {
        static_cast<float>(winWidth) / 2.0f - scaling * (0.5f * width),
        static_cast<float>(winHeight) / 2.0f - scaling * (0.5f * height)};
}

void Character::tick(float deltaTime){
    // Puoi tenere il codice più compatto se usi gli if mettendo il codice da eseguire dopo la condizione senza
    // graffe e sulla stessa linea dell'if
    BaseCharacter::tick(deltaTime);
    
    Vector2 direction{};
    if (IsKeyDown(KEY_A))
        direction.x -= 1.0;
    if (IsKeyDown(KEY_D))
        direction.x += 1.0;
    if (IsKeyDown(KEY_W))
        direction.y -= 1.0;
    if (IsKeyDown(KEY_S))
        direction.y += 1.0;
    if (Vector2Length(direction) != 0.0){
        // set worldPos = worldPos + direction
        // sottrai la posizione della mappa con il vettore direzione normalizzato (1) scalato per la speed
        worldPos = Vector2Add(worldPos, Vector2Scale(Vector2Normalize(direction), speed));
        direction.x < 0.f ? rightLeft = -1.f : rightLeft = 1.f;
        texture = run;
    }
    else{
        texture = idle;
    }
   
}