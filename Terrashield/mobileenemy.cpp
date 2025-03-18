#include "mobileenemy.h"

MobileEnemy::MobileEnemy() : Enemy()
{
    setSprite("C:/Users/chenc/Desktop/Work/Développement Objets/Projet Développement Objets 2D Platformes/Hostile/Mushroom/Mushroom Run.png");
    type = "mobileEnemy";
    isRightSide = true;
    setXForce(20);
}

void MobileEnemy::switchSide()
{
    if(isRightSide){
        isRightSide = false;
        setXForce(-20);
    }
    else{
        isRightSide = true;
        setXForce(20);
    }
}
