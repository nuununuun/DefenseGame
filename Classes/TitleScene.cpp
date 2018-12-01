//
//  TitleScene.cpp
//  DefenseGame
//
//  Created by A on 2018. 12. 1..
//

#include "TitleScene.hpp"

USING_NS_CC;
using namespace cocos2d::network;

bool TitleScene::init() {
    auto defenseText = MenuItemLabel::create(Label::createWithSystemFont("Defense", "", 32));
    auto offenseText = MenuItemLabel::create(Label::createWithSystemFont("Offense", "", 32));
    
    auto menu = Menu::create(defenseText, offenseText, nullptr);
    menu->setPosition(Vec2(1280, 720) / 2);
    menu->alignItemsHorizontally();
    addChild(menu);
    
//    SocketIO::connect("http://10.10.0.66:8080", );
    
    defenseText->setCallback([&] (Ref *r) {
        
    });
    
    offenseText->setCallback([&] (Ref *r) {
        
    });
    
    return true;
}