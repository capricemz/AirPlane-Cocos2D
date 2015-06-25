#pragma once

#include "cocos2d.h"
#include "..\SceneGame.h"
#include "LayerPlane.h"
#include "LayerEnemy.h"
#include "LayerUFO.h"
#include "LayerUI.h"
#include "LayerBullet.h"

USING_NS_CC;

class ManagetLayer
{
public:
	//提供getInstance全局指针
	static ManagetLayer * getInstance()
	{
		if (_instance == nullptr)
		{
			_instance = new ManagetLayer();
		}
		return _instance;
	};
private:
	ManagetLayer(void);

	static ManagetLayer *_instance;

	class CGarbo//唯一的作用就是在析构时删除m_pInstance
	{
	public:
		~CGarbo()
		{
			if (ManagetLayer::_instance != nullptr)
			{
				delete ManagetLayer::_instance;
			}
		}
	};

	static CGarbo _garbo;//程序结束，系统会自动调用其析构函数

public:
	~ManagetLayer(void);

	void createLayer(SceneGame *scene);

	LayerGame * layerGameGet();
	LayerPlane * layerPlaneGet();
	LayerBullet * layerBulletGet();
	LayerEnemy * layerEnemyGet();
	LayerUFO * layerUFOGet();
	LayerUI * layerUIGet();

	void destoryLayer();

private:
	LayerGame *_layerGame;
	LayerPlane *_layerPlane;
	LayerBullet *_layerBullet;
	LayerEnemy *_layerEnemy;
	LayerUFO *_layerUFO;
	LayerUI *_layerUI;
};

