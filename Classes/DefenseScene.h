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
    
    void update(float dt);
    
    CREATE_FUNC(DefenseScene);
    
public:
    void selectGrid(const cocos2d::Vec2 &pos);
    
    cocos2d::DrawNode *lineRenderer;
    cocos2d::Vec2 mouseDownPosition;
    
    cocos2d::Layer *menuLayer;
    std::vector<cocos2d::Sprite *> towerSamples;
    cocos2d::Node *selectedSample;
    cocos2d::Sprite *towerPreview;
    
    bool isMouseDown = false;
    
    
};

#endif /* DefenseScene_h */
