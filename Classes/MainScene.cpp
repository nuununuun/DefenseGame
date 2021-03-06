//
//  MainScene.cpp
//  DefenseGame
//
//  Created by A on 2018. 11. 30..
//

#include "MainScene.h"
#include "Constant.h"

#include "Tower.hpp"

USING_NS_CC;
using namespace std;

bool MainScene::init() {
    tileSize = 48.0f;
    
    mapData = MapData("data/map1.tmx");
    
    auto size = Director::getInstance()->getVisibleSize();
    auto winSize = Director::getInstance()->getWinSize();
    Vec2 origin = size / 2;
    
    auto bg = Sprite::create("res/background.png");
    bg->setPosition(winSize * 0.5f);
    bg->getTexture()->setAliasTexParameters();
    bg->setGlobalZOrder(100);
    addChild(bg);
    
    auto toolbox = Sprite::create("res/toolbox.png");
    toolbox->setPosition(origin);
    toolbox->getTexture()->setAliasTexParameters();
    toolbox->setGlobalZOrder(1000);
    addChild(toolbox);
    
    auto toolboxInner = Sprite::create("res/toolboxInner.png");
    toolboxInner->setPosition(origin);
    toolboxInner->getTexture()->setAliasTexParameters();
    toolboxInner->setGlobalZOrder(999);
    addChild(toolboxInner);
    
    //    timeLabel = Label::createWithTTF(, <#const std::string &fontFilePath#>, <#float fontSize#>)
    //    this->setPosition();
    //    this->addChild(timeLabel);
    initializeMap();
    
    pathFinder = pathfinding::PathFinding::create();
    pathFinder->retain();
    pathFinder->setupMap(mapData.getPathData());
    
    mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(MainScene::onMouseDown, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(MainScene::onMouseUp, this);
    mouseListener->onMouseMove = CC_CALLBACK_1(MainScene::onMouseMove, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
    
    return true;
}

void MainScene::initializeMap() {
    auto size = Director::getInstance()->getVisibleSize();
    Vec2 origin = size / 2;
    
    width = mapData.width, height = mapData.height;

    mapLayer = Layer::create();
    mapLayer->setPosition(Vec2(width * tileSize * 0.5f + 48, origin.y));
    addChild(mapLayer);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            //tile 위치
            int x = mapData.showData[i][j] % 4;
            int y = mapData.showData[i][j] / 4;
            
            auto tile = Sprite::create("res/ALLtiles.png");
            // -타일 맵 전체 사이즈 / 2 + 타일의 현재 위치 + 타일 하나의 사이즈 / 2
            tile->setPosition(-Vec2(width, height) * tileSize * 0.5f + Vec2(j, i) * tileSize + Vec2(tileSize, tileSize) * 0.5f);
            tile->setTextureRect(Rect(x * 48, y * 48, 48, 48));
            tile->getTexture()->setAliasTexParameters();
            mapLayer->addChild(tile);
            mapTiles.push_back(tile);
            
//            switch (mapData.getTileData(j, i)) {
//                case EMPTY: break;
//                case STARTING: tile->setColor(Color3B::GREEN); break;
//                case BARRICADE: break;
//                case CORE: tile->setColor(Color3B::RED); break;
//                case SETABLE: tile->setColor(Color3B::GRAY); break;
//            }
        }
    }
}

void MainScene::updateMap() {
//    for (int i = 0; i < height; i++) {
//        for (int j = 0; j < width; j++) {
//            auto data = mapData.getTileData(j, i);
//            if (mapData.isEquals(data, TileType::EMPTY)) {
//
//                mapTiles[i * width + j]->setColor(Color3B::WHITE);
//
//            } else if (mapData.isEquals(data, TileType::STARTING)) {
//
//                mapTiles[i * width + j]->setColor(Color3B::GREEN);
//
//            } else if (mapData.isEquals(data, TileType::SETABLE)) {
//
//                mapTiles[i * width + j]->setColor(Color3B(100, 50, 50));
//
//            } else if (mapData.isEquals(data, TileType::CORE)) {
//
//                mapTiles[i * width + j]->setColor(Color3B::RED);
//
//            } else if (mapData.isEquals(data, TileType::BARRICADE)) {
//
//                mapTiles[i * width + j]->setColor(Color3B::GRAY);
//
//            }
//        }
//    }
}

bool MainScene::updateTime(float dt)
{
    timeNow -= dt;
 
    //label에 시간 업데이트

    secCounter += dt;
    if(secCounter >= 1000){
        secCounter -= 1000;
        return true;
    }
    return false;
}

void MainScene::onMouseDown(EventMouse *e) {
}

void MainScene::onMouseUp(EventMouse *e) {
}

void MainScene::onMouseMove(EventMouse *e) {
}

Vec2 MainScene::getGridPosition(const Vec2 &rp) {
    auto p = mapLayer->convertToNodeSpace(rp);
    return Vec2(int((p.x + width * tileSize * 0.5f) / tileSize), int((p.y + height * tileSize * 0.5f) / tileSize));
}

Vec2 MainScene::getRealPosition(const cocos2d::Vec2 &gp) {
    return mapLayer->convertToWorldSpace(gp * tileSize) - Vec2(width - 1, height - 1) * tileSize * 0.5f;
}
