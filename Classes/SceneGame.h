#pragma once

#include "cocos2d.h"
#include "layer\LayerGame.h"

class SceneGame : public Scene
{
public:
	SceneGame(void);
	~SceneGame(void);

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	// implement the "static create()" method manually
	CREATE_FUNC(SceneGame);

	LayerGame *_layerGame;//°ÑGameLayer±©Â¶¸øGameScene  
};