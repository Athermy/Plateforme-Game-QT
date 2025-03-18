#include "wall.h"
#include "configuration.h"

Wall::Wall() : FixedBlock()
{
    QPixmap blocSprite = QPixmap(":/resources/images/Box.png");
    blocSprite = blocSprite.scaled(BLOC_SIZE,BLOC_SIZE);
    setPixmap(blocSprite);

    width = BLOC_SIZE;
    height = BLOC_SIZE;

    // Accept collision with transparent pixels
    this->setShapeMode(QGraphicsPixmapItem::BoundingRectShape);

    type = "wall";

}
