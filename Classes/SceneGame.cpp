#include "SceneGame.h"
#include "tests\TestSpriteBtachNode.h"

SceneGame::SceneGame(void)
{
	_layerGame = NULL;
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
		_layerGame = LayerGame::create();//在这里获取GameLayer实例
		CC_BREAK_IF(!_layerGame);
		addChild(_layerGame);//add _gameLayer到场景中

		auto test = TestSpriteBtachNode::create();
		addChild(test);

		isInit = true;
	} while (0);
	return isInit;
}