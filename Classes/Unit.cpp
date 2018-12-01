//
//  Unit.cpp
//  DefenseGame
//
//  Created by A on 2018. 12. 1..
//

#include "Unit.hpp"

#include "MainScene.h"

USING_NS_CC;
using namespace std;

Unit *Unit::create(MainScene *parent) {
    auto ret = new (std::nothrow) Unit();
    if (ret && ret->init()) {
        ret->parentScene = parent;
        ret->autorelease();
    } else CC_SAFE_DELETE(ret);
    
    return ret;
}

bool Unit::init() {
    if (!Sprite::initWithFile("res/unit1.png")) return false;
    
    return true;
}

void Unit::onEnter() {
    auto gp = parentScene->getGridPosition(getPosition());
}
