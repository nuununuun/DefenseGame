//
//  Tower.cpp
//  DefenseGame
//
//  Created by A on 2018. 12. 1..
//

#include "Tower.hpp"

USING_NS_CC;

Tower *Tower::create(int dir) {
    auto ret = new (std::nothrow) Tower();
    if (ret && ret->init(dir)) {
        ret->autorelease();
    } else CC_SAFE_DELETE(ret);
    
    return ret;
}

bool Tower::init(int dire) {
    if (!Sprite::initWithFile("res/tower1.png")) return false;
    
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

void Tower::attack() {
    
}


