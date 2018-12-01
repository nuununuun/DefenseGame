//
//  DefenseScene.h
//  DefenseGame
//
//  Created by A on 2018. 12. 1..
//

#ifndef DefenseScene_h
#define DefenseScene_h

#include "MainScene.h"

#include "Tower.hpp"
#include "network/SocketIO.h"

#include "OffenseUnit.h"

using namespace cocos2d::network;

class DefenseScene : public MainScene {
public:
    bool init();
    
    void onMouseDown(cocos2d::EventMouse *e) override;
    void onMouseUp(cocos2d::EventMouse *e) override;
    void onMouseMove(cocos2d::EventMouse *e) override;
    
    void update(float dt);
    
    void putTower(int dir);
    void clearPreview();
    
    void drawTowerRange(const cocos2d::Vec2 &gp);
    bool isAbleTower(const cocos2d::Vec2 &gp);

    void addFlyingEye();
    void addBaby();
    void addFinger();
    void addHeart();
    void addRib();
    
    void setFirstPosition(cocos2d::Sprite* sprite);    
    void selfRemover(cocos2d::Node* sender);
    
    CREATE_FUNC(DefenseScene);
    
public:
    void selectGrid(const cocos2d::Vec2 &pos);
    
    cocos2d::DrawNode *directionRenderer;
    cocos2d::Vec2 mouseDownPosition;
    
    cocos2d::Layer *menuLayer;
    std::vector<cocos2d::Sprite *> towerSamples;
    std::vector<Tower *> towers;
    cocos2d::Node *selectedSample;
    cocos2d::Sprite *towerPreview;
    
    int towerState = 0;
    
    bool isMouseDown = false;
    
public:
    std::vector<OffenseUnit*> offenseUnits;
    
};

#endif /* DefenseScene_h */
