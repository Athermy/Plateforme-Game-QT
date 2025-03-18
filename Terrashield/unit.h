#ifndef UNIT_H
#define UNIT_H

#include <QTimer>
#include "element.h"


class Unit : public Element
{
    Q_OBJECT
public:

    Unit();

    //seta o atributo de estado movingRight
    void SetMovingRight(bool state);

    //seta o atributo de estado movingLeft
    void SetMovingLeft(bool state);

    //retorna o valor do atributo flying
    bool isFlying() const;

    //retorna o valor do atributo falling
    bool isFalling() const;

    //retorna o valor do atributo jumping
    bool isJumping() const;

    //retorna weight
    int getWeight() const;

    //retorna valor do atributo movingLeft
    bool isMovingLeft() const;

    //retorna valor do atributo movingRight
    bool isMovingRight() const;

    //retorna valor do atributo yForce
    float getYForce() const;

    //Seta o valor da yForce
    void setYForce(float value);

    //retorna o valor do atributo xForce
    float getXForce() const;

    //seta a xForce
    void setXForce(float value);

    //atualiza todos os atributos de um objeto Unit
    void updateMovementStates();

    //aumenta a velocidade de movimentação para a esquerda até a máxima velocidade
    void increaseLeftForce();

    //aumenta a velocidade de movimentação para a direita até a máxima velocidade
    void increaseRightForce();

    //diminui a velocidade do player em movimento até ele parar
    void decreaseXForce();

    //retorna o valor do atributo fixed
    bool getFixed() const;

    //afeta o dano recebido
    void receiveDammage(int dammage);

    //afeta o dano causado
    void attack(Unit * unit);

    //retorna valor do atributo alive
    bool isAlive() const;

    //retorna o valor do atributo immune
    bool getImmune() const;

    //seta o valor do atributo immune
    void setImmune(bool value);

    //retorna timer de imunidade
    QTimer *getImmuneTimer() const;

public slots:

    //remove a imunidade
    virtual void disableImmune();


protected :

    //true se player está voando
    bool flying;

    //true se player está caindo
    bool falling;

    //true se player está pulando
    bool jumping;

    //true se player está parado
    bool fixed;

    //velocidade vertical
    float yForce;

    //velocidade horizontal
    float xForce;

    //aceleração em x
    float xAcceleration;

    int weight;

    //true se estiver se movendo para a esquerda
    bool movingLeft;

    //true se estiver se movendo para a direita
    bool movingRight;

    //máxima velocidade do objeto unit
    int maxSpeed;

    //true se o objeto estiver vivo
    bool alive;

    //true se o objeto está imune
    bool immune;

    //timer de imunidade
    QTimer * immuneTimer;


};

#endif // UNIT_H
