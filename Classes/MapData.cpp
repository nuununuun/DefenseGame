//
//  MapData.cpp
//  DefenseGame
//
//  Created by A on 2018. 12. 1..
//

#include "MapData.h"
#include "cocos2d.h"

#include <iostream>
#include <fstream>

using namespace std;
USING_NS_CC;

MapData::MapData() : width(0), height(0) {}

MapData::MapData(const string &path) {
    ifstream input(path);

    input >> width >> height;
    
    for (int i = 0; i < height; i++) {
        data.push_back(vector<int>());
        pathData.push_back(vector<int>());
    }
    for (int i = height - 1; i >= 0; i--) {
        for (int j = 0; j < width; j++) {
            int val;
            input >> val;
            data[i].push_back(val * 10);
            pathData[i].push_back(0);
        }
    }
    updatePathData();

    input.close();
}

void MapData::updatePathData() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (isEquals((TileType)data[i][j], TileType::SETABLE) || isEquals((TileType)data[i][j], TileType::BARRICADE)) pathData[i][j] = 1;
        }
    }
}

TileType MapData::getTileData(int x, int y) {
    CCASSERT((x < width && x >= 0 && y < height && y >= 0), "out of index");
    return (TileType)data[y][x];
}

void MapData::setTileData(int x, int y, TileType type) {
    CCASSERT((x < width && x >= 0 && y < height && y >= 0), "out of index");
    data[y][x] = type;
}

vector<vector<int> > &MapData::getData() {
    return data;
}

vector<vector<int> > &MapData::getPathData() {
    return pathData;
}

cocos2d::Vec2 MapData::getTargetPosition() {
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            if (data[i][j] == TileType::CORE) return Vec2(j, i);
        }
    }
}

bool MapData::isOutOfIndex(const cocos2d::Vec2 &pos) {
    return !(pos.x > 0 && pos.x < width && pos.y > 0 && pos.y < height);
}

bool MapData::isEquals(TileType o, TileType type) {
    return o >= type && (o < type + 10);
}
