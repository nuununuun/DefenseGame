//
//  Unit.hpp
//  DefenseGame
//
//  Created by A on 2018. 12. 1..
//

#ifndef Unit_hpp
#define Unit_hpp

#include "cocos2d.h"

class MainScene;

class Unit : public cocos2d::Sprite {
public:
    static Unit *create(MainScene *parent);
    
    bool init();
    
    void onEnter() override;
    
    void update(float dt);
    
private:
    MainScene *parentScene;
    
    std::vector<cocos2d::Vec2> path;
    
};

#endif /* Unit_hpp */
