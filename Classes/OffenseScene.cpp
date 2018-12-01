#include "OffenseScene.h"

USING_NS_CC;
using namespace std;

bool OffenseScene::init() {
	if (!MainScene::init()) return false;

	lineRenderer = DrawNode::create(3);
	addChild(lineRenderer);

	/*
	menuLayer = Layer::create();
	addChild(menuLayer);

	towerPreview = Sprite::create("res/tower1.png");
	towerPreview->setVisible(false);
	addChild(towerPreview);

	for (int i = 0; i < 8; i++) {
		auto sample = Sprite::create("res/tower1.png");
		sample->setPosition(Vec2(96, i * 64 + 48));
		menuLayer->addChild(sample);
		towerSamples.push_back(sample);
	}
	*/

	scheduleUpdate();

	return true;
}

void OffenseScene::onMouseDown(cocos2d::EventMouse *e) {
	MainScene::onMouseDown(e);
	/*
	for (auto &towerSample : towerSamples) {
		if (towerSample->getBoundingBox().containsPoint(e->getLocationInView())) {
			selectedSample = towerSample;
			break;
		}
	}

	if (selectedSample != nullptr) {
		towerPreview->setPosition(e->getLocationInView());
		towerPreview->setVisible(true);
	}
	*/
}

void OffenseScene::onMouseUp(cocos2d::EventMouse *e) {
	MainScene::onMouseUp(e);
	/*
	if (selectedSample != nullptr) {
		towerPreview->setVisible(false);

		auto gp = getGridPosition(e->getLocationInView());
		if (mapData.isOutOfIndex(gp)) return;

		auto data = mapData.getTileData(gp.x, gp.y);
		if (data == TileType::SETABLE) {
			auto tower = Tower::create();
			tower->setPosition(getRealPosition(gp));
			addChild(tower);
			int type = (int)TileType::SETABLE + 1;
			mapData.setTileData(gp.x, gp.y, (TileType)type);
			towers.push_back(tower);
		}
	}

	selectedSample = nullptr;
	*/
}

void OffenseScene::onMouseMove(cocos2d::EventMouse *e) {
	MainScene::onMouseMove(e);
	/*
	auto pos = e->getLocationInView();

	for (auto tower : towers) {
		if (tower->getBoundingBox().containsPoint(pos)) {
			tower->setVisibleRange();
		}
		else {
			tower->setInvisibleRange();
		}
	}

	if (selectedSample != nullptr) {
		towerPreview->setPosition(pos);

		auto gp = getGridPosition(e->getLocationInView());
		if (mapData.isOutOfIndex(gp)) return;

		auto data = mapData.getTileData(gp.x, gp.y);
		if (data == TileType::SETABLE) {
			towerPreview->setColor(Color3B::WHITE);
		}
		else {
			towerPreview->setColor(Color3B::RED);
		}
	}
	*/
}

void OffenseScene::update(float dt) {
}

void OffenseScene::selectGrid(const Vec2 &pos) {
	auto gridPosition = getGridPosition(pos);

	mapData.setTileData(gridPosition.x, gridPosition.y, TileType::BARRICADE);

	updateMap();
}
