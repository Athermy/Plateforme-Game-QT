#ifndef CONSUMABLES_H
#define CONSUMABLES_H

#include "configuration.h"
#include "element.h"
#include "unit.h"

class Consumables: public Element
{
public:

    //Consumíveis
    //só reseta a duração do efeito para 0
    Consumables();

    //retorna o valor de DurationOfEffect
    int getDurationOfEffect() const;

    //seta o valor de DurationOfEffect
    void setDurationOfEffect(int value);

    virtual void applyEffect(Unit * unit)=0;

private:

    int durationOfEffect;
};

#endif // CONSUMABLES_H
