#include "OffenseInterface.h"
#include "Constant.h"
#include "PathFinding.h"

#include "MainScene.h"
#include "FlyingEye.hpp"
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
	
	interfaceFlying_eye = Sprite::create("res/Flying_eye_R.png");
	interfaceFlying_eye->setTextureRect(Rect(0, 0, 32, 32));
	interfaceFlying_eye->setPosition(Vec2(336, 48) * 0.5f + Vec2(336 + 48 * 2, 0));
	parent->addChild(interfaceFlying_eye);

	parentScene = parent;

	//flyingEye = FlyingEye::create(parentScene);
//    parentScene->addChild(flyingEye);
	return true;
}

bool OffenseInterface::isContain(Sprite* sprite, Point point)
{
	if (sprite->getBoundingBox().containsPoint(point))
	{
		CCLOG("Touched!");
		return true;
	}

	CCLOG("sprite x: %f y: %f", sprite->getPosition().x, sprite->getPosition().y);
	return false;
}

void OffenseInterface::addUnit(Sprite* unit)
{
	arrUnit.push_back(unit);
}

void OffenseInterface::addKenny()
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
	CallFuncN* callfunc = CallFuncN::create(CC_CALLBACK_1(OffenseInterface::selfRemover, this));
	acts.pushBack(callfunc);

	auto act = Sequence::create(acts);
	auto rep = RepeatForever::create(act);

	spriteKenny->runAction(rep);
	addUnit(spriteKenny);
}

void OffenseInterface::addFlying_eye()
{
	Size winSize = Director::getInstance()->getWinSize();

	/*
	auto sprite = Sprite::create("res/Flying_eye_R.png");
	auto texture = sprite->getTexture();

	auto animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for(int i=0; i<10; i++)
		animation->addSpriteFrameWithTexture(texture, Rect(32 * i, 0, 32, 32));

	auto pMan = Sprite::create("res/Flying_eye_R.png", Rect(0, 0, 32, 32));
	setFirstPosition(pMan);
	parentScene->addChild(pMan);

	auto animate = Animate::create(animation);
	auto rep = RepeatForever::create(animate);
	pMan->runAction(rep);
	*/
	
	auto textureFlying_eye = Sprite::create("res/Flying_eye_R.png")->getTexture();

	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (int i = 0; i < 10; i++)
		animation->addSpriteFrameWithTexture(textureFlying_eye, Rect(32 * i, 0, 32, 32));

	Animate* animate = Animate::create(animation);

	spriteFlying_eye = Sprite::create("res/Flying_eye_R.png", Rect(0, 0, 32, 32));
	setFirstPosition(spriteFlying_eye);
	parentScene->addChild(spriteFlying_eye);

	Vec2 entryPos = parentScene->getGridPosition(spriteFlying_eye->getPosition());
	std::vector<Vec2> path = parentScene->pathFinder->getShortestPath(entryPos, Vec2(16, 6));

	Vector<FiniteTimeAction*> moves;
	for (int i = 0; i < path.size(); i++)
	{
		MoveTo* moveTo = MoveTo::create(0.5f, parentScene->getRealPosition(path[i]));
		moves.pushBack(moveTo);
	}
	
	CallFuncN* callfunc = CallFuncN::create(CC_CALLBACK_1(OffenseInterface::selfRemover, this));
	moves.pushBack(callfunc);

	auto moveSeq = Sequence::create(moves);
	//Vector<FiniteTimeAction*> actions;
	//actions.pushBack(moveSeq);
	//actions.pushBack(animateReapeat);
	//actions.pushBack(callfunc);

	auto animateReapeat = RepeatForever::create(animate);
	auto act = Spawn::create(moveSeq, Repeat::create(animate, 100), NULL);

	spriteFlying_eye->runAction(act);
	addUnit(spriteFlying_eye);
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

void OffenseInterface::onMouseDown(EventMouse *e) {
	auto touchPoint = e->getLocationInView();

	CCLOG("x = %f, y = %f", touchPoint.x, touchPoint.y);

	if (isContain(interfaceKenny, touchPoint))
		addKenny();
	if (isContain(interfaceFlying_eye, touchPoint))
		addFlying_eye();
}

void OffenseInterface::onMouseUp(EventMouse *e) {
}

void OffenseInterface::onMouseMove(EventMouse *e) {
}
