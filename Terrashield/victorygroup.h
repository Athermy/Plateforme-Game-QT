#ifndef VICTORYGROUP_H
#define VICTORYGROUP_H

#include <QGraphicsItemGroup>
#include "menubutton.h"
#include <QGraphicsTextItem>

class VictoryGroup : public QGraphicsItemGroup
{
public:

    VictoryGroup();

    ~VictoryGroup();

    //retorna o valor do botão retry
    MenuButton *getRetryBtn() const;

    //retorna o valor do botão back to menu
    MenuButton *getBackMenuBtn() const;

private:

    //botão para jogar a fase de novo
    MenuButton * retryBtn;

    //botão para retornar ao menu
    MenuButton * backMenuBtn;

    //Victory
    QGraphicsTextItem * title;
};

#endif // VICTORYGROUP_H
