#ifndef MOBILEENEMY_H
#define MOBILEENEMY_H

#include "enemy.h"

class MobileEnemy : public Enemy
{
public:

    MobileEnemy();

    //troca a direção do inimigo
    void switchSide();
};

#endif // MOBILEENEMY_H
