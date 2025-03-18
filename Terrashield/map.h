#ifndef MAP_H
#define MAP_H

#include <QGraphicsPixmapItem>
#include <QObject>

#include "player.h"
#include "element.h"
#include "finish.h"


class Map
{
public:

    //inicializa os atributos de um objeto mapa qualquer
    Map();

    //remove tudo do mapa
    ~Map();

    //Gera o primeiro mapa
    void generateMap1();

    //gera o segundo mapa
    void generateMap2();

    //gera o terceiro mapa
    void generateMap3();

    //cria um mapa a partir de um arquivo
    bool readmap(QString directory);

    //deleta os objetos usados para criar o mapa
    void clearMap();

    //salva o mapa em um arquivo
    bool saveMap(QString directory);

    //retorna uma lista de elementos
    QList<Element *> * getElementList() const;

    //retorna uma lista de units
    QList<Unit *> * getUnitList() const;


    //retorna um player*
    Player *getPlayer() const;

    //retorna uma linha de chegada
    Finish *getFinish() const;

    //retorna um background
    QImage getBackground() const;

    //retorna width
    int getWidth() const;

    //retorna height
    int getHeight() const;

    //Seta um background
    void setBackground(const QImage &value);

    //retorna uma lista de fases
    static QList<QString> getLevels();

    QString getName() const;


    int getDifficulty() const;

private:

    QImage background;

    QString backgroundPath;

    //o player do mapa
    Player * player;

    //o finish do mapa
    Finish * finish;

    //lista de elementos do mapa
    QList<Element *> * elementList;

    //lista de units do mapa
    QList<Unit *> * unitList;




    //largura do mapa
    int width;

    //altura do mapa
    int height;

    //nome do mapa
    QString name;

    //dificuldade
    int difficulty;
};

#endif // MAP_H
