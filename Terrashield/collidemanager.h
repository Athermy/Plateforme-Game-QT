#ifndef COLLIDEMANAGER_H
#define COLLIDEMANAGER_H

#include "unit.h"
#include <QMap>
#include <QGraphicsItem>

struct fromPosition
{
    bool fromTop;
    bool fromUnder;
    bool fromRight;
    bool fromLeft;
};

//permite a colisão dos objetos da classe Player com os da classe Element
template <class itemType>
class CollideManager{

public:

    // Construtor da classe CollideManager
    //os parâmetros retém a posição inicial do player antes dele se mover
    CollideManager(Unit * subject, bool solidTop, bool solidLeft, bool solidRight, bool solidUnder);

    //ajusta a posição do indivíduo se ele entra em contato com um bloco
    void updateCollidingPosition();

    //Retorna o valor do atributo areColliding
    bool getAreColliding() const;

    // Retorna uma lista de elementos em colisão com o indivíduo player
    QMap<itemType *, fromPosition> getCollidingItemList() const;

private:

    //objeto em colisão
    Unit * subject;

    //lista de objetos colididos
    QMap<itemType *,fromPosition> collidingItemList;

    //assume true se o indivíduo está em colisão
    bool areColliding;

    //assume true se a colisão é no topo do objeto
    bool solidTop;

    //assume true se a colisão é na esquerda do objeto
    bool solidLeft;

    //assume true se a colisão é à direita do objeto
    bool solidRight;

    //assume true se a colisão é por baixo do objeto
    bool solidUnder;

    //a coordenada y na hora da colisão
    int prec_y;

    //a coordenada x na hora da colisão
    int prec_x;
};

#endif // COLLIDEMANAGER_H
