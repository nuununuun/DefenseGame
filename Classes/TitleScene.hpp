//
//  TitleScene.hpp
//  DefenseGame
//
//  Created by A on 2018. 12. 1..
//

#ifndef TitleScene_hpp
#define TitleScene_hpp

#include "cocos2d.h"
#include "network/SocketIO.h"

class TitleScene : public cocos2d::Scene {
public:
    bool init();
    
    CREATE_FUNC(TitleScene);
};

#endif /* TitleScene_hpp */
