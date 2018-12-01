//
//  DefenseScene.cpp
//  DefenseGame
//
//  Created by A on 2018. 12. 1..
//

#include "DefenseScene.h"

#include "Tower.hpp"
#include "Unit.hpp"

#include "Projectile.hpp"

USING_NS_CC;
using namespace std;

bool DefenseScene::init() {
    if (!MainScene::init()) return false;
    
    directionRenderer = DrawNode::create(3);
    addChild(directionRenderer);
    
    menuLayer = Layer::create();
    addChild(menuLayer);
    
    towerPreview = Sprite::create("res/tower1.png");
    towerPreview->setVisible(false);
    addChild(towerPreview);
    
    /// tower1
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 2; j++) {
            auto sample = Sprite::create("res/tower1.png");
            sample->setPosition(Vec2(967 + j * 98, 118 + i * 98));
            sample->setGlobalZOrder(1001);
            menuLayer->addChild(sample);
            towerSamples.push_back(sample);
        }
    }
    
    scheduleUpdate();
    
    return true;
}

void DefenseScene::onMouseDown(cocos2d::EventMouse *e) {
    MainScene::onMouseDown(e);
    
    for (auto &towerSample : towerSamples) {
        if (towerSample->getBoundingBox().containsPoint(e->getLocationInView())) {
            selectedSample = towerSample;
            towerState = 1;
            break;
        }
    }
    
    if (selectedSample != nullptr) {
        towerPreview->setPosition(e->getLocationInView());
        towerPreview->setVisible(true);
        directionRenderer->clear();
    }
}

void DefenseScene::onMouseMove(cocos2d::EventMouse *e) {
    MainScene::onMouseMove(e);
    
    auto pos = e->getLocationInView();
    
        for (auto tower : towers) {
            if (tower->getBoundingBox().containsPoint(pos)) {
                tower->setVisibleRange();
            } else {
                tower->setInvisibleRange();
            }
        }
    
    if (towerState == 1) {
        towerPreview->setPosition(pos);
        
        auto gp = getGridPosition(e->getLocationInView());
        CCLOG((to_string(gp.x) + ", " + to_string(gp.y)).c_str());
        if (mapData.isOutOfIndex(gp)) return;
        
        auto data = mapData.getTileData(gp.x, gp.y);
        if (data == TileType::SETABLE && isAbleTower(gp)) {
            towerPreview->setColor(Color3B::WHITE);
            drawTowerRange(gp);
        } else {
            towerPreview->setColor(Color3B::RED);
            directionRenderer->clear();
        }
    }
}

void DefenseScene::onMouseUp(cocos2d::EventMouse *e) {
    MainScene::onMouseUp(e);
    auto pos = e->getLocationInView();
    auto gp = getGridPosition(pos);
    
    if (towerState == 1) {
        if (mapData.isOutOfIndex(gp) || !isAbleTower(gp) || mapData.getTileData(gp.x, gp.y) != TileType::SETABLE) {
            towerState = 0;
            clearPreview();
            return;
        }
        
        Vec2 rp = getRealPosition(gp);
        towerPreview->setPosition(rp);

        towerState = 2;
    } else if (towerState == 2) {
        for (int i = 0; i < 4; i++) {
            Vec2 dir = Tower::idxToDir(i);
            
            if (gp == dir + getGridPosition(towerPreview->getPosition())) {
                putTower(i);
                clearPreview();
                directionRenderer->clear();
                break;
            }
        }
        
        towerState = 0;
    }
    
    selectedSample = nullptr;
}

void DefenseScene::putTower(int dir) {
    towerState = 0;
    
    auto gp = getGridPosition(towerPreview->getPosition());
    if (mapData.getTileData(gp.x, gp.y) == TileType::SETABLE) {
        auto tower = Tower::create(dir, Tower::ARROW);
        tower->setPosition(getRealPosition(gp));
        addChild(tower);
        int type = (int)TileType::SETABLE + 1;
        mapData.setTileData(gp.x, gp.y, (TileType)type);
        towers.push_back(tower);
    }
}

void DefenseScene::selectGrid(const Vec2 &pos) {
    auto gridPosition = getGridPosition(pos);
    
    mapData.setTileData(gridPosition.x, gridPosition.y, TileType::BARRICADE);
    
    updateMap();
}

void DefenseScene::drawTowerRange(const Vec2 &gp) {
    directionRenderer->clear();
    for (int i = 0; i < 4; i++) {
        Vec2 dir = Tower::idxToDir(i);
        if (mapData.isOutOfIndex(gp + dir)) continue;
        auto data = mapData.getTileData(gp.x + dir.x, gp.y + dir.y);
        
        if (mapData.isEquals(data, TileType::SETABLE)) continue;
        
        Vec2 rp = getRealPosition(gp);
        directionRenderer->drawSolidRect(rp + dir * 48 - Vec2(20, 20), rp + dir * 48 + Vec2(20, 20), Color4F::RED);
    }
}

bool DefenseScene::isAbleTower(const Vec2 &gp) {
    int cnt = 0;
    for (int i = 0; i < 4; i++) {
        Vec2 dir = Tower::idxToDir(i);
        if (mapData.isOutOfIndex(gp + dir)) continue;
        auto data = mapData.getTileData(gp.x + dir.x, gp.y + dir.y);
        
        if (mapData.isEquals(data, TileType::SETABLE)) continue;
        
        cnt += 1;
    }
    
    return cnt;
}

void DefenseScene::clearPreview() {
    towerPreview->setVisible(false);
}

void DefenseScene::update(float dt) {
    for (auto &tower : towers) {
        // check
        if (tower->attackTick >= tower->attackDelay) {
            tower->act();
            tower->attackTick = 0;
        } else tower->attackTick += 1.0f * dt;
    }
    updateTime(dt);
}
