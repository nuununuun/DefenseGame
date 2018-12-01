#ifndef OFFENSE_SCENE_H_
#define OFFENSE_SCENE_H_

#include "MainScene.h"
#include <vector>

class OffenseScene : public MainScene {
public:
	bool init();

	void onMouseDown(cocos2d::EventMouse *e) override;
	void onMouseUp(cocos2d::EventMouse *e) override;
	void onMouseMove(cocos2d::EventMouse *e) override;

	void update(float dt);

	CREATE_FUNC(OffenseScene);

public:
	void selectGrid(const cocos2d::Vec2 &pos);


	cocos2d::Vec2 mouseDownPosition;

	cocos2d::Layer *menuLayer;
	std::vector<cocos2d::Sprite *>interfaceUnit;
	/*
	cocos2d::Layer *menuLayer;
	std::vector<cocos2d::Sprite *> towerSamples;
	std::vector<Tower *> towers;
	cocos2d::Node *selectedSample;
	cocos2d::Sprite *towerPreview;
	*/
	bool isMouseDown = false;
};

#endif