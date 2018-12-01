#ifndef __OFFENSE_UNIT_H_
#define __OFFENSE_UNIT_H_

#include "cocos2d.h"

enum UNIT_TYPE {
	RUSH = 0,
	HEALTH,
	SELF_DESTRUCT
};

enum UNIT_COST {
	COST_FLYING_EYE = 2,
	COST_BABY,
	COST_FINGER,
	COST_HEART,
	COST_RIB,
	COST_TOOTH,
	COST_CAECUM,
	COST_FIST
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
	int attackDamage;
	int cost;
	int speed;
};

#endif