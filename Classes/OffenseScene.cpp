#include "OffenseScene.h"

USING_NS_CC;
using namespace std;

bool OffenseScene::init() {
	if (!MainScene::init()) return false;

	menuLayer = Layer::create();
	addChild(menuLayer);

	interfaceFlyingEye = Sprite::create("res/Flying_eye_R.png", Rect(0, 0, 32, 32));
	interfaceFlyingEye->setPosition(Vec2(336, 48) * 0.5f + Vec2(336 + 48 * 0, 0));
	interfaceFlyingEye->setScale(1.5f);
	menuLayer->addChild(interfaceFlyingEye);

	interfaceBaby = Sprite::create("res/Baby_R.png", Rect(0, 0, 32, 32));
	interfaceBaby->setPosition(Vec2(336, 48) * 0.5f + Vec2(336 + 48 * 1, 0));
	interfaceBaby->setScale(1.5f);
	menuLayer->addChild(interfaceBaby);

	interfaceFinger = Sprite::create("res/Finger_R.png", Rect(0, 0, 32, 32));
	interfaceFinger->setPosition(Vec2(336, 48) * 0.5f + Vec2(336 + 48 * 2, 0));
	interfaceFinger->setScale(1.5f);
	menuLayer->addChild(interfaceFinger);

	interfaceHeart = Sprite::create("res/Heart_R.png", Rect(0, 0, 32, 32));
	interfaceHeart->setPosition(Vec2(336, 48) * 0.5f + Vec2(336 + 48 * 3, 0));
	interfaceHeart->setScale(1.5f);
	menuLayer->addChild(interfaceHeart);

	interfaceRib = Sprite::create("res/Rib_R.png", Rect(0, 0, 32, 32));
	interfaceRib->setPosition(Vec2(336, 48) * 0.5f + Vec2(336 + 48 * 4, 0));
	interfaceRib->setScale(1.5f);
	menuLayer->addChild(interfaceRib);

	//interfaceUnits.push_back(interfaceFlyingEye);
	scheduleUpdate();

	return true;
}

void OffenseScene::onMouseDown(cocos2d::EventMouse *e) {
	MainScene::onMouseDown(e);
	
	if (interfaceFlyingEye->getBoundingBox().containsPoint(e->getLocationInView()))
		addFlyingEye();
	if (interfaceBaby->getBoundingBox().containsPoint(e->getLocationInView()))
		addBaby();
	if (interfaceFinger->getBoundingBox().containsPoint(e->getLocationInView()))
		addFinger();
	if (interfaceHeart->getBoundingBox().containsPoint(e->getLocationInView()))
		addHeart();
	if (interfaceRib->getBoundingBox().containsPoint(e->getLocationInView()))
		addRib();
}

void OffenseScene::onMouseUp(cocos2d::EventMouse *e) {
	MainScene::onMouseUp(e);

}

void OffenseScene::onMouseMove(cocos2d::EventMouse *e) {
	MainScene::onMouseMove(e);

}

void OffenseScene::update(float dt) {
}

void OffenseScene::selectGrid(const Vec2 &pos) {
	auto gridPosition = getGridPosition(pos);

	mapData.setTileData(gridPosition.x, gridPosition.y, TileType::BARRICADE);

	updateMap();
}

void OffenseScene::setFirstPosition(Sprite* sprite)
{
	Size winSize = Director::getInstance()->getWinSize();

	//float xPos = rand() % (int)winSize.width + 500;
	//float yPos = rand() % (int)winSize.height;

	//sprite->setPosition(xPos, yPos);
	//sprite->setAnchorPoint(Vec2(0.5, 0.5));

	Vec2 pos(this->getRealPosition(Vec2(0, 6)));
	sprite->setPosition(pos);
}

void OffenseScene::selfRemover(Node* sender)
{
	sender->removeFromParentAndCleanup(true);
}

