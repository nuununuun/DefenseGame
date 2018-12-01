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
    
    towerPreview = Sprite::create("res/tower1.png");
    towerPreview->setVisible(false);
    addChild(towerPreview);
    
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
        towerPreview->setPosition(e->getLocationInView());
        towerPreview->setVisible(true);
    }
}

void DefenseScene::onMouseUp(cocos2d::EventMouse *e) {
    MainScene::onMouseUp(e);
    
    if (selectedSample != nullptr) {
        towerPreview->setVisible(false);
        
        auto gp = getGridPosition(e->getLocationInView());
        if (mapData.isOutOfIndex(gp)) return;
        
        auto tileData = mapData.getTileData(gp.x, gp.y);
        if ((tileData > TileType::EMPTY && tileData < TileType::EMPTY + 10)) {
            auto tower = Tower::create();
            tower->setPosition(getRealPosition(gp));
            addChild(tower);
        }
    }
    
    selectedSample = nullptr;
}

void DefenseScene::onMouseMove(cocos2d::EventMouse *e) {
    MainScene::onMouseMove(e);
    
    if (selectedSample != nullptr) {
        towerPreview->setPosition(e->getLocationInView());
        
        auto gp = getGridPosition(e->getLocationInView());
        if (mapData.isOutOfIndex(gp)) return;
        
        auto tileData = mapData.getTileData(gp.x, gp.y);
        if (!(tileData > TileType::EMPTY && tileData < TileType::EMPTY + 10)) {
            towerPreview->setColor(Color3B::RED);
        } else {
            towerPreview->setColor(Color3B::WHITE);
        }
    }
}

void DefenseScene::update(float dt) {
}

void DefenseScene::selectGrid(const Vec2 &pos) {
    auto gridPosition = getGridPosition(pos);
    
    mapData.setTileData(gridPosition.x, gridPosition.y, TileType::BARRICADE);
    
    updateMap();
}
