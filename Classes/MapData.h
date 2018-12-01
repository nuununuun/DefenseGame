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
    EMPTY, STARTING, SETABLE, CORE, BARRICADE
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
    
private:
    std::vector<std::vector<int> > data;
    std::vector<std::vector<int> > pathData;
    
};

#endif /* MapData_h */
