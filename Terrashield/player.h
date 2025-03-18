#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QGraphicsItem>
#include <QKeyEvent>
#include <QTimer>
#include <QDebug>

#include "unit.h"

class Player : public Unit{
    Q_OBJECT
public:

    Player();

    //faz o player pular
    void jump();

    //faz o player quicar ao cair em cima de um inimigo
    void bounce();

    //muda as vidas do player
    void setLife(int value);




};

#endif // PLAYER_H
