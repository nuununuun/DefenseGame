//
//  TitleScene.cpp
//  DefenseGame
//
//  Created by A on 2018. 12. 1..
//

#include "TitleScene.hpp"

#include "DefenseScene.h"
#include "OffenseScene.h"

#include "StringUtil.h"

USING_NS_CC;
using namespace cocos2d::network;

bool TitleScene::init() {

    bg = Sprite::create("res/title/Background.png");
    bg->setPosition(Vec2(1280, 720) / 2);
    this->addChild(bg);
    
    auto bottom = Sprite::create("res/title/bottom.png");
    bottom->setPosition(Vec2(1280, 720) / 2);
    this->addChild(bottom);
    
    
    title = Sprite::create("res/title/Maintitle.png");
    title->setPosition(Vec2(1280 / 2, 720));
    title->runAction(MoveTo::create(1.8f, Vec2(1280 / 2, 360)));
    this->addChild(title);
    
    subTitle = Sprite::create("res/title/Subtitle.png");
    subTitle->setPosition(Vec2(1280 / 2, 0));
    subTitle->runAction(MoveTo::create(1.8f, Vec2(1280 / 2, 360)));
    this->addChild(subTitle);

	auto defenseText = MenuItemImage::create("res/title/Dff.png", "res/title/Dff.png");
	auto offenseText = MenuItemImage::create("res/title/Atk.png", "res/title/Atk.png");

	auto menu = Menu::create(defenseText, offenseText, nullptr);
	menu->setPosition(Vec2(1280 / 2, 80));
	menu->alignItemsHorizontally();
	addChild(menu);

    
    left = Sprite::create("res/title/LeftDoor.png");
    left->setPosition(Vec2(-640, 720) / 2);
    this->addChild(left);
    
    right = Sprite::create("res/title/RightDoor.png");
    right->setPosition(Vec2(1280 + 640 / 2, 720 / 2));
    this->addChild(right);
    
    auto act = Sequence::create(EaseSineOut::create(MoveBy::create(2.5, Vec3(0, -4, 0))), EaseSineIn::create(MoveBy::create(2.5, Vec3(0, 8, 0))), nullptr);
    bg->runAction(RepeatForever::create(act));
    
    defenseText->setCallback([&] (Ref *r) {
        dScene = DefenseScene::create();
<<<<<<< HEAD
//        dScene->retain();
        auto client = SocketIO::connect("http://10.10.0.66:8000", *dScene);
=======
        dScene->retain();
        auto client = SocketIO::connect("http://10.10.0.66:8001", *dScene);
>>>>>>> 2b2d4ec671592460b3631284e31779008f6d2107
        dScene->client = client;
        dScene->client->on("connect", [=](SIOClient *c, const std::string &data) {
            dScene->client->emit("defense", "");
            dScene->client->on("summon", [=](SIOClient *c, const std::string &data) {
                if (data == "\"0\"") dScene->addFlyingEye();
                if (data == "\"1\"") dScene->addBaby();
                if (data == "\"2\"") dScene->addFinger();
                if (data == "\"3\"") dScene->addHeart();
                if (data == "\"4\"") dScene->addFist();
                if (data == "\"5\"") dScene->addRib();
                if (data == "\"6\"") dScene->addTooth();
                if (data == "\"7\"") dScene->addCaecum();
            });
            
            auto moveTo = MoveTo::create(0.2f, Vec2(1280, 720) / 2);
            auto actionInterval = EaseQuarticActionOut::create(moveTo);
            Sequence *sequence = Sequence::create(actionInterval, CallFunc::create([&] {
            }), NULL);
            left->runAction(sequence);
            moveTo = MoveTo::create(0.2f, Vec2(1280, 720) / 2);
            actionInterval = EaseQuarticActionOut::create(moveTo);
            right->runAction(actionInterval);
            
            c->on("game-ready", [=](SIOClient *c, const std::string &data) {
                Director::getInstance()->replaceScene(dScene);
            });
        });
    });
    
    offenseText->setCallback([&] (Ref *r) {
<<<<<<< HEAD
        oScene = OffenseScene::create();
        oScene->retain();
        auto client = SocketIO::connect("http://10.10.0.66:8000", *oScene);
        oScene->client = client;
=======
        auto scene = OffenseScene::create();
        auto client = SocketIO::connect("http://10.10.0.66:8001", *scene);
        scene->client = client;
>>>>>>> 2b2d4ec671592460b3631284e31779008f6d2107
        client->on("connect", [=](SIOClient *c, const std::string &data) {
            c->emit("offense", "");
            c->on("build", [=](SIOClient *c, const std::string &data) {
                auto msg = StringUtil::trim(data, "\"");
                auto spl = StringUtil::split(msg, ' ');
                
                int gx = std::stoi(spl[0]), gy = std::stoi(spl[1]), dir = std::stoi(spl[2]);
                oScene->putTower(Vec2(gx, gy), dir);
            });
            
            auto moveTo = MoveTo::create(0.2f, Vec2(1280, 720) / 2);
            auto actionInterval = EaseQuarticActionOut::create(moveTo);
            Sequence *sequence = Sequence::create(actionInterval, CallFunc::create([&] {
            }), NULL);
            left->runAction(sequence);
            moveTo = MoveTo::create(0.2f, Vec2(1280, 720) / 2);
            actionInterval = EaseQuarticActionOut::create(moveTo);
            right->runAction(actionInterval);
            
            c->on("game-ready", [=](SIOClient *c, const std::string &data) {
                Director::getInstance()->replaceScene(oScene);
            });
        });
    });
    
    return true;
}