void OffenseScene::addFlyingEye()
{
	Size winSize = Director::getInstance()->getWinSize();

	auto textureFlying_eye = Sprite::create("res/Flying_eye_R.png")->getTexture();
	
	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (int i = 0; i < 10; i++)
		animation->addSpriteFrameWithTexture(textureFlying_eye, Rect(32 * i, 0, 32, 32));

	Animate* animate = Animate::create(animation);

	spriteFlyingEye = Sprite::create("res/Flying_eye_R.png", Rect(0, 0, 32, 32));
	spriteFlyingEye->setScale(1.5f);
	setFirstPosition(spriteFlyingEye);
	this->addChild(spriteFlyingEye);

	Vec2 entryPos = this->getGridPosition(spriteFlyingEye->getPosition());
	std::vector<Vec2> path = this->pathFinder->getShortestPath(entryPos, Vec2(16, 6));

	Vector<FiniteTimeAction*> moves;
	for (int i = 0; i < path.size(); i++)
	{
		MoveTo* moveTo = MoveTo::create(0.5f, this->getRealPosition(path[i]));
		moves.pushBack(moveTo);
	}

	CallFuncN* callfunc = CallFuncN::create(CC_CALLBACK_1(OffenseScene::selfRemover, this));
	moves.pushBack(callfunc);

	auto moveSeq = Sequence::create(moves);
	//Vector<FiniteTimeAction*> actions;
	//actions.pushBack(moveSeq);
	//actions.pushBack(animateReapeat);
	//actions.pushBack(callfunc);

	auto animateReapeat = RepeatForever::create(animate);
	auto act = Spawn::create(moveSeq, Repeat::create(animate, 100), NULL);

	spriteFlyingEye->runAction(act);
	//addUnit(spriteFlying_eye);
}

void OffenseScene::addBaby()
{
	Size winSize = Director::getInstance()->getWinSize();

	auto textureFlying_eye = Sprite::create("res/Baby_R.png")->getTexture();

	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.15f);

	for (int i = 0; i < 6; i++)
		animation->addSpriteFrameWithTexture(textureFlying_eye, Rect(32 * i, 0, 32, 32));

	Animate* animate = Animate::create(animation);

	spriteBaby = Sprite::create("res/Baby_R.png", Rect(0, 0, 32, 32));
	spriteBaby->setScale(1.5f);
	setFirstPosition(spriteBaby);
	this->addChild(spriteBaby);

	Vec2 entryPos = this->getGridPosition(spriteBaby->getPosition());
	std::vector<Vec2> path = this->pathFinder->getShortestPath(entryPos, Vec2(16, 6));

	Vector<FiniteTimeAction*> moves;
	for (int i = 0; i < path.size(); i++)
	{
		MoveTo* moveTo = MoveTo::create(0.5f, this->getRealPosition(path[i]));
		moves.pushBack(moveTo);
	}

	CallFuncN* callfunc = CallFuncN::create(CC_CALLBACK_1(OffenseScene::selfRemover, this));
	moves.pushBack(callfunc);

	auto moveSeq = Sequence::create(moves);
	//Vector<FiniteTimeAction*> actions;
	//actions.pushBack(moveSeq);
	//actions.pushBack(animateReapeat);
	//actions.pushBack(callfunc);

	auto animateReapeat = RepeatForever::create(animate);
	auto act = Spawn::create(moveSeq, Repeat::create(animate, 100), NULL);

	spriteBaby->runAction(act);
	//addUnit(spriteFlying_eye);
}

void OffenseScene::addFinger()
{
	Size winSize = Director::getInstance()->getWinSize();

	auto textureFlying_eye = Sprite::create("res/Finger_R.png")->getTexture();

	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.3f);

	for (int i = 0; i < 4; i++)
		animation->addSpriteFrameWithTexture(textureFlying_eye, Rect(32 * i, 0, 32, 32));

	Animate* animate = Animate::create(animation);

	spriteFinger = Sprite::create("res/Finger_R.png", Rect(0, 0, 32, 32));
	spriteFinger->setScale(1.5f);
	setFirstPosition(spriteFinger);
	this->addChild(spriteFinger);

	Vec2 entryPos = this->getGridPosition(spriteFinger->getPosition());
	std::vector<Vec2> path = this->pathFinder->getShortestPath(entryPos, Vec2(16, 6));

	Vector<FiniteTimeAction*> moves;
	for (int i = 0; i < path.size(); i++)
	{
		MoveTo* moveTo = MoveTo::create(0.5f, this->getRealPosition(path[i]));
		moves.pushBack(moveTo);
	}

	CallFuncN* callfunc = CallFuncN::create(CC_CALLBACK_1(OffenseScene::selfRemover, this));
	moves.pushBack(callfunc);

	auto moveSeq = Sequence::create(moves);
	//Vector<FiniteTimeAction*> actions;
	//actions.pushBack(moveSeq);
	//actions.pushBack(animateReapeat);
	//actions.pushBack(callfunc);

	auto animateReapeat = RepeatForever::create(animate);
	auto act = Spawn::create(moveSeq, Repeat::create(animate, 100), NULL);

	spriteFinger->runAction(act);
	//addUnit(spriteFlying_eye);
}

