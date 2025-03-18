#include "menu.h"
#include "configuration.h"
#include "qgraphicsitem.h"
#include "map.h"
#include <QStyleHints>

Menu::Menu() : QGraphicsScene()
{
    int xButton = 200;
    int yStartButton = 300;
    //Cria scene com background
    this->setSceneRect(0,0,MAP_WIDTH,MAP_HEIGHT);
    QImage background = QImage(":/resources/images/backgrounds/bg1.png");
    background = background.scaledToHeight(WINDOW_HEIGHT);
    this->setBackgroundBrush(background);

    //Mostra botões das fases
    int index = 0;
    foreach (QString world, Map::getLevels() ){
        MenuButton * button = new MenuButton(world);
        button->move(xButton,yStartButton + index * (button->height() + BTN_GAP));
        buttonList.append(button);
        this->addWidget(button);
        index ++;
    }

    //Mostra botão Quit
    QuitBtn= new MenuButton("Quit");
    QuitBtn->move(xButton,yStartButton + index * (QuitBtn->height() + BTN_GAP));
    this->addWidget(QuitBtn);

    //Imagem do player
    QGraphicsPixmapItem * playerImage = new QGraphicsPixmapItem();
    QPixmap img = QPixmap(":/resources/images/player/p1.png");
    img = img.scaled(600,600);
    playerImage->setPixmap(img);
    playerImage->setPos(890,290);
    this->addItem(playerImage);

    //Título do jogo
    QGraphicsTextItem * title = new QGraphicsTextItem();
    title->setPlainText(TITLE);
    QFont font = QFont("Agency FB",100);
    font.setBold(true);
    title->setFont(font);
    title->setPos(910,120); //900x200
    this->addItem(title);
}

Menu::~Menu()
{
    foreach(QPushButton * btn,buttonList){
        delete btn;
    }
    buttonList.clear();
    delete QuitBtn;
}

QList<MenuButton *> Menu::getButtonList() const
{
    return buttonList;
}

MenuButton *Menu::getQuitBtn() const
{
    return QuitBtn;
}
