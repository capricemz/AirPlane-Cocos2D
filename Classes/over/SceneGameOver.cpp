#include "SceneGameOver.h"

SceneGameOver::SceneGameOver(void)
{
	_layerGameOver = nullptr;
}

SceneGameOver::~SceneGameOver(void)
{
}

bool SceneGameOver::init()
{
	auto isInit = false;
	do 
	{
		CC_BREAK_IF(!Scene::init());
		_layerGameOver = LayerGameOver::create();
		CC_BREAK_IF(!_layerGameOver);
		addChild(_layerGameOver);
		isInit = true;
	} while (0);
	return isInit;
}

void SceneGameOver::scoreOverSet( int score )
{
	_layerGameOver->scoreOverSet(score);
}
