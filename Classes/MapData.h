//
//  MapData.h
//  DefenseGame
//
//  Created by A on 2018. 12. 1..
//

#ifndef MapData_h
#define MapData_h

#include "cocos2d.h"
#include <vector>

using TileType = enum {
    EMPTY = 0, STARTING = 10, SETABLE = 20, CORE = 30, BARRICADE = 40
};

class MapData {
public:
    MapData();
    MapData(const std::string &path);
        
    TileType getTileData(int x, int y);
    void setTileData(int x, int y, TileType type);
    
    // get all tile data
    std::vector<std::vector<int> > &getData();
    cocos2d::Vec2 getTargetPosition();
    
    bool isOutOfIndex(const cocos2d::Vec2 &pos);
    bool isEquals(TileType o, TileType type);
    
    void updatePathData();
    std::vector<std::vector<int> > &getPathData();
    
public:
    int width, height;
    
public:
    std::vector<std::vector<int> > data;
    std::vector<std::vector<int>> showData;
    std::vector<std::vector<int> > pathData;
    
};

#endif /* MapData_h */
