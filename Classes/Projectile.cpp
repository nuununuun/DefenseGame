//
//  Projectile.cpp
//  DefenseGame
//
//  Created by A on 2018. 12. 1..
//

#include "Projectile.hpp"

USING_NS_CC;

bool Projectile::init() {
    if (!Sprite::initWithFile("res/arrow.png")) return false;
    
    return true;
}
