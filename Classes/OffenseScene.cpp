#include "OffenseScene.h"

USING_NS_CC;
using namespace std;

bool OffenseScene::init() {
	if (!MainScene::init()) 
		return false;
    
	menuLayer = Layer::create();
	addChild(menuLayer);

	coreHealth = 100;
	money = 20;

	for (int i = 0; i < 5; i++)
	{
		cost.push_back(Sprite::create("res/cost.png"));
		cost[i]->setPosition(Vec2(977 + i * 60, 128 + 4 * 98));
		cost[i]->setGlobalZOrder(1001);
		cost[i]->setVisible(false);
		menuLayer->addChild(cost[i]);
	}

	//hpBar_fill = Sprite::create("res/hpBar_fill.png");
	//hpBar_fill->setGlobalZOrder(1001);
	//hpBar_empty = Sprite::create("res/hpBar_empty.png");
	//hpBar_empty->setGlobalZOrder(1001);

	//hpBar_fill->setPosition(Vec2(967 + 0 * 98, 118 + 4 * 98));
	//hpBar_empty->setPosition(Vec2(967 + 0 * 98, 118 + 4 * 98));
	//
	//menuLayer->addChild(hpBar_empty);
	//menuLayer->addChild(hpBar_fill);

	//sample->setPosition(Vec2(mapLayer->getPositionX() + mapData.width * 48 * 0.5f + (48 + 16) * (j + 1), i * 64 + 72));
	//setPosition(Vec2(967 + j * 98, 118 + i * 98));
	interfaceFlyingEye = Sprite::create("res/Flying_eye_R.png", Rect(0, 0, 32, 32));
	interfaceFlyingEye->getTexture()->setAliasTexParameters();
	interfaceFlyingEye->setPosition(Vec2(967 + 0 * 98, 118 + 0 * 98));
	interfaceFlyingEye->setGlobalZOrder(1001);
	interfaceFlyingEye->setScale(1.5f);
	menuLayer->addChild(interfaceFlyingEye);

	interfaceBaby = Sprite::create("res/Baby_R.png", Rect(0, 0, 32, 32));
	interfaceBaby->getTexture()->setAliasTexParameters();
	interfaceBaby->setPosition(Vec2(967 + 1 * 98, 118 + 0 * 98));
	interfaceBaby->setGlobalZOrder(1001);
	interfaceBaby->setScale(1.5f);
	menuLayer->addChild(interfaceBaby);

	interfaceFinger = Sprite::create("res/Finger_R.png", Rect(0, 0, 32, 32));
	interfaceFinger->getTexture()->setAliasTexParameters();
	interfaceFinger->setPosition(Vec2(967 + 0 * 98, 118 + 1 * 98));
	interfaceFinger->setGlobalZOrder(1001);
	interfaceFinger->setScale(1.5f);
	menuLayer->addChild(interfaceFinger);

	interfaceHeart = Sprite::create("res/Heart_R.png", Rect(0, 0, 32, 32));
	interfaceHeart->getTexture()->setAliasTexParameters();
	interfaceHeart->setPosition(Vec2(967 + 1 * 98, 118 + 1 * 98));
	interfaceHeart->setGlobalZOrder(1001);
	interfaceHeart->setScale(1.5f);
	menuLayer->addChild(interfaceHeart);

	interfaceRib = Sprite::create("res/Rib_D.png", Rect(0, 0, 32, 32));
	interfaceRib->getTexture()->setAliasTexParameters();
	interfaceRib->setPosition(Vec2(967 + 0 * 98, 118 + 2 * 98));
	interfaceRib->setGlobalZOrder(1001);
	interfaceRib->setScale(1.5f);
	menuLayer->addChild(interfaceRib);

	interfaceTooth = Sprite::create("res/Tooth_D.png", Rect(0, 0, 32, 32));
	interfaceTooth->getTexture()->setAliasTexParameters();
	interfaceTooth->setPosition(Vec2(967 + 1 * 98, 118 + 2 * 98));
	interfaceTooth->setGlobalZOrder(1001);
	interfaceTooth->setScale(1.5f);
	menuLayer->addChild(interfaceTooth);

	interfaceCaecum = Sprite::create("res/Caecum_R.png", Rect(0, 0, 32, 32));
	interfaceCaecum->getTexture()->setAliasTexParameters();
	interfaceCaecum->setPosition(Vec2(967 + 0 * 98, 118 + 3 * 98));
	interfaceCaecum->setGlobalZOrder(1001);
	interfaceCaecum->setScale(1.5f);
	menuLayer->addChild(interfaceCaecum);

	interfaceFist = Sprite::create("res/Fist_R.png", Rect(0, 0, 32, 32));
	interfaceFist->getTexture()->setAliasTexParameters();
	interfaceFist->setPosition(Vec2(967 + 1 * 98, 118 + 3 * 98));
	interfaceFist->setGlobalZOrder(1001);
	interfaceFist->setScale(1.5f);
	menuLayer->addChild(interfaceFist);

	//interfaceUnits.push_back(interfaceFlyingEye);
	scheduleUpdate();
	schedule(schedule_selector(OffenseScene::IsCollision), 0.01f);
	schedule(schedule_selector(OffenseScene::updateCoolTime));
	return true;
}

