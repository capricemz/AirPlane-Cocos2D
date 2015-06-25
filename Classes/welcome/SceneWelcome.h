#pragma once

#include "cocos2d.h"
#include "welcome/LayerWelcome.h"

USING_NS_CC;

class SceneWelcome : public Scene
{
public:
	SceneWelcome(void);
	~SceneWelcome(void);

	CREATE_FUNC(SceneWelcome);

	virtual bool init();

private:
	void preloadMusic();

private:
	LayerWelcome *_layerWelcome;

};