#include "OffenseInterface.h"
#include "Constant.h"
#include "PathFinding.h"

#include "MainScene.h"

#include <vector>

USING_NS_CC;

OffenseInterface *OffenseInterface::create(MainScene *parent) {
	auto ret = new (std::nothrow) OffenseInterface();
	if (ret && ret->init(parent)) {
		ret->autorelease();
	}
	else CC_SAFE_DELETE(ret);

	return ret;
}

bool OffenseInterface::init(MainScene* parent)
{
	interfaceKenny = Sprite::create("res/kenny.png");
	interfaceKenny->setPosition(Vec2(336, 48) * 0.5f + Vec2(336, 0));
	parent->addChild(interfaceKenny);
	
	interfaceJenny = Sprite::create("res/jenny.png");
	interfaceJenny->setPosition(Vec2(336, 48) * 0.5f + Vec2(336 + 48 * 2, 0));
	parent->addChild(interfaceJenny);

	parentScene = parent;

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

void OffenseInterface::addUnit(Sprite* unit)
{
	arrUnit.push_back(unit);
}

void OffenseInterface::addKenny(float dt)
{
	Size winSize = Director::getInstance()->getWinSize();

	spriteKenny = Sprite::create("res/kenny.png");
	setFirstPosition(spriteKenny);
	spriteKenny->setAnchorPoint(Vec2(0.5f, 0.5f));
	spriteKenny->setScale(0.5f);

	Vec2 entryPos = parentScene->getGridPosition(spriteKenny->getPosition());
	std::vector<Vec2> path = parentScene->pathFinder->getShortestPath(entryPos, Vec2(16, 6));
	
	parentScene->addChild(spriteKenny);

	Vector<FiniteTimeAction*> acts;
	for (int i = 0; i < path.size(); i++)
	{
		MoveTo* moveTo = MoveTo::create(0.5f, parentScene->getRealPosition(path[i]));
		acts.pushBack(moveTo);
	}
	//CallFuncN* callfunc = CallFuncN::create(CC_CALLBACK_1(OffenseInterface::selfRemover, this));
	//acts.pushBack(callfunc);

	auto act = Sequence::create(acts);
	auto rep = RepeatForever::create(act);

	spriteKenny->runAction(rep);
	addUnit(spriteKenny);
}

void OffenseInterface::setFirstPosition(Sprite* sprite)
{
	Size winSize = Director::getInstance()->getWinSize();

	//float xPos = rand() % (int)winSize.width + 500;
	//float yPos = rand() % (int)winSize.height;

	//sprite->setPosition(xPos, yPos);
	//sprite->setAnchorPoint(Vec2(0.5, 0.5));
	
	Vec2 pos(parentScene->getRealPosition(Vec2(0, 6)));
	sprite->setPosition(pos);
}

void OffenseInterface::selfRemover(Node* sender)
{
	sender->removeFromParentAndCleanup(true);
}

bool OffenseInterface::onTouchBegan(Touch* touch, Event* event)
{
	auto touchPoint = touch->getLocation();

	CCLOG("onTouchBegan id = %d, x = %f, y = %f",
		touch->getID(), touchPoint.x, touchPoint.y);

	isContain(interfaceKenny, touchPoint);
	isContain(interfaceJenny, touchPoint);
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