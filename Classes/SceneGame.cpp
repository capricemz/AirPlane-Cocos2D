#include "SceneGame.h"
#include "layer\ManagetLayer.h"

SceneGame::SceneGame(void)
{
}

SceneGame::~SceneGame(void)
{
}

bool SceneGame::init()
{
	auto isInit = false;
	do
	{
		CC_BREAK_IF(!Scene::init());
		ManagetLayer::getInstance()->initLayer(this);

		isInit = true;
	} while (0);
	return isInit;
}