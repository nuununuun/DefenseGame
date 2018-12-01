#include "OffenseScene.h"

USING_NS_CC;
using namespace std;

bool OffenseScene::init() {
	if (!MainScene::init()) return false;

	menuLayer = Layer::create();
	addChild(menuLayer);

	auto interfaceFlyingEye = Sprite::create("res/Flying_eye_R.png", Rect(0, 0, 32, 32));
	interfaceFlyingEye->setPosition(Vec2(336, 48) * 0.5f + Vec2(336 + 48 * 2, 0));
	interfaceFlyingEye->setScale(1.5f);
	menuLayer->addChild(interfaceFlyingEye);

	interfaceUnit.push_back(interfaceFlyingEye);

	scheduleUpdate();

	return true;
}

void OffenseScene::onMouseDown(cocos2d::EventMouse *e) {
	MainScene::onMouseDown(e);

}

void OffenseScene::onMouseUp(cocos2d::EventMouse *e) {
	MainScene::onMouseUp(e);

}

void OffenseScene::onMouseMove(cocos2d::EventMouse *e) {
	MainScene::onMouseMove(e);

}

void OffenseScene::update(float dt) {
}

void OffenseScene::selectGrid(const Vec2 &pos) {
	auto gridPosition = getGridPosition(pos);

	mapData.setTileData(gridPosition.x, gridPosition.y, TileType::BARRICADE);

	updateMap();
}
