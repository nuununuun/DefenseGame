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

	left = Sprite::create("res/title/LeftDoor.png");
	left->setPosition(Vec2(-640, 720) / 2);
	this->addChild(left);

	right = Sprite::create("res/title/RightDoor.png");
	right->setPosition(Vec2(1280 + 640 / 2, 720 / 2));
	this->addChild(right);


	this->schedule([&](float dt) {
		Vec2 pos = bg->getPosition();
		if (pos.y <= 360 - 15 || pos.y >= 360) ani_add *= -1;
		pos.y += ani_add;
		bg->setPosition(pos);
	}, "ani");

	auto defenseText = MenuItemImage::create("res/title/Dff.png", "res/title/Dff.png");
	auto offenseText = MenuItemImage::create("res/title/Atk.png", "res/title/Atk.png");
	
	auto menu = Menu::create(defenseText, offenseText, nullptr);
	menu->setPosition(Vec2(1280/2, 80));
	menu->alignItemsHorizontally();
	addChild(menu);

	//auto moveTo = MoveTo::create(0.9f, Vec2(1280,720)/2);
	//auto actionInterval = EaseBounceOut::create(moveTo);
	//left->runAction(actionInterval);
	//moveTo = MoveTo::create(0.9f, Vec2(1280, 720) / 2);
	//actionInterval = EaseBounceOut::create(moveTo);
	//right->runAction(actionInterval);
	

    defenseText->setCallback([&] (Ref *r) {
        auto scene = DefenseScene::create();
        auto client = SocketIO::connect("http://10.10.0.66:8080", *scene);
        scene->client = client;
        client->emit("defense", "");
		Director::getInstance()->replaceScene(scene);
    });
    
    offenseText->setCallback([&] (Ref *r) {
        auto scene = OffenseScene::create();
        auto client = SocketIO::connect("http://10.10.0.66:8080", *scene);
        scene->client = client;
        client->emit("offense", "");
        Director::getInstance()->replaceScene(scene);
    });
    
    return true;
}