void OffenseScene::onConnect(SIOClient* c) {
}

void OffenseScene::updateCoolTime(float dt)
{
	fireCool += dt;

	if (money >= 50.0f) {
		cost[0]->setVisible(true);
		cost[1]->setVisible(true);
		cost[2]->setVisible(true);
		cost[3]->setVisible(true);
		cost[4]->setVisible(true);
	}
	else if (money >= 40.0f) {
		cost[0]->setVisible(true);
		cost[1]->setVisible(true);
		cost[2]->setVisible(true);
		cost[3]->setVisible(true);
		cost[4]->setVisible(false);
	}
	else if (money >= 30.0f) {
		cost[0]->setVisible(true);
		cost[1]->setVisible(true);
		cost[2]->setVisible(true);
		cost[3]->setVisible(false);
		cost[4]->setVisible(false);
	}
	else if (money >= 20.0f) {
		cost[0]->setVisible(true);
		cost[1]->setVisible(true);
		cost[2]->setVisible(false);
		cost[3]->setVisible(false);
		cost[4]->setVisible(false);
	}
	else if (money >= 10.0f) {
		cost[0]->setVisible(true);
		cost[1]->setVisible(false);
		cost[2]->setVisible(false);
		cost[3]->setVisible(false);
		cost[4]->setVisible(false);
	}
	else {
		cost[0]->setVisible(false);
		cost[1]->setVisible(false);
		cost[2]->setVisible(false);
		cost[3]->setVisible(false);
		cost[4]->setVisible(false);
	}

	if(money <= 50.0f)
		money += dt * 10;

	CCLOG("%f", money);
	shootFromCharacter();
}

