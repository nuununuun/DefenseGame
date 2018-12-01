#ifndef __OFFENSE_INTERFACE_H__
#define __OFFENSE_INTERFACE_H__

#include "cocos2d.h"

class OffenseInterface : public cocos2d::Layer
{
public:
	OffenseInterface();
	virtual ~OffenseInterface();

	bool init(cocos2d::Scene* parent);
	bool isContain(cocos2d::Sprite* sprite, cocos2d::Point);

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	//void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	//void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	//void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
private:
	cocos2d::Sprite* kenny;
	cocos2d::Sprite* jenny;
};

#endif