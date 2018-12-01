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
    
    void setVisibleRange();
    void setInvisibleRange();
    
    void setDirection(int direction);
    
public:
    int range = 2;
    cocos2d::DrawNode *rangeRenderer;
    
    float attackDelay;
    float damage;
    
    int direction;
    
};

#endif /* Tower_hpp */