void OffenseScene::onMouseDown(cocos2d::EventMouse *e) {
	MainScene::onMouseDown(e);
	
    if (interfaceFlyingEye->getBoundingBox().containsPoint(e->getLocationInView())) {
		if (money < COST_FLYING_EYE)
			return;

		addFlyingEye();
        client->emit("summon", "0");

		money -= COST_FLYING_EYE;
    }
    if (interfaceBaby->getBoundingBox().containsPoint(e->getLocationInView())) {
		if (money < COST_BABY)
			return;

		addBaby();
        client->emit("summon", "1");

		money -= COST_BABY;
    }
    if (interfaceFinger->getBoundingBox().containsPoint(e->getLocationInView())) {
		if (money < COST_FINGER)
			return;

		addFinger();
        client->emit("summon", "2");

		money -= COST_FINGER;
    }
    if (interfaceHeart->getBoundingBox().containsPoint(e->getLocationInView())) {
		if (money < COST_HEART)
			return;

		addHeart();
        client->emit("summon", "3");

		money -= COST_HEART;
    }
    if (interfaceFist->getBoundingBox().containsPoint(e->getLocationInView())) {
		if (money < COST_FIST)
			return;

		addFist();
        client->emit("summon", "4");

		money -= COST_FIST;
    }
	if (interfaceRib->getBoundingBox().containsPoint(e->getLocationInView())) {
		addRib();
		client->emit("summon", "5");

		money -= COST_RIB;
	}
	if (interfaceTooth->getBoundingBox().containsPoint(e->getLocationInView())) {
		if (money < COST_TOOTH)
			return;

		addTooth();
		client->emit("summon", "6");

		money -= COST_TOOTH;
	}
	if (interfaceCaecum->getBoundingBox().containsPoint(e->getLocationInView())) {
		if (money < COST_CAECUM)
			return;

		addCaecum();
		client->emit("summon", "7");

		money -= COST_CAECUM;
	}


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
		if (fireCool >= 0.01f)
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
					auto textureFlying_eye = Sprite::create("res/Blood_boom.png")->getTexture();

					Animation* animation = Animation::create();
					animation->setDelayPerUnit(0.05f);

					for (int i = 0; i < 21; i++)
						animation->addSpriteFrameWithTexture(textureFlying_eye, Rect(48 * i, 0, 48, 48));

					Animate* animate = Animate::create(animation);

					auto sprite = Sprite::create("res/Blood_boom.png", Rect(0, 0, 48, 48));
					sprite->getTexture()->setAliasTexParameters();
					sprite->setScale(1.5f);
					//setFirstPosition(spriteFlyingEye);
					sprite->setPosition(u->body->getPosition());
					this->addChild(sprite);
					sprite->runAction(animate);
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
			coreHealth -= u->attackDamage;
			if (coreHealth < 0)
				coreHealth = 0;

			//	hpBar_fill->setScaleX(coreHealth * 0.01f);
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
	spriteFlyingEye->setScale(2.0f);
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
	spriteFlyingEye->getTexture()->setAliasTexParameters();

	OffenseUnit *unit = new OffenseUnit();
	unit->body = spriteFlyingEye;
	unit->body->setTag(0);
	unit->isEnermy = true;
	unit->eUnitType = RUSH;
	unit->setEnergy(2);
	unit->attackDamage = 2;
	unit->cost = 2;

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
	spriteBaby->getTexture()->setAliasTexParameters();

	OffenseUnit *unit = new OffenseUnit();
	unit->body = spriteBaby;
	unit->body->setTag(0);
	unit->isEnermy = true;
	unit->eUnitType = RUSH;
	unit->setEnergy(10);
	unit->attackDamage = 2;
	unit->cost = 2;

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
	spriteFinger->getTexture()->setAliasTexParameters();

	OffenseUnit *unit = new OffenseUnit();
	unit->body = spriteFinger;
	unit->body->setTag(0);
	unit->isEnermy = true;
	unit->eUnitType = RUSH;
	unit->setEnergy(2);
	unit->attackDamage = 2;
	unit->cost = 2;

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
	spriteHeart->getTexture()->setAliasTexParameters();

	OffenseUnit *unit = new OffenseUnit();
	unit->body = spriteHeart;
	unit->body->setTag(0);
	unit->isEnermy = true;
	unit->eUnitType = RUSH;
	unit->setEnergy(2);
	unit->attackDamage = 2;
	unit->cost = 2;

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
	spriteRib->getTexture()->setAliasTexParameters();

	OffenseUnit *unit = new OffenseUnit();
	unit->body = spriteRib;
	unit->body->setTag(0);
	unit->isEnermy = true;
	unit->eUnitType = RUSH;
	unit->setEnergy(2);
	unit->attackDamage = 2;
	unit->cost = 2;

	offenseUnits.push_back(unit);
}

