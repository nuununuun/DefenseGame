//
//  Projectile.cpp
//  DefenseGame
//
//  Created by A on 2018. 12. 1..
//

#include "Projectile.hpp"

USING_NS_CC;

Projectile *Projectile::create(float speed) {
    auto ret = new (std::nothrow) Projectile();
    if (ret && ret->init(speed)) {
        ret->autorelease();
    } else CC_SAFE_DELETE(ret);
    
    return ret;
}

bool Projectile::init(float speed) {
    if (!Sprite::initWithFile("res/arrow.png")) return false;
    
    this->speed = speed;
    
    scheduleUpdate();
    
    return true;
}

void Projectile::update(float dt) {
    this->setPosition(this->getPositionX() - speed, this->getPositionY());
}
