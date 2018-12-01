//
//  DefenseScene.cpp
//  DefenseGame
//
//  Created by A on 2018. 12. 1..
//

#include "DefenseScene.h"

#include "Tower.hpp"
#include "Unit.hpp"

USING_NS_CC;
using namespace std;

bool DefenseScene::init() {
    if (!MainScene::init()) return false;
    
    lineRenderer = DrawNode::create(3);
    addChild(lineRenderer);
    
    menuLayer = Layer::create();
    addChild(menuLayer);
    
    for (int i = 0; i < 8; i++) {
        auto sample = Sprite::create("res/tower1.png");
        sample->setPosition(Vec2(96, i * 64 + 48));
        menuLayer->addChild(sample);
        towerSamples.push_back(sample);
    }
    
    scheduleUpdate();
    
    return true;
}

void DefenseScene::onMouseDown(cocos2d::EventMouse *e) {
    MainScene::onMouseDown(e);
    
    for (auto &towerSample : towerSamples) {
        if (towerSample->getBoundingBox().containsPoint(e->getLocationInView())) {
            selectedSample = towerSample;
            break;
        }
    }
    
    if (selectedSample != nullptr) {
        selectedSample->runAction(Sequence::create(ScaleTo::create(0.1, 1.2), ScaleTo::create(0.1, 1), nullptr));
    }
}

void DefenseScene::onMouseUp(cocos2d::EventMouse *e) {
    MainScene::onMouseUp(e);
    
    selectedSample = nullptr;
}

void DefenseScene::onMouseMove(cocos2d::EventMouse *e) {
    MainScene::onMouseMove(e);
}

void DefenseScene::update(float dt) {
}

void DefenseScene::selectGrid(const Vec2 &pos) {
    auto gridPosition = getGridPosition(pos);
    
    mapData.setTileData(gridPosition.x, gridPosition.y, TileType::BARRICADE);
    
    updateMap();
}
