//
//  Projectile.hpp
//  DefenseGame
//
//  Created by A on 2018. 12. 1..
//

#ifndef Projectile_hpp
#define Projectile_hpp

#include "cocos2d.h"

class Projectile : public cocos2d::Sprite {
public:
    static Projectile *create(float speed);
    
    bool init(float speed);
    
    void update(float dt);
    
public:
    float speed;
    
};

#endif /* Projectile_hpp */
