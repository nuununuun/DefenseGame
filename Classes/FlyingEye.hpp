#ifndef __FLYING_EYE_H_
#define __FLYING_EYE_H_

#include "cocos2d.h"

class MainScene;
class FlyingEye
{
public:
	FlyingEye();
	static FlyingEye* create();
	bool init();

	void addSelf(MainScene *parent);
	void selfRemover(cocos2d::Node* sender);
private:
	cocos2d::Sprite *sprite;
	int attackDamage = 2;
	int health = 2;
	int speed = 4;
	int cost = 2;
};

#endif