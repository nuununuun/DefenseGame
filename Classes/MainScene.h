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

#include "PathFinding.h"

class MainScene : public cocos2d::Scene {
public:
    virtual bool init();
    
    void initializeMap();

    CREATE_FUNC(MainScene);
    
    virtual void onMouseDown(cocos2d::EventMouse *e);
    virtual void onMouseUp(cocos2d::EventMouse *e);
    virtual void onMouseMove(cocos2d::EventMouse *e);
    
    cocos2d::Vec2 getGridPosition(const cocos2d::Vec2 &rp);
    cocos2d::Vec2 getRealPosition(const cocos2d::Vec2 &gp);
    
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
    
    cocos2d::EventListenerMouse *mouseListener;
    
public:
    pathfinding::PathFinding *pathFinder;
    
};

#endif /* MainScene_h */
