#include "OffenseUnit.h"

OffenseUnit::OffenseUnit() : body(NULL), maxEnergy(100), curEnergy(0), eUnitType(RUSH), isEnermy(true), attackDamage(0)
{
}

OffenseUnit::~OffenseUnit()
{
    release();
}

void OffenseUnit::release()
{
    if(NULL != body)
    {
        body->removeFromParentAndCleanup(true);
        body = NULL;
    }
}

void OffenseUnit::setEnergy(float max)
{
    maxEnergy = curEnergy = max;
}

float OffenseUnit::subEnergy(float damage)
{
    curEnergy -= damage;
    if(curEnergy < 0)
        curEnergy = 0;
    return curEnergy;
}