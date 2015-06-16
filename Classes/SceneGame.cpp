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
		_layerGame = LayerGame::create();//�������ȡGameLayerʵ��
		CC_BREAK_IF(!_layerGame);
		addChild(_layerGame);//add _gameLayer��������

		auto test = TestSpriteBtachNode::create();
		addChild(test);

		isInit = true;
	} while (0);
	return isInit;
}