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

class DefenseScene;
class OffenseScene;

class TitleScene : public cocos2d::Scene {
public:
    bool init();
    
    CREATE_FUNC(TitleScene);
public:
	float ani_add = 0.06;
	cocos2d::Sprite * bg;
	cocos2d::Sprite * left, * right;
	cocos2d::Sprite * title, * subTitle;

	DefenseScene *dScene;
	OffenseScene *oScene;
	
};

#endif /* TitleScene_hpp */
