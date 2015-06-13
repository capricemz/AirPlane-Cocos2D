#pragma once

#include "cocos2d.h"
#include "LayerPlane.h"
#include "LayerBullet.h"

USING_NS_CC;

class LayerGame : public Layer
{
public:
	LayerGame(void);
	~LayerGame(void);

    virtual bool init();

	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual void onTouchMoved(Touch *touch, Event *event);

	CREATE_FUNC(LayerGame);

	void LayerGame::backgroundMove(float dt);

private:
	void LayerGame::eventAdd();
	void LayerGame::eventRemove();

private:
	EventListenerTouchOneByOne *eventListener;

	Sprite *background1;
	Sprite *background2;

	LayerPlane *layerPlane;
	LayerBullet *layerBullet;
};