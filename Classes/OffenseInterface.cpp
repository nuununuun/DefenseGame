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

void OffenseInterface::addJenny()
{
	Size winSize = Director::getInstance()->getWinSize();

	spriteJenny = Sprite::create("res/Flying_eye_R.png");
	spriteJenny->setTextureRect(Rect(0, 0, 32, 32));
	setFirstPosition(spriteJenny);
	spriteJenny->setAnchorPoint(Vec2(0.5f, 0.5f));
//	spriteJenny->setScale(0.5f);

	SpriteFrameCache* frameCache = SpriteFrameCache::getInstance();
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.3f);

	for (int i = 0; i < 10; i++)
	{
		frameCache->addSpriteFrame(SpriteFrame::createWithTexture(spriteJenny->getTexture(), Rect(32 * i, 0, 32, 32)), "res/Flying_eye_R.png");
		animation->addSpriteFrameWithTexture(spriteJenny->getTexture(), Rect(32 * i, 0, 32, 32));
	}

	Animate* animate = Animate::create(animation);

	Vec2 entryPos = parentScene->getGridPosition(spriteJenny->getPosition());
	std::vector<Vec2> path = parentScene->pathFinder->getShortestPath(entryPos, Vec2(16, 6));

	parentScene->addChild(spriteJenny);

	Vector<FiniteTimeAction*> moves;
	for (int i = 0; i < path.size(); i++)
	{
		MoveTo* moveTo = MoveTo::create(0.5f, parentScene->getRealPosition(path[i]));
		moves.pushBack(moveTo);
	}
	CallFuncN* callfunc = CallFuncN::create(CC_CALLBACK_1(OffenseInterface::selfRemover, this));
	//acts.pushBack(callfunc);
	//acts.pushBack(animate);
	auto moveSeq = Sequence::create(moves);
	Vector<FiniteTimeAction*> actions;
	actions.pushBack(moveSeq);
	actions.pushBack(animate);
	actions.pushBack(callfunc);

	auto act = Spawn::create(actions);
	auto rep = RepeatForever::create(act);

	spriteJenny->runAction(rep);
	addUnit(spriteJenny);
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
	if (isContain(interfaceJenny, touchPoint))
		addJenny();
}

void OffenseInterface::onMouseUp(EventMouse *e) {
}

void OffenseInterface::onMouseMove(EventMouse *e) {
}