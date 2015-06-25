#pragma once

#include "cocos2d.h"
#include "LayerGameOver.h"

USING_NS_CC;

class SceneGameOver : public Scene
{
public:
	SceneGameOver(void);
	~SceneGameOver(void);

	CREATE_FUNC(SceneGameOver);

	virtual bool init();

	void scoreOverSet(int score);

private:
	LayerGameOver *_layerGameOver;
};