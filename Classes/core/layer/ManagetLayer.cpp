#include "ManagetLayer.h"

ManagetLayer* ManagetLayer::_instance = nullptr;//��̬��Ա�����Ķ���
ManagetLayer::CGarbo ManagetLayer::_garbo;//��Ƕ�ྲ̬��Ա�����Ķ���

ManagetLayer::ManagetLayer(void)
{
	destoryLayer();
}


ManagetLayer::~ManagetLayer(void)
{
}

void ManagetLayer::createLayer( SceneGame *scene )
{
	_layerGame = LayerGame::create();
	scene->addChild(_layerGame);

	//����layerPlane
	_layerPlane = LayerPlane::create();
	_layerGame->addChild(_layerPlane);

	//����layerBullet
	_layerBullet = LayerBullet::create();
	_layerGame->addChild(_layerBullet);

	//����layerEnemy
	_layerEnemy = LayerEnemy::create();
	_layerGame->addChild(_layerEnemy);

	//����layerUFO
	_layerUFO = LayerUFO::create();
	_layerGame->addChild(_layerUFO);

	//����layerUI
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

void ManagetLayer::destoryLayer()
{
	_layerGame = nullptr;
	_layerPlane = nullptr;
	_layerBullet = nullptr;
	_layerEnemy = nullptr;
	_layerUFO = nullptr;
	_layerUI = nullptr;
}