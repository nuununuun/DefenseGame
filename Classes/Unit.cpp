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
    auto pos = parentScene->getGridPosition(getPosition());
    path = parentScene->pathFinder->getShortestPath(pos, parentScene->mapData.getTargetPosition());// Vec2(16, 6));
    
    auto dn = DrawNode::create();
    dn->clear();
    parentScene->addChild(dn);
    
    for (int i = 0; i < path.size() - 1; i++) {
        Vec2 src = parentScene->getRealPosition(path[i]);
        Vec2 dst = parentScene->getRealPosition(path[i + 1]);
        dn->drawLine(src, dst, Color4F::RED);
    }
    
    scheduleUpdate();
}

void Unit::update(float dt) {
    
}
