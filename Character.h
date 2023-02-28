#include "raylib.h"
#include "BaseCharacter.h"

class Character : public BaseCharacter
{
    public:
        //Costruttore
        Character(int winWidth, int winHeight);
        virtual void tick(float deltaTime) override;
     
    private:

};