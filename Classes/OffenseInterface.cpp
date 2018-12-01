#include "OffenseInterface.h"

USING_NS_CC;

OffenseInterface::OffenseInterface()
{

}

OffenseInterface::~OffenseInterface()
{
}

bool OffenseInterface::init(Scene* parent)
{
	kenny = Sprite::create("res/kenny.png");
	kenny->setPosition(Vec2(336, 48) * 0.5f + Vec2(336, 0));
	parent->addChild(kenny);
	
	jenny = Sprite::create("res/jenny.png");
	jenny->setPosition(Vec2(336, 48) * 0.5f + Vec2(336 + 48 * 2, 0));
	parent->addChild(jenny);

	return true;
}

bool OffenseInterface::isContain(Sprite* sprite, Point point)
{
	if (sprite->getBoundingBox().containsPoint(point))
	{
		CCLOG("Touched!");
		return true;
	}

	return false;
}

bool OffenseInterface::onTouchBegan(Touch* touch, Event* event)
{
	auto touchPoint = touch->getLocation();

	CCLOG("onTouchBegan id = %d, x = %f, y = %f",
		touch->getID(), touchPoint.x, touchPoint.y);

	isContain(kenny, touchPoint);
	isContain(jenny, touchPoint);
	//bool bTouch = pMan->getBoundingBox().containsPoint(touchPoint);

	return true;
}

/*
void OffenseInterface::onTouchMoved(Touch* touch, Event* event)
{
	auto touchPoint = touch->getLocation();

	CCLOG("onTouchMoved id = %d, x = %f, y = %f",
		touch->getID(), touchPoint.x, touchPoint.y);
}

void OffenseInterface::onTouchEnded(Touch* touch, Event* event)
{
	auto touchPoint = touch->getLocation();

	CCLOG("onTouchEnded id = %d, x = %f, y = %f",
		touch->getID(), touchPoint.x, touchPoint.y);
}

void OffenseInterface::onTouchCancelled(Touch* touch, Event* event)
{

}
*/