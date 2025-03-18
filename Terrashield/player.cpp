#include "player.h"
#include "configuration.h"

Player::Player() : Unit()
{
    width = PLAYER_WIDTH;
    height = PLAYER_HEIGHT;

    setSprite(":/resources/images/player/p1.png");
    type = "player";

    // Accept collision with transparent pixels
    this->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

}

void Player::jump()
{
    if(flying == false){
        yForce = -900;
        updateMovementStates();
    }
}

void Player::bounce()
{
    yForce = -800;
    updateMovementStates();
}