void OffenseScene::addTooth()
{
	Size winSize = Director::getInstance()->getWinSize();

	auto textureFlying_eye = Sprite::create("res/Tooth_D.png")->getTexture();

	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.2f);

	for (int i = 0; i < 8; i++)
		animation->addSpriteFrameWithTexture(textureFlying_eye, Rect(32 * i, 0, 32, 32));

	Animate* animate = Animate::create(animation);

	auto spriteTooth = Sprite::create("res/Tooth_D.png", Rect(0, 0, 32, 32));
	spriteTooth->setScale(1.5f);
	setFirstPosition(spriteTooth);
	this->addChild(spriteTooth);

	Vec2 entryPos = this->getGridPosition(spriteTooth->getPosition());
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

	spriteTooth->runAction(act);
	spriteTooth->getTexture()->setAliasTexParameters();

	OffenseUnit *unit = new OffenseUnit();
	unit->body = spriteTooth;
	unit->body->setTag(0);
	unit->isEnermy = true;
	unit->eUnitType = RUSH;
	unit->setEnergy(2);
	unit->attackDamage = 2;
	unit->cost = 2;

	offenseUnits.push_back(unit);
}

void OffenseScene::addCaecum()
{
	Size winSize = Director::getInstance()->getWinSize();

	auto textureFlying_eye = Sprite::create("res/Caecum_R.png")->getTexture();

	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.1f);

	for (int i = 0; i < 8; i++)
		animation->addSpriteFrameWithTexture(textureFlying_eye, Rect(32 * i, 0, 32, 32));

	Animate* animate = Animate::create(animation);

	auto spriteCaecum = Sprite::create("res/Caecum_R.png", Rect(0, 0, 32, 32));
	spriteCaecum->setScale(1.5f);
	setFirstPosition(spriteCaecum);
	this->addChild(spriteCaecum);

	Vec2 entryPos = this->getGridPosition(spriteCaecum->getPosition());
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

	spriteCaecum->runAction(act);
	spriteCaecum->getTexture()->setAliasTexParameters();

	OffenseUnit *unit = new OffenseUnit();
	unit->body = spriteCaecum;
	unit->body->setTag(0);
	unit->isEnermy = true;
	unit->eUnitType = RUSH;
	unit->setEnergy(2);
	unit->attackDamage = 2;
	unit->cost = 2;

	offenseUnits.push_back(unit);
}

void OffenseScene::addFist()
{
	Size winSize = Director::getInstance()->getWinSize();

	auto textureFlying_eye = Sprite::create("res/Fist_R.png")->getTexture();

	Animation* animation = Animation::create();
	animation->setDelayPerUnit(0.3f);

	for (int i = 0; i < 4; i++)
		animation->addSpriteFrameWithTexture(textureFlying_eye, Rect(32 * i, 0, 32, 32));

	Animate* animate = Animate::create(animation);

	auto spriteFist = Sprite::create("res/Fist_R.png", Rect(0, 0, 32, 32));
	spriteFist->setScale(1.5f);
	setFirstPosition(spriteFist);
	this->addChild(spriteFist);

	Vec2 entryPos = this->getGridPosition(spriteFist->getPosition());
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

	spriteFist->runAction(act);
	spriteFist->getTexture()->setAliasTexParameters();

	OffenseUnit *unit = new OffenseUnit();
	unit->body = spriteFist;
	unit->body->setTag(0);
	unit->isEnermy = true;
	unit->eUnitType = RUSH;
	unit->setEnergy(2);
	unit->attackDamage = 2;
	unit->cost = 2;

	offenseUnits.push_back(unit);
}

void OffenseScene::putTower(int dir) {
//    towerState = 0;
//    
//    auto gp = getGridPosition(towerPreview->getPosition());
//    if (mapData.getTileData(gp.x, gp.y) == TileType::SETABLE) {
//        auto tower = Tower::create(dir, Tower::ARROW);
//        tower->setPosition(getRealPosition(gp));
//        addChild(tower);
//        int type = (int)TileType::SETABLE + 1;
//        mapData.setTileData(gp.x, gp.y, (TileType)type);
//        towers.push_back(tower);
//    }
}
