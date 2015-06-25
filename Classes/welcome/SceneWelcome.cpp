#include "welcome/SceneWelcome.h"

SceneWelcome::SceneWelcome(void)
{
	_layerWelcome = nullptr;
}

SceneWelcome::~SceneWelcome(void)
{
}

bool SceneWelcome::init()
{
	auto isInit = false;
	do 
	{
		CC_BREAK_IF(!Scene::init());
		_layerWelcome = LayerWelcome::create();
		CC_BREAK_IF(!_layerWelcome);
		addChild(_layerWelcome);
		preloadMusic();

		isInit = true;
	} while (0);
	return isInit;
}

void SceneWelcome::preloadMusic()
{

}
