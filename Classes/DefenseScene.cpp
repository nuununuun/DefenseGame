//
//  DefenseScene.cpp
//  DefenseGame
//
//  Created by A on 2018. 12. 1..
//

#include "DefenseScene.h"

#include "Tower.hpp"
#include "Unit.hpp"

#include "Projectile.hpp"

USING_NS_CC;
using namespace std;

bool DefenseScene::init() {
    if (!MainScene::init()) return false;
    
    directionRenderer = DrawNode::create(3);
    addChild(directionRenderer);
    
    menuLayer = Layer::create();
    addChild(menuLayer);
    
    towerPreview = Sprite::create("res/tower1.png");
    towerPreview->setVisible(false);
    addChild(towerPreview);
    
    /// tower1
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            auto sample = Sprite::create("res/tower1.png");
            sample->setPosition(Vec2(967 + j * 98, 118 + i * 98));
            sample->setGlobalZOrder(1001);
            menuLayer->addChild(sample);
            towerSamples.push_back(sample);
        }
    }
    
    scheduleUpdate();
    
    return true;
}

void DefenseScene::onConnect(cocos2d::network::SIOClient *c) {
    client->emit("defense", "");
    client->on("summon", [=](SIOClient *c, const std::string &data) {
        if (data == "0") addFlyingEye();
        if (data == "1") addBaby();
        if (data == "2") addFinger();
        if (data == "3") addHeart();
        if (data == "4") addRib();
    });
}

void DefenseScene::onMouseDown(cocos2d::EventMouse *e) {
    MainScene::onMouseDown(e);
    
    for (auto &towerSample : towerSamples) {
        if (towerSample->getBoundingBox().containsPoint(e->getLocationInView())) {
            selectedSample = towerSample;
            towerState = 1;
            break;
        }
    }
    
    if (selectedSample != nullptr) {
        towerPreview->setPosition(e->getLocationInView());
        towerPreview->setVisible(true);
        directionRenderer->clear();
    }
}

void DefenseScene::onMouseMove(cocos2d::EventMouse *e) {
    MainScene::onMouseMove(e);
    
    auto pos = e->getLocationInView();
    
        for (auto tower : towers) {
            if (tower->getBoundingBox().containsPoint(pos)) {
                tower->setVisibleRange();
            } else {
                tower->setInvisibleRange();
            }
        }
    
    if (towerState == 1) {
        towerPreview->setPosition(pos);
        
        auto gp = getGridPosition(e->getLocationInView());
        CCLOG((to_string(gp.x) + ", " + to_string(gp.y)).c_str());
        if (mapData.isOutOfIndex(gp)) return;
        
        auto data = mapData.getTileData(gp.x, gp.y);
        if (data == TileType::SETABLE && isAbleTower(gp)) {
            towerPreview->setColor(Color3B::WHITE);
            drawTowerRange(gp);
        } else {
            towerPreview->setColor(Color3B::RED);
            directionRenderer->clear();
        }
    }
}

void DefenseScene::onMouseUp(cocos2d::EventMouse *e) {
    MainScene::onMouseUp(e);
    auto pos = e->getLocationInView();
    auto gp = getGridPosition(pos);
    
    if (towerState == 1) {
        if (mapData.isOutOfIndex(gp) || !isAbleTower(gp) || mapData.getTileData(gp.x, gp.y) != TileType::SETABLE) {
            towerState = 0;
            clearPreview();
            return;
        }
        
        Vec2 rp = getRealPosition(gp);
        towerPreview->setPosition(rp);

        towerState = 2;
    } else if (towerState == 2) {
        for (int i = 0; i < 4; i++) {
            Vec2 dir = Tower::idxToDir(i);
            
            if (gp == dir + getGridPosition(towerPreview->getPosition())) {
                putTower(i);
                clearPreview();
                directionRenderer->clear();
                break;
            }
        }
        
        towerState = 0;
    }
    
    selectedSample = nullptr;
}

void DefenseScene::putTower(int dir) {
    towerState = 0;
    
    auto gp = getGridPosition(towerPreview->getPosition());
    if (mapData.getTileData(gp.x, gp.y) == TileType::SETABLE) {
        auto tower = Tower::create(dir, Tower::ARROW);
        tower->setPosition(getRealPosition(gp));
        addChild(tower);
        int type = (int)TileType::SETABLE + 1;
        mapData.setTileData(gp.x, gp.y, (TileType)type);
        towers.push_back(tower);
    }
}

void DefenseScene::selectGrid(const Vec2 &pos) {
    auto gridPosition = getGridPosition(pos);
    
    mapData.setTileData(gridPosition.x, gridPosition.y, TileType::BARRICADE);
    
    updateMap();
}

void DefenseScene::drawTowerRange(const Vec2 &gp) {
    directionRenderer->clear();
    for (int i = 0; i < 4; i++) {
        Vec2 dir = Tower::idxToDir(i);
        if (mapData.isOutOfIndex(gp + dir)) continue;
        auto data = mapData.getTileData(gp.x + dir.x, gp.y + dir.y);
        
        if (mapData.isEquals(data, TileType::SETABLE)) continue;
        
        Vec2 rp = getRealPosition(gp);
        directionRenderer->drawSolidRect(rp + dir * 48 - Vec2(20, 20), rp + dir * 48 + Vec2(20, 20), Color4F::RED);
    }
}

bool DefenseScene::isAbleTower(const Vec2 &gp) {
    int cnt = 0;
    for (int i = 0; i < 4; i++) {
        Vec2 dir = Tower::idxToDir(i);
        if (mapData.isOutOfIndex(gp + dir)) continue;
        auto data = mapData.getTileData(gp.x + dir.x, gp.y + dir.y);
        
        if (mapData.isEquals(data, TileType::SETABLE)) continue;
        
        cnt += 1;
    }
    
    return cnt;
}

void DefenseScene::clearPreview() {
    towerPreview->setVisible(false);
}

void DefenseScene::update(float dt) {
    for (auto &tower : towers) {
        // check
        if (tower->attackTick >= tower->attackDelay) {
            tower->act();
            tower->attackTick = 0;
        } else tower->attackTick += 1.0f * dt;
    }
    updateTime(dt);
}

void DefenseScene::selfRemover(Node* sender)
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

void DefenseScene::setFirstPosition(Sprite* sprite)
{
    Size winSize = Director::getInstance()->getWinSize();
    
    //float xPos = rand() % (int)winSize.width + 500;
    //float yPos = rand() % (int)winSize.height;
    
    //sprite->setPosition(xPos, yPos);
    //sprite->setAnchorPoint(Vec2(0.5, 0.5));
    
    Vec2 pos(this->getRealPosition(Vec2(0, 6)));
    sprite->setPosition(pos);
}

void DefenseScene::addFlyingEye()
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
    
    CallFuncN* callfunc = CallFuncN::create(CC_CALLBACK_1( DefenseScene::selfRemover, this));
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
    unit->body->setTag(0);
    unit->isEnermy = true;
    unit->eUnitType = RUSH;
    unit->setEnergy(2);
    
    offenseUnits.push_back(unit);
}

void  DefenseScene::addBaby()
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
    
    CallFuncN* callfunc = CallFuncN::create(CC_CALLBACK_1( DefenseScene::selfRemover, this));
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
    unit->body->setTag(0);
    unit->isEnermy = true;
    unit->eUnitType = RUSH;
    unit->setEnergy(10);
    
    offenseUnits.push_back(unit);
}

void DefenseScene::addFinger()
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
    
    CallFuncN* callfunc = CallFuncN::create(CC_CALLBACK_1( DefenseScene::selfRemover, this));
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
    unit->body->setTag(0);
    unit->isEnermy = true;
    unit->eUnitType = RUSH;
    unit->setEnergy(2);
    
    offenseUnits.push_back(unit);
}

void DefenseScene::addHeart()
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
    
    CallFuncN* callfunc = CallFuncN::create(CC_CALLBACK_1( DefenseScene::selfRemover, this));
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
    unit->body->setTag(0);
    unit->isEnermy = true;
    unit->eUnitType = RUSH;
    unit->setEnergy(2);
    
    offenseUnits.push_back(unit);
}

void DefenseScene::addRib()
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
    
    CallFuncN* callfunc = CallFuncN::create(CC_CALLBACK_1( DefenseScene::selfRemover, this));
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
    unit->body->setTag(0);
    unit->isEnermy = true;
    unit->eUnitType = RUSH;
    unit->setEnergy(2);
    
    offenseUnits.push_back(unit);
}

