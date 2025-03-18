#include "consumables.h"

Consumables::Consumables()
{
    durationOfEffect = 0;

}

void Consumables::setDurationOfEffect(int value){
    durationOfEffect = value;
}

int Consumables::getDurationOfEffect() const{
    return durationOfEffect;
}
