#ifndef ELEMENT_H
#define ELEMENT_H

#include <QGraphicsPixmapItem>
#include <QObject>
#include <QMutex>

//Estrutura básica dos elementos do mapa
class Element :  public QObject, public QGraphicsPixmapItem
{
public:

    //Construtor que reseta altura e largura do elemento pra 0
    Element();

    //Construtor sobrecarregado que inicializa altura e largura do elemento com os valores passados
    Element(int height,int width);

    //Retorna a largura
    int getWidth() const;

    //Seta a largura
    void setWidth(int value);

    //Retorna a altura
    int getHeight() const;

    //Seta a altura
    void setHeight(int value);

    //Seta o sprite
    void setSprite(QString ressource);

    //Retorna o atributo type do objeto Element como Qstring
    QString getType() const;

    //Seta o type do objeto Element
    void setType(const QString &value);

    //Retorna o spawn x em int do objeto Element
    int getSpawnX() const;

    //Seta o spawn x em int do objeto Element
    void setSpawnX(int value);

    //Retorna o spawn y do objeto Element
    int getSpawnY() const;

    //Seta o spawn y do objeto Element
    void setSpawnY(int value);

    //Respawna um Element
    void respawn();

    //Retorna se o objeto está para o lado direito a partir do atributo isRightSide
    int getIsRightSide() const;

    //Seta se o objeto está ou não para o lado direito (0 ou 1)
    void setIsRightSide(int value);

protected:

    int width;

    int height;

    //1 - está para o lado direito, 0 - está para o esquerdo
    int isRightSide;

    //tipo do element
    QString type;

    //posição x de spawn de um elemento
    int spawnX;

    //posição y de spawn de um elemento
    int spawnY;
};

#endif // ELEMENT_H
