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
    static Tower *create(int dir);
        bool init(int dir);
    
    void setVisibleRange();
    void setInvisibleRange();
    
    void setDirection(int direction);
    
    static cocos2d::Vec2 idxToDir(int idx) {
        return idx == 0 ? cocos2d::Vec2(-1, 0) : idx == 1 ? cocos2d::Vec2(1, 0) : idx == 2 ? cocos2d::Vec2(0, -1) : cocos2d::Vec2(0, 1);
    }
    
public:
    int range = 2;
    cocos2d::DrawNode *rangeRenderer;
    
    float attackDelay = 1.0f, attackTick = 0;
    float damage;
    
    int direction;
    
};

#endif /* Tower_hpp */
