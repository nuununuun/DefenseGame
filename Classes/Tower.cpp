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
    
    return true;
}
