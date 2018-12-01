//
//  DefenseScene.h
//  DefenseGame
//
//  Created by A on 2018. 12. 1..
//

#ifndef DefenseScene_h
#define DefenseScene_h

#include "MainScene.h"

class DefenseScene : public MainScene {
public:
    bool init();
    
    void onMouseDown(cocos2d::EventMouse *e) override;
    void onMouseUp(cocos2d::EventMouse *e) override;
    void onMouseMove(cocos2d::EventMouse *e) override;
    
    CREATE_FUNC(DefenseScene);
    
public:
    
    
};

#endif /* DefenseScene_h */
