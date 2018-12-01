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
    
    CREATE_FUNC(DefenseScene);
    
public:
    cocos2d::EventListenerTouchAllAtOnce
    
};

#endif /* DefenseScene_h */
