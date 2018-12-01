//
//  MainScene.cpp
//  DefenseGame
//
//  Created by A on 2018. 11. 30..
//

#include "MainScene.h"
#include "OffenseInterface.h"

#include "PathFinding.h"

USING_NS_CC;
using namespace std;

bool MainScene::init() {
    tileSize = 32.0f;
    
    mapData = MapData("data/map1.dat");
    
    auto size = Director::getInstance()->getVisibleSize();
    Vec2 origin = size / 2;
    
    auto bg = LayerColor::create(Color4B::GRAY);
    addChild(bg);
    
    initializeMap();
    
    auto pathFinder = pathfinding::PathFinding::create();
    pathFinder->setupMap(mapData.getPathData());
    
    debugPathDraw = DrawNode::create(4);
    auto path = pathFinder->getShortestPath(Vec2(0, 0), mapData.getTargetPosition());
    for (int i = 0; i < path.size() - 1; i++) {
        Vec2 src = -Vec2(mapData.width, mapData.height) * tileSize * 0.5f + path[i] * tileSize + Vec2(tileSize, tileSize) * 0.5f;
        Vec2 dst = -Vec2(mapData.width, mapData.height) * tileSize * 0.5f + path[i + 1] * tileSize + Vec2(tileSize, tileSize) * 0.5f;
        debugPathDraw->drawLine(src, dst, Color4F::MAGENTA);
    }
    mapLayer->addChild(debugPathDraw);
    
	/* when you offenser */
	offenseInterface = new OffenseInterface();
	offenseInterface->init(this);

    return true;
}

void MainScene::initializeMap() {
    auto size = Director::getInstance()->getVisibleSize();
    Vec2 origin = size / 2;
    
    int width = mapData.width, height = mapData.height;

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

void MainScene::onEnter()
{
	Scene::onEnter();

	auto listener = EventListenerTouchOneByOne::create();

	listener->setSwallowTouches(true);

	listener->onTouchBegan = 
		CC_CALLBACK_2(MainScene::onTouchBegan, this);
	/*
	listener->onTouchMoved =
		CC_CALLBACK_2(OffenseInterface::onTouchMoved, this);

	listener->onTouchEnded =
		CC_CALLBACK_2(OffenseInterface::onTouchEnded, this);
	*/
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void MainScene::onExit()
{
	_eventDispatcher->removeAllEventListeners();
	Scene::onExit();
}

bool MainScene::onTouchBegan(Touch* touch, Event* event)
{
	offenseInterface->onTouchBegan(touch, event);
	return true;
}
