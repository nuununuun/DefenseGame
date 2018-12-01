//
//  Tower.hpp
//  DefenseGame
//
//  Created by A on 2018. 12. 1..
//

#ifndef Tower_hpp
#define Tower_hpp

#include "cocos2d.h"

class Tower : public cocos2d::Sprite {
public:
    static Tower *create();
    
    bool init();
    
public:
    float range;
    
};

#endif /* Tower_hpp */
