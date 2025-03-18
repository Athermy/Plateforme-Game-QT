#ifndef PAUSEGROUP_H
#define PAUSEGROUP_H

#include <QGraphicsItemGroup>
#include "menubutton.h"

class PauseGroup : public QGraphicsItemGroup
{
public:

    PauseGroup();

    ~PauseGroup();

    MenuButton *getContinueBtn() const;

    MenuButton *getBackMenuBtn() const;

private:

    //botão para continuar o jogo
    MenuButton * continueBtn;

    //botão para retornar ao menu principal
    MenuButton * backMenuBtn;

    QGraphicsTextItem * title;
};

#endif // PAUSEGROUP_H
