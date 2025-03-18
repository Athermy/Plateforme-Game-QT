#include "collidemanager.h"

template<class itemType>
CollideManager<itemType>::CollideManager(Unit *subject, bool solidTop, bool solidLeft, bool solidRight, bool solidUnder)
{
    this->subject = subject;
    this->solidTop = solidTop;
    this->solidLeft = solidLeft;
    this->solidRight = solidRight;
    this->solidUnder = solidUnder;

    areColliding = false;

    prec_x = subject->x();
    prec_y = subject->y();
}

template<class itemType>
void CollideManager<itemType>::updateCollidingPosition()
{
    int next_x = subject->x();
    int next_y = subject->y();

    //pega uma lista de todos os itens colidindo com o player no momento
    QList<QGraphicsItem *> colliding_items = subject->collidingItems();
    QList<itemType *> collidingItemList;
    itemType * collidedItem = NULL;

    for(QGraphicsItem * item : colliding_items){
        itemType * specificItem = dynamic_cast<itemType *>(item);

        if(specificItem){
            collidingItemList.append(specificItem);
            areColliding = true;
        }
    }

    if (collidingItemList.count() > 0 && areColliding){
        for(int i = 0 ; i < collidingItemList.count() ; i ++){
            collidedItem = collidingItemList[i];

            // posição do bloco
            int bloc_y = collidedItem->y();
            int bloc_x = collidedItem->x();

            // última posição
            bool fromTop = false;
            bool fromUnder = false;
            bool fromRight = false;
            bool fromLeft = false;

            if( prec_y + subject->getHeight() - 1 <= bloc_y)
                fromTop = true;
            if( prec_y - collidedItem->getHeight() >= bloc_y)
                fromUnder = true;
            if( prec_x + subject->getWidth() <= bloc_x)
                fromLeft = true;
            if( prec_x >= bloc_x + collidedItem->getWidth() )
                fromRight = true;

            fromPosition positions;
            positions.fromTop = fromTop;
            positions.fromLeft = fromLeft;
            positions.fromRight = fromRight;
            positions.fromUnder = fromUnder;
            this->collidingItemList.insert(collidedItem,positions);


            //Colidindo no topo
            if(solidTop && fromTop && !fromUnder && !fromRight && !fromLeft){
                // Ajusta a posição do player exatamente no bloco
                next_y = bloc_y - subject->getHeight() + 1; // +1 para ficar em contato com o bloco
                subject->setYForce(0);
            }
            // Colidindo embaixo
            else if(solidUnder && subject->isJumping() && !fromTop && fromUnder && !fromRight && !fromLeft ){
                next_y = bloc_y + collidedItem->getHeight() ;
                subject->setYForce( - subject->getYForce() );
            }
            // Colidindo à direita
            else if(solidRight && !fromTop && !fromLeft && !fromUnder && fromRight ){
                // Ajusta a posição do player exatamente ao lado do bloco
                next_x = bloc_x + collidedItem->getWidth() + 1;
                subject->setXForce(0);
            }
            // Colidindo à esquerda
            else if(solidLeft && !fromTop && !fromRight && !fromUnder && fromLeft ){
                // Ajusta a posição do player exatamente ao lado do bloco
                next_x = bloc_x - subject->getWidth() - 1;
                subject->setXForce(0);
            }
            else if (collidingItemList.count() > 1){
                continue;   // se existir outras colisões, então não é em um canto, então pula esses casos
            }
            // Colidindo no canto superior direito
            else if ((solidTop || solidRight) && fromTop == true && fromRight == true){
                next_x = bloc_x + collidedItem->getWidth();
                subject->setXForce(0);
            }
            // Colidindo no canto superior esquerdo
            else if ((solidTop || solidLeft) && fromTop == true && fromLeft == true){
                next_x = bloc_x - subject->getWidth();
                subject->setXForce(0);
            }
            // Colidindo canto inferior direito
            else if ((solidUnder || solidRight) && fromUnder ==  true && fromRight == true && subject->isJumping() == true){
                next_y = bloc_y + collidedItem->getHeight() + 2;
                next_x = bloc_x + collidedItem->getWidth() + 1;
                subject->setYForce( - subject->getYForce());
            }
            // Colidindo canto inferior esquerdo
            else if ((solidUnder || solidLeft) && fromUnder ==  true && fromLeft == true && subject->isJumping() == true){
                next_y = bloc_y + collidedItem->getHeight() ;
                next_x = bloc_x - subject->getWidth() - 1;
                subject->setYForce( - subject->getYForce());
                subject->setXForce(0);
            }
            else{
                // reset speed
                subject->setXForce(10);
            }
        }
        subject->setPos(next_x,next_y);
    }
}

template<class itemType>
bool CollideManager<itemType>::getAreColliding() const
{
    return areColliding;
}

template<class itemType>
QMap<itemType *, fromPosition> CollideManager<itemType>::getCollidingItemList() const
{
    return collidingItemList;
}
