#include "ManagetLayer.h"

ManagetLayer* ManagetLayer::_instance = nullptr;//静态成员变量的定义
ManagetLayer::CGarbo ManagetLayer::_garbo;//内嵌类静态成员变量的定义

ManagetLayer::ManagetLayer(void)
{
	_layerBullet = nullptr;
	_layerEnemy = nullptr;
	_layerPlane = nullptr;
	_layerUFO = nullptr;
	_layerUI = nullptr;
}


ManagetLayer::~ManagetLayer(void)
{
}

void ManagetLayer::initLayer( SceneGame *scene )
{
	_layerGame = LayerGame::create();
	scene->addChild(_layerGame);

	//加入layerPlane
	_layerPlane = LayerPlane::create();
	_layerGame->addChild(_layerPlane);

	//加入layerBullet
	_layerBullet = LayerBullet::create();
	_layerGame->addChild(_layerBullet);
	_layerBullet->shootStart();

	//加入layerEnemy
	_layerEnemy = LayerEnemy::create();
	_layerGame->addChild(_layerEnemy);

	//加入layerUFO
	_layerUFO = LayerUFO::create();
	_layerGame->addChild(_layerUFO);

	//加入layerUI
	_layerUI = LayerUI::create();
	_layerGame->addChild(_layerUI);
}

LayerGame * ManagetLayer::layerGameGet()
{
	return _layerGame;
}

LayerPlane * ManagetLayer::layerPlaneGet()
{
	return _layerPlane;
}

LayerBullet * ManagetLayer::layerBulletGet()
{
	return _layerBullet;
}

LayerEnemy * ManagetLayer::layerEnemyGet()
{
	return _layerEnemy;
}

LayerUFO * ManagetLayer::layerUFOGet()
{
	return _layerUFO;
}

LayerUI * ManagetLayer::layerUIGet()
{
	return _layerUI;
}