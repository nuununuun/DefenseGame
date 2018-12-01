//
//  Tower.cpp
//  DefenseGame
//
//  Created by A on 2018. 12. 1..
//

#include "Tower.hpp"

#include "Projectile.hpp"

USING_NS_CC;

Tower *Tower::create(int dir, TowerType type) {
    auto ret = new (std::nothrow) Tower();
    if (ret && ret->init(dir, type)) {
        ret->autorelease();
    } else CC_SAFE_DELETE(ret);
    
    return ret;
}

bool Tower::init(int dire, TowerType type) {
    if (!Sprite::initWithFile("res/tower1.png")) return false;
    
    switch(type){
        case ARROW:
            range = 2;
            attackPower = 2;
            cost = 20;
            baseTile = OBSTACLE;
            attackDelay = 20;
            break;
        case FLAME:
            range = 2;
            attackPower = 2;
            cost = 20;
            baseTile = OBSTACLE;
            attackDelay = 20;
            break;
        case LASER:
            range = -1;
            attackPower = 0.5f;
            cost = 70;
            baseTile = OBSTACLE;
            attackDelay = 0;
            break;
        case SLOW:
            range = 0;
            attackPower = 0;
            cost = 30;
            baseTile = PATH;
            attackDelay = 0;
            break;
        case DEALT:
            range = 0;
            attackPower = 0.1f;
            cost = 50;
            baseTile = PATH;
            attackDelay = 0;
            break;
        case BOMB:
            range = 1;
            attackPower = 4;
            cost = 150;
            baseTile = PATH;
            attackDelay = 0;
            break;
        case PRISON:
            range = 0;
            attackPower = 0;
            cost = 80;
            baseTile = PATH;
            attackDelay = 3*60;
            break;
        case BARRICADE:
            range = 0;
            attackPower = 0;
            cost = 20;
            baseTile = PATH;
            attackDelay = 0;
            break;
    }
    
    rangeRenderer = DrawNode::create();
    rangeRenderer->setVisible(false);
    addChild(rangeRenderer);
    
    setDirection(dire);
    
    return true;
}

void Tower::setVisibleRange() {
    rangeRenderer->setVisible(true);
}

void Tower::setInvisibleRange() {
    rangeRenderer->setVisible(false);
}

void Tower::setDirection(int direction) {
    this->direction = direction;
    
    auto dir = Tower::idxToDir(direction);
    
    rangeRenderer->clear();
    for (int i = 1; i <= range; i++) {
        rangeRenderer->drawCircle(Vec2(24, 24) + dir * 48 * i, 16, 0, 32, false, Color4F::RED);
        rangeRenderer->drawCircle(Vec2(24, 24) + dir * 48 * i, 12, 0, 32, false, Color4F::RED);
    }
}

void Tower::act()
{
    if (type == ARROW) {
        Tower::idxToDir(direction);
        auto proj = Projectile::create(5);
        proj->setPosition(getPosition());
        proj->setGlobalZOrder(1000);
        addChild(proj);
    } else if (type == FLAME) {
        range = 2;
        attackPower = 2;
        cost = 20;
        baseTile = OBSTACLE;
        attackDelay = 20;
    } else if (type == LASER) {
        range = -1;
        attackPower = 0.5f;
        cost = 70;
        baseTile = OBSTACLE;
        attackDelay = 0;
    } else if (type == SLOW) {
        range = 0;
        attackPower = 0;
        cost = 30;
        baseTile = PATH;
        attackDelay = 0;
    } else if (type == DEALT) {
        range = 0;
        attackPower = 0.1f;
        cost = 50;
        baseTile = PATH;
        attackDelay = 0;
    } else if (type == BOMB) {
        range = 1;
        attackPower = 4;
        cost = 150;
        baseTile = PATH;
        attackDelay = 0;
    } else if (type == PRISON) {
        range = 0;
        attackPower = 0;
        cost = 80;
        baseTile = PATH;
        attackDelay = 3*60;
    } else if (type == BARRICADE) {
        range = 0;
        attackPower = 0;
        cost = 20;
        baseTile = PATH;
        attackDelay = 0;
    }
}


