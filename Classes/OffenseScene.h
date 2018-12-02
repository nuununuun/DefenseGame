#ifndef OFFENSE_SCENE_H_
#define OFFENSE_SCENE_H_

#include "MainScene.h"
#include "cocos2d.h"
#include <vector>
#include "OffenseUnit.h"

class OffenseScene : public MainScene {
public:
	bool init();
    
    virtual void onConnect(SIOClient* client) override;

	void onMouseDown(cocos2d::EventMouse *e) override;
	void onMouseUp(cocos2d::EventMouse *e) override;
	void onMouseMove(cocos2d::EventMouse *e) override;

	void addFlyingEye();
	void addBaby();
	void addFinger();
	void addHeart();
	void addRib();
	void addTooth();
	void addCaecum();
	void addFist();
	void setFirstPosition(cocos2d::Sprite* sprite);

	void selfRemover(cocos2d::Node* sender);
	void update(float dt);
    
    void putTower(int dir);

	CREATE_FUNC(OffenseScene);

public:
	void selectGrid(const cocos2d::Vec2 &pos);

	cocos2d::Vec2 mouseDownPosition;
	cocos2d::Layer *menuLayer;
	bool isMouseDown = false;
	void updateCoolTime(float dt);

private:
	cocos2d::Sprite *interfaceFlyingEye;
	//cocos2d::Sprite *spriteFlyingEye;

	cocos2d::Sprite *interfaceBaby;
	//cocos2d::Sprite *spriteBaby;

	cocos2d::Sprite *interfaceFinger;
	//cocos2d::Sprite *spriteFinger;

	cocos2d::Sprite *interfaceHeart;
	//cocos2d::Sprite *spriteHeart;

	cocos2d::Sprite *interfaceRib;
	//cocos2d::Sprite *spriteRib;

	cocos2d::Sprite *interfaceTooth;

	cocos2d::Sprite *interfaceCaecum;

	cocos2d::Sprite *interfaceFist;

	void addShootFire(cocos2d::Point pt);
	void weaponRemover(Node* sender);
	void IsCollision(float dt);
	std::vector<OffenseUnit*> offenseUnits;
	std::vector<cocos2d::Sprite*> weaponArr;
	void shootFromCharacter();
	cocos2d::Sprite *bullet;
	cocos2d::Point mPtShoot;
	float fireCool;

	bool mIsShoot;
private:
	int coreHealth;
	cocos2d::Sprite *hpBar_fill;
	cocos2d::Sprite *hpBar_empty;

	float money;
	std::vector<cocos2d::Sprite *>cost;
};

#endif
