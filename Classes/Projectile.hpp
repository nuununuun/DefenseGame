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
    bool init();
    
    CREATE_FUNC(Projectile);
};

#endif /* Projectile_hpp */
