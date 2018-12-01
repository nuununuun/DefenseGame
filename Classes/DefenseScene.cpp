//
//  DefenseScene.cpp
//  DefenseGame
//
//  Created by A on 2018. 12. 1..
//

#include "DefenseScene.h"

#include "Tower.hpp"
#include "Unit.hpp"

USING_NS_CC;
using namespace std;

bool DefenseScene::init() {
    if (!MainScene::init()) return false;
    
    return true;
}

void DefenseScene::onMouseDown(cocos2d::EventMouse *e) {
    MainScene::onMouseDown(e);
    
    auto pos = e->getLocationInView();
    auto unit = Unit::create(this);
    auto gp = getGridPosition(pos);
    unit->setPosition(getRealPosition(gp));
    addChild(unit);
    
}

void DefenseScene::onMouseUp(cocos2d::EventMouse *e) {
    MainScene::onMouseUp(e);

}

void DefenseScene::onMouseMove(cocos2d::EventMouse *e) {
    MainScene::onMouseMove(e);
    
}
