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

#include "PathFinding.h"

#include "network/SocketIO.h"

#include "OffenseUnit.h"

#include "Tower.hpp"

using namespace cocos2d::network;

class MainScene : public cocos2d::Scene, public SocketIO::SIODelegate {
public:
    virtual bool init();
    
    void initializeMap();

    CREATE_FUNC(MainScene);
    
    virtual void onConnect(SIOClient* client) {}
    virtual void onMessage(SIOClient* client, const std::string& data) {}
    virtual void onClose(SIOClient* client) {}
    virtual void onError(SIOClient* client, const std::string& data) {}
    
    virtual void onMouseDown(cocos2d::EventMouse *e);
    virtual void onMouseUp(cocos2d::EventMouse *e);
    virtual void onMouseMove(cocos2d::EventMouse *e);
    
    cocos2d::Vec2 getGridPosition(const cocos2d::Vec2 &rp);
    cocos2d::Vec2 getRealPosition(const cocos2d::Vec2 &gp);
    
    void updateMap();
    bool updateTime(float dt);
    
//server:0 or client:1
private:
    int socket_status = 0;
    
// non cocos object
protected:
    int width, height;
    float tileSize;
    
    bool check = false;
    
    //게임 시간 기록
    float timeNow = 60*5 *1000;
    float secCounter=0;
public:
    MapData mapData;

// cocos object
protected:
    cocos2d::Label *timeLabel;
    cocos2d::Layer *mapLayer;
    std::vector<cocos2d::Sprite *> mapTiles;
    cocos2d::DrawNode *debugPathDraw;
  
	//OffenseInterface* offenseInterface;
    
    cocos2d::EventListenerMouse *mouseListener;
    
public:
    pathfinding::PathFinding *pathFinder;
    
    SIOClient *client;
    
    int coreHealth;
    cocos2d::Sprite *hpBar_fill;
    cocos2d::Sprite *hpBar_empty;
    std::vector<OffenseUnit*> offenseUnits;
    
    
    std::vector<Tower *> towers;
    
};

#endif /* MainScene_h */
