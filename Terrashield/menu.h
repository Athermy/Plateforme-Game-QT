#ifndef MENU_H
#define MENU_H

#include <QGraphicsScene>
#include "menubutton.h"
#include <QDebug>

class Menu : public QGraphicsScene
{
public:

    Menu();

    ~Menu();

    //retorna lista de botões do menu
    QList<MenuButton *> getButtonList() const;

    MenuButton *getQuitBtn() const;

private:
    //lista de botões do menu
    QList<MenuButton *> buttonList;

    //quit button
    MenuButton * QuitBtn;

};

#endif // MENU_H
