//
//  MainScene.cpp
//  DefenseGame
//
//  Created by A on 2018. 11. 30..
//

#include "MainScene.h"
#include "OffenseInterface.h"
#include "Constant.h"

#include "Tower.hpp"
#include "SocketServer.h"
#include "SocketClient.h"

USING_NS_CC;
using namespace std;

bool MainScene::init() {
    
    SocketServer server(7000);
    server.listenClient([&] {
        check = true;
    });
    
    SocketClient client("10.10.0.66", 7000);
    client.connectServer([&] (bool con) {
        if (con && !check) MessageBox("", "");
    });
    
    tileSize = 48.0f;
    
    mapData = MapData("data/map1.dat");
    
    auto size = Director::getInstance()->getVisibleSize();
    Vec2 origin = size / 2;
    
    auto bg = LayerColor::create(Color4B::GRAY);
    addChild(bg);
    
    initializeMap();
    
    pathFinder = pathfinding::PathFinding::create();
    pathFinder->retain();
    pathFinder->setupMap(mapData.getPathData());
    
    mouseListener = EventListenerMouse::create();
    mouseListener->onMouseDown = CC_CALLBACK_1(MainScene::onMouseDown, this);
    mouseListener->onMouseUp = CC_CALLBACK_1(MainScene::onMouseUp, this);
    mouseListener->onMouseMove = CC_CALLBACK_1(MainScene::onMouseMove, this);
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
    
	/* when you offenser */
	//offenseInterface = OffenseInterface::create(this);
	//addChild(offenseInterface);

	//offenseInterface->addKenny(0.1f);
	//offenseInterface->addJenny(0.1f);
    return true;
}

void MainScene::initializeMap() {
    auto size = Director::getInstance()->getVisibleSize();
    Vec2 origin = size / 2;
    
    width = mapData.width, height = mapData.height;

    mapLayer = Layer::create();
    mapLayer->setPosition(origin);
    addChild(mapLayer);
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            auto tile = Sprite::create("res/tile.png");
            // -타일 맵 전체 사이즈 / 2 + 타일의 현재 위치 + 타일 하나의 사이즈 / 2
            tile->setPosition(-Vec2(width, height) * tileSize * 0.5f + Vec2(j, i) * tileSize + Vec2(tileSize, tileSize) * 0.5f);
            mapLayer->addChild(tile);
            mapTiles.push_back(tile);
            
            switch (mapData.getTileData(j, i)) {
                case EMPTY: break;
                case STARTING: tile->setColor(Color3B::GREEN); break;
                case BARRICADE: break;
                case CORE: tile->setColor(Color3B::RED); break;
                case SETABLE: tile->setColor(Color3B::GRAY); break;
            }
        }
    }
}

void MainScene::updateMap() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            auto data = mapData.getTileData(j, i);
            if (mapData.isEquals(data, TileType::EMPTY)) {
                
                mapTiles[i * width + j]->setColor(Color3B::WHITE);
                
            } else if (mapData.isEquals(data, TileType::STARTING)) {
                
                mapTiles[i * width + j]->setColor(Color3B::GREEN);
                
            } else if (mapData.isEquals(data, TileType::SETABLE)) {
                
                mapTiles[i * width + j]->setColor(Color3B(100, 50, 50));
                
            } else if (mapData.isEquals(data, TileType::CORE)) {
                
                mapTiles[i * width + j]->setColor(Color3B::RED);
                
            } else if (mapData.isEquals(data, TileType::BARRICADE)) {
                
                mapTiles[i * width + j]->setColor(Color3B::GRAY);
                
            }
        }
    }
}

//bool MainScene::onTouchBegan(Touch* touch, Event* event)
//{
//    offenseInterface->onTouchBegan(touch, event);
//    return true;
//}

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
