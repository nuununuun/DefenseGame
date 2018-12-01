#ifndef __OFFENSE_INTERFACE_H__
#define __OFFENSE_INTERFACE_H__

#include "cocos2d.h"
#include "PathFinding.h"
#include <vector>

class MainScene;

class OffenseInterface : public cocos2d::Layer
{
public:
	static OffenseInterface *create(MainScene *parent);

	bool init(MainScene* parent);
	bool isContain(cocos2d::Sprite* sprite, cocos2d::Point);

	void addKenny(float dt);
	void addUnit(cocos2d::Sprite* unit);

	void setFirstPosition(cocos2d::Sprite* sprite);
	void selfRemover(cocos2d::Node* sender);

	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	//void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	//void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	//void onTouchCancelled(cocos2d::Touch* touch, cocos2d::Event* event);
private:
	std::vector<cocos2d::Sprite*> arrUnit;
	cocos2d::Sprite* interfaceKenny;
	cocos2d::Sprite* interfaceJenny;

	cocos2d::Sprite* spriteKenny;
	cocos2d::Sprite* spriteJenny;

	MainScene* parentScene;
};

#endif