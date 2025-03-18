#include "pausegroup.h"
#include "configuration.h"

PauseGroup::PauseGroup()
{
    continueBtn = new MenuButton("Continue");
    backMenuBtn = new MenuButton("Menu");

    int yOffset = 120;
    int borderOffset = 50;

    QGraphicsRectItem * rect = new QGraphicsRectItem(0,0,continueBtn->width() + borderOffset, yOffset * 3 + borderOffset);
    rect->setBrush(Qt::white);
    rect->setPos(WINDOW_WIDTH / 2 - continueBtn->width() / 2 - borderOffset/2 ,yOffset - borderOffset/2);
    this->addToGroup(rect);

    title = new QGraphicsTextItem("Pause");
    QFont font = QFont("Agency FB",60);
    font.setBold(true);
    title->setFont(font);
    title->setPos(WINDOW_WIDTH / 2 - 190 / 2,yOffset-10);
    addToGroup(title);

    //Coloca botões no meio da tela
    continueBtn->move(WINDOW_WIDTH / 2 - continueBtn->width() / 2,yOffset * 2);
    backMenuBtn->move(WINDOW_WIDTH / 2 - backMenuBtn->width() / 2, yOffset * 3);


}

PauseGroup::~PauseGroup()
{
    delete continueBtn;
    delete backMenuBtn;
    delete title;
}

MenuButton *PauseGroup::getContinueBtn() const
{
    return continueBtn;
}

MenuButton *PauseGroup::getBackMenuBtn() const
{
    return backMenuBtn;
}
