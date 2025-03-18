#include "enemy.h"
#include "configuration.h"

Enemy::Enemy() : Unit()
{
    width = ENEMY_WIDTH;
    height = ENEMY_HEIGHT;

    // set graphic
    QPixmap MushRoom = QPixmap(":/resources/images/enemy.png");
    MushRoom = MushRoom.scaled(64,64);
    setPixmap(MushRoom);

    // set graphic
    QPixmap BlueBird = QPixmap(":/resources/images/enemy.png");
    BlueBird = BlueBird.scaled(64,64);
    setPixmap(BlueBird);

    // set graphic
    QPixmap Plant = QPixmap(":/resources/images/enemy.png");
    Plant = Plant.scaled(88,84);
    setPixmap(Plant);

    // Accept collision with transparent pixels
    this->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

    type = "enemy";
}
