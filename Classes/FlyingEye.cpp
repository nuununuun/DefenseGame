#include "FlyingEye.hpp"
#include "MainScene.h"

USING_NS_CC;

/*
FlyingEye * FlyingEye::create()
{
	auto ret = new (std::nothrow) FlyingEye();
	if (ret && ret->init()) {	
		ret->autorelease();
	}
	else CC_SAFE_DELETE(ret);

	return ret;
}
*/

FlyingEye::FlyingEye()
{
	init();
}

bool FlyingEye::init()
{
	sprite = Sprite::create("res/Flying_eye_R.png", Rect(0, 0, 32, 32));

	return true;
}

void FlyingEye::addSelf(MainScene *parent)
{
	Size winSize = Director::getInstance()->getWinSize();

	auto textureFlying_eye = Sprite::create("res/Flying_eye_R.png")->getTexture();

	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (int i = 0; i < 10; i++)
		animation->addSpriteFrameWithTexture(textureFlying_eye, Rect(32 * i, 0, 32, 32));

	Animate* animate = Animate::create(animation);

	//auto spriteFlying_eye = Sprite::create("res/Flying_eye_R.png", Rect(0, 0, 32, 32));
	//setFirstPosition(spriteFlying_eye);
	parent->addChild(sprite);

	Vec2 entryPos = parent->getGridPosition(sprite->getPosition());
	std::vector<Vec2> path = parent->pathFinder->getShortestPath(entryPos, Vec2(16, 6));

	Vector<FiniteTimeAction*> moves;
	for (int i = 0; i < path.size(); i++)
	{
		MoveTo* moveTo = MoveTo::create(0.5f, parent->getRealPosition(path[i]));
		moves.pushBack(moveTo);
	}

	CallFuncN* callfunc = CallFuncN::create(CC_CALLBACK_1(FlyingEye::selfRemover, this));
	moves.pushBack(callfunc);

	auto moveSeq = Sequence::create(moves);
	//Vector<FiniteTimeAction*> actions;
	//actions.pushBack(moveSeq);
	//actions.pushBack(animateReapeat);
	//actions.pushBack(callfunc);

	auto animateReapeat = RepeatForever::create(animate);
	auto act = Spawn::create(moveSeq, Repeat::create(animate, 100), NULL);

	sprite->runAction(act);
	//addUnit(spriteFlying_eye);
}

void FlyingEye::selfRemover(Node* sender)
{
	sender->removeFromParentAndCleanup(true);
}