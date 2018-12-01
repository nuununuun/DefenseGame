//
//  TitleScene.cpp
//  DefenseGame
//
//  Created by A on 2018. 12. 1..
//

#include "TitleScene.hpp"

#include "DefenseScene.h"
#include "OffenseScene.h"

USING_NS_CC;
using namespace cocos2d::network;

bool TitleScene::init() {
    auto defenseText = MenuItemLabel::create(Label::createWithSystemFont("Defense", "", 32));
    auto offenseText = MenuItemLabel::create(Label::createWithSystemFont("Offense", "", 32));
    
    auto menu = Menu::create(defenseText, offenseText, nullptr);
    menu->setPosition(Vec2(1280, 720) / 2);
    menu->alignItemsHorizontally();
    addChild(menu);
    
    
    defenseText->setCallback([&] (Ref *r) {
        auto scene = DefenseScene::create();
        auto client = SocketIO::connect("http://10.10.0.66:8080", *scene);
        scene->client = client;
        client->emit("defense", "");
        client->on("connect", [=](SIOClient *c, const std::string &data){
            client->emit("defense", "");
            client->on("summon", [=](SIOClient *c, const std::string &data) {
                if (data == "\"0\"") scene->addFlyingEye();
                if (data == "\"1\"") scene->addBaby();
                if (data == "\"2\"") scene->addFinger();
                if (data == "\"3\"") scene->addHeart();
                if (data == "\"4\"") scene->addRib();
            });

        });
		Director::getInstance()->replaceScene(scene);
    });
    
    offenseText->setCallback([&] (Ref *r) {
        auto scene = OffenseScene::create();
        auto client = SocketIO::connect("http://10.10.0.66:8080", *scene);
        scene->client = client;
        client->emit("offense", "");
        client->on("connect", [=](SIOClient *c, const std::string &data){
            client->emit("offense", "");
        });
        Director::getInstance()->replaceScene(scene);
    });
    
    return true;
}
