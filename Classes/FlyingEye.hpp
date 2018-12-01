#ifndef __FLYING_EYE_H_
#define __FLYING_EYE_H_

#include "cocos2d.h"

class FlyingEye : public cocos2d::Sprite
{
public:
	static FlyingEye* create();
	bool init();

	void selfRemover(cocos2d::Node* sender);
private:
	int attackDamage = 2;
	int health = 2;
	int speed = 4;
	int cost = 2;
};

#endif