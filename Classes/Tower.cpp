//
//  Tower.cpp
//  DefenseGame
//
//  Created by A on 2018. 12. 1..
//

#include "Tower.hpp"

USING_NS_CC;

Tower *Tower::create() {
    auto ret = new (std::nothrow) Tower();
    if (ret && ret->init()) {
        ret->autorelease();
    } else CC_SAFE_DELETE(ret);
    
    return ret;
}

bool Tower::init() {
    if (!Sprite::initWithFile("res/tower1.png")) return false;
    
    Vec2 dir = direction == 0 ? Vec2(-1, 0) : direction == 1 ? Vec2(1, 0) : direction == 2 ? Vec2(0, -1) : Vec2(0, 1);
    
    rangeRenderer = DrawNode::create();
    addChild(rangeRenderer);
    setDirection(direction);
    
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
    
    Vec2 dir = direction == 0 ? Vec2(-1, 0) : direction == 1 ? Vec2(1, 0) : direction == 2 ? Vec2(0, -1) : Vec2(0, 1);
    
    rangeRenderer->clear();
    for (int i = 1; i <= range; i++) {
        rangeRenderer->drawCircle(Vec2(24, 24) + dir * 48 * i, 16, 0, 32, false, Color4F::RED);
        rangeRenderer->drawCircle(Vec2(24, 24) + dir * 48 * i, 12, 0, 32, false, Color4F::RED);
    }
}
