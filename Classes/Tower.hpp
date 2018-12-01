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
    enum TowerType { ARROW, FLAME, LASER, SLOW, DEALT, BOMB, PRISON, BARRICADE };
    enum { PATH, OBSTACLE };
    
    static Tower *create(int dir, TowerType type);
    
    bool init(int dir, TowerType type);
    
    void setVisibleRange();
    void setInvisibleRange();
    
    void setDirection(int direction);
    
    void act();
    
    static cocos2d::Vec2 idxToDir(int idx) {
        return idx == 0 ? cocos2d::Vec2(-1, 0) : idx == 1 ? cocos2d::Vec2(1, 0) : idx == 2 ? cocos2d::Vec2(0, -1) : cocos2d::Vec2(0, 1);
    }
    
public:
    TowerType type;
    int range = 2;
    float attackPower;
    int cost;
    int baseTile;
    cocos2d::DrawNode *rangeRenderer;
    
    float attackDelay = 1.0f, attackTick = 0;
    
    int direction;
    
};

#endif /* Tower_hpp */