void OffenseScene::addHeart()
{
	Size winSize = Director::getInstance()->getWinSize();

	auto textureFlying_eye = Sprite::create("res/Heart_R.png")->getTexture();

	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.5f);

	for (int i = 0; i < 2; i++)
		animation->addSpriteFrameWithTexture(textureFlying_eye, Rect(32 * i, 0, 32, 32));

	Animate* animate = Animate::create(animation);

	spriteHeart = Sprite::create("res/Heart_R.png", Rect(0, 0, 32, 32));
	spriteHeart->setScale(1.5f);
	setFirstPosition(spriteHeart);
	this->addChild(spriteHeart);

	Vec2 entryPos = this->getGridPosition(spriteHeart->getPosition());
	std::vector<Vec2> path = this->pathFinder->getShortestPath(entryPos, Vec2(16, 6));

	Vector<FiniteTimeAction*> moves;
	for (int i = 0; i < path.size(); i++)
	{
		MoveTo* moveTo = MoveTo::create(0.5f, this->getRealPosition(path[i]));
		moves.pushBack(moveTo);
	}

	CallFuncN* callfunc = CallFuncN::create(CC_CALLBACK_1(OffenseScene::selfRemover, this));
	moves.pushBack(callfunc);

	auto moveSeq = Sequence::create(moves);
	//Vector<FiniteTimeAction*> actions;
	//actions.pushBack(moveSeq);
	//actions.pushBack(animateReapeat);
	//actions.pushBack(callfunc);

	auto animateReapeat = RepeatForever::create(animate);
	auto act = Spawn::create(moveSeq, Repeat::create(animate, 100), NULL);

	spriteHeart->runAction(act);
	//addUnit(spriteFlying_eye);
}

void OffenseScene::addRib()
{
	Size winSize = Director::getInstance()->getWinSize();

	auto textureFlying_eye = Sprite::create("res/Rib_R.png")->getTexture();

	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.15f);

	for (int i = 0; i < 6; i++)
		animation->addSpriteFrameWithTexture(textureFlying_eye, Rect(32 * i, 0, 32, 32));

	Animate* animate = Animate::create(animation);

	spriteRib = Sprite::create("res/Rib_R.png", Rect(0, 0, 32, 32));
	spriteRib->setScale(1.5f);
	setFirstPosition(spriteRib);
	this->addChild(spriteRib);

	Vec2 entryPos = this->getGridPosition(spriteRib->getPosition());
	std::vector<Vec2> path = this->pathFinder->getShortestPath(entryPos, Vec2(16, 6));

	Vector<FiniteTimeAction*> moves;
	for (int i = 0; i < path.size(); i++)
	{
		MoveTo* moveTo = MoveTo::create(0.5f, this->getRealPosition(path[i]));
		moves.pushBack(moveTo);
	}

	CallFuncN* callfunc = CallFuncN::create(CC_CALLBACK_1(OffenseScene::selfRemover, this));
	moves.pushBack(callfunc);

	auto moveSeq = Sequence::create(moves);
	//Vector<FiniteTimeAction*> actions;
	//actions.pushBack(moveSeq);
	//actions.pushBack(animateReapeat);
	//actions.pushBack(callfunc);

	auto animateReapeat = RepeatForever::create(animate);
	auto act = Spawn::create(moveSeq, Repeat::create(animate, 100), NULL);

	spriteRib->runAction(act);
	//addUnit(spriteFlying_eye);
}
