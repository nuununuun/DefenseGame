//
//  MainScene.h
//  DefenseGame
//
//  Created by A on 2018. 11. 30..
//

#ifndef MainScene_h
#define MainScene_h

#include "cocos2d.h"
#include "MapData.h"
#include "OffenseInterface.h"

class MainScene : public cocos2d::Scene {
public:
    virtual bool init();
    
    void initializeMap();
    
	void onEnter();
	void onExit();

    CREATE_FUNC(MainScene);
    
    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    
// non cocos object
private:
    int width, height;
    float tileSize;
    
    MapData mapData;

// cocos object
private:
    cocos2d::Layer *mapLayer;
    std::vector<cocos2d::Sprite *> mapTiles;
    cocos2d::DrawNode *debugPathDraw;
  
	OffenseInterface* offenseInterface;
};

#endif /* MainScene_h */
