#pragma once

#include "cocos2d.h"
#include "layer\LayerUFO.h"
#include "layer\LayerEnemy.h"
#include "layer\LayerBullet.h"
#include "layer\LayerPlane.h"

USING_NS_CC;

class LayerGame : public Layer
{
public:
	LayerGame(void);
	~LayerGame(void);

	CREATE_FUNC(LayerGame);
    virtual bool init();

	void LayerGame::backgroundMove(float delta);

	void update(float delta) override;

private:
	void LayerGame::eventAdd();
	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual void onTouchMoved(Touch *touch, Event *event);
	void LayerGame::eventRemove();

	void updateCollisionBulletEnemy();
	void updateCollisionUFOPlane();
private:
	EventListenerTouchOneByOne *_eventListener;

	Sprite *_background1;
	Sprite *_background2;

	LayerPlane *_layerPlane;
	LayerBullet *_layerBullet;
	LayerEnemy *_layerEnemy;
	LayerUFO *_layerUFO;
};