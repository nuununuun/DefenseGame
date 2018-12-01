#ifndef __OFFENSE_UNIT_H_
#define __OFFENSE_UNIT_H_

#include "cocos2d.h"

enum UNIT_TYPE {
	RUSH = 0,
	HEALTH,
	SELF_DESTRUCT
};

class OffenseUnit
{
public:
	OffenseUnit();
    virtual ~OffenseUnit();
    
    void setEnergy(float max);
    float subEnergy(float damage);
    void release();
    
    cocos2d::Sprite* body;
    
    UNIT_TYPE eUnitType;
    float maxEnergy;
    float curEnergy;
    bool isEnermy;
};

#endif