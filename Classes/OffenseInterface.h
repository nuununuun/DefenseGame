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

	void addKenny();
	void addFlying_eye();

	void addUnit(cocos2d::Sprite* unit);

	void setFirstPosition(cocos2d::Sprite* sprite);
	void selfRemover(cocos2d::Node* sender);

	virtual void onMouseDown(cocos2d::EventMouse *e);
	virtual void onMouseUp(cocos2d::EventMouse *e);
	virtual void onMouseMove(cocos2d::EventMouse *e);

private:
	std::vector<cocos2d::Sprite*> arrUnit;
	cocos2d::Sprite* interfaceKenny;
	cocos2d::Sprite* interfaceFlying_eye;

	cocos2d::Sprite* spriteKenny;
	cocos2d::Sprite* spriteFlying_eye;

	MainScene* parentScene;
};

#endif