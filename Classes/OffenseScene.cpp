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
	schedule(schedule_selector(OffenseScene::IsCollision), 0.01f);
	schedule(schedule_selector(OffenseScene::updateCoolTime));
	return true;
}

void OffenseScene::updateCoolTime(float dt)
{
	fireCool += dt;
	shootFromCharacter();
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

	mPtShoot = e->getLocationInView();
	mIsShoot = true;

	isMouseDown = true;
}

void OffenseScene::onMouseUp(cocos2d::EventMouse *e) {
	MainScene::onMouseUp(e);
	mIsShoot = false;
	isMouseDown = false;
}

void OffenseScene::onMouseMove(cocos2d::EventMouse *e) {
	MainScene::onMouseMove(e);

	if (isMouseDown)
	{
		mPtShoot = e->getLocationInView();
		mIsShoot = true;
	}
}

void OffenseScene::update(float dt) {
}

void OffenseScene::selectGrid(const Vec2 &pos) {
	auto gridPosition = getGridPosition(pos);

	mapData.setTileData(gridPosition.x, gridPosition.y, TileType::BARRICADE);

	updateMap();
}

void OffenseScene::addShootFire(Point pt)
{
	Size winSize = Director::getInstance()->getWinSize();
	Point location = getRealPosition(Vec2(16, 6));

	bullet = Sprite::create("bullet.png");
	bullet->setPosition(location);
	bullet->setAnchorPoint(Vec2(0, 0));
	//	bullet->setScale(0.5f);

	float angle = (float)atanf((pt.x - location.x) / (pt.y - location.y)) * (180.f / M_PI);
	if (location.y > pt.y)
		bullet->setRotation(angle - 180);
	else
		bullet->setRotation(angle);

	this->addChild(bullet);

	auto moveTo = MoveTo::create(0.5f, pt);
	ActionInterval* actionInterval = EaseOut::create(moveTo, 1.8f);
	CallFuncN* callfunc = CallFuncN::create(CC_CALLBACK_1(OffenseScene::weaponRemover, this));

	Sequence* sequence = Sequence::create(actionInterval, callfunc, NULL);
	bullet->runAction(sequence);

	weaponArr.push_back(bullet);
}

void OffenseScene::shootFromCharacter()
{
	if (mIsShoot == true)
	{
		if (fireCool >= 0.1f)
		{
			fireCool = 0;
			addShootFire(mPtShoot);
		}
	}
}

void OffenseScene::weaponRemover(Node* sender)
{
	Sprite* weapon = nullptr;

	for (auto iter = weaponArr.begin(); iter != weaponArr.end(); iter++)
	{
		weapon = *iter;

		if (weapon == sender)
		{
			weaponArr.erase(iter);
			break;
		}

		weapon = nullptr;
	}

	weapon->removeFromParentAndCleanup(true);
}

void OffenseScene::IsCollision(float dt)
{
	Size winSize = Director::getInstance()->getWinSize();
	Sprite* weapon = NULL;
	Sprite* unit = NULL;

	for (auto iter = weaponArr.begin(); iter != weaponArr.end(); iter++)
	{
		Sprite* w = *iter;
		bool bHit = false;

		for (auto iterE = offenseUnits.begin(); iterE != offenseUnits.end(); iterE++)
		{
			OffenseUnit* u = (*iterE);

			if (w->getBoundingBox().intersectsRect(u->body->getBoundingBox()))
			{
				bHit = true;

				u->curEnergy -= 1.0f;
				if (u->curEnergy <= 0)
				{
					u->body->removeFromParentAndCleanup(true);
					u = nullptr;
					offenseUnits.erase(iterE);
				}
				w->removeFromParentAndCleanup(true);
				w = nullptr;
				weaponArr.erase(iter);

				return;
			}
		}
	}
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
	for (auto iterE = offenseUnits.begin(); iterE != offenseUnits.end(); iterE++)
	{
		OffenseUnit* u = (*iterE);

		if (sender == u->body)
		{
			sender->removeFromParentAndCleanup(true);
			u = nullptr;
			offenseUnits.erase(iterE);
		}
		return;
	}
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

	auto spriteFlyingEye = Sprite::create("res/Flying_eye_R.png", Rect(0, 0, 32, 32));
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

	OffenseUnit *unit = new OffenseUnit();
	unit->body = spriteFlyingEye;
	unit->body->setTag(TAG_TYPE_OFFENSE);
	unit->isEnermy = true;
	unit->eUnitType = RUSH;
	unit->setEnergy(2);

	offenseUnits.push_back(unit);
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

	auto spriteBaby = Sprite::create("res/Baby_R.png", Rect(0, 0, 32, 32));
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
	
	OffenseUnit *unit = new OffenseUnit();
	unit->body = spriteBaby;
	unit->body->setTag(TAG_TYPE_OFFENSE);
	unit->isEnermy = true;
	unit->eUnitType = RUSH;
	unit->setEnergy(10);

	offenseUnits.push_back(unit);
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

	auto spriteFinger = Sprite::create("res/Finger_R.png", Rect(0, 0, 32, 32));
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
	
	OffenseUnit *unit = new OffenseUnit();
	unit->body = spriteFinger;
	unit->body->setTag(TAG_TYPE_OFFENSE);
	unit->isEnermy = true;
	unit->eUnitType = RUSH;
	unit->setEnergy(2);

	offenseUnits.push_back(unit);
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

	auto spriteHeart = Sprite::create("res/Heart_R.png", Rect(0, 0, 32, 32));
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
	
	OffenseUnit *unit = new OffenseUnit();
	unit->body = spriteHeart;
	unit->body->setTag(TAG_TYPE_OFFENSE);
	unit->isEnermy = true;
	unit->eUnitType = RUSH;
	unit->setEnergy(2);

	offenseUnits.push_back(unit);
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

	auto spriteRib = Sprite::create("res/Rib_R.png", Rect(0, 0, 32, 32));
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
	
	OffenseUnit *unit = new OffenseUnit();
	unit->body = spriteRib;
	unit->body->setTag(TAG_TYPE_OFFENSE);
	unit->isEnermy = true;
	unit->eUnitType = RUSH;
	unit->setEnergy(2);

	offenseUnits.push_back(unit);
}
