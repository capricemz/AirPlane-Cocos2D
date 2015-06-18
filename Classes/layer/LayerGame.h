#pragma once

#include "cocos2d.h"
#include "layer\LayerUFO.h"
#include "layer\LayerEnemy.h"
#include "layer\LayerBullet.h"
#include "layer\LayerPlane.h"
#include "layer\LayerUI.h"

USING_NS_CC;

class LayerGame : public Layer
{
public:
	//提供getInstance全局指针
	static LayerGame * getInstance()
	{
		if (_instance == NULL)
		{
			_instance = LayerGame::create();
		}
		return _instance;
	};
private:
	LayerGame(void);

	CREATE_FUNC(LayerGame);
	virtual bool init();

	static LayerGame *_instance;
	
	class CGarbo//唯一的作用就是在析构时删除m_pInstance
	{
	public:
		~CGarbo()
		{
			if (LayerGame::_instance != NULL)
			{
				delete LayerGame::_instance;
			}
		}
	};
	
	static CGarbo _garbo;//程序结束，系统会自动调用其析构函数

public:
	~LayerGame(void);

	void LayerGame::backgroundMove(float delta);

	void update(float delta) override;

	LayerPlane * layerPlaneGet();
	LayerEnemy * layerEnemyGet();

private:
	void LayerGame::eventAdd();
	virtual bool onTouchBegan(Touch *touch, Event *event);
	virtual void onTouchMoved(Touch *touch, Event *event);
	void LayerGame::eventRemove();

	void updateCollisionBulletEnemy();
	void updateCollisionUFOPlane();

private:
	EventListenerTouchOneByOne *_eventListener;

	Sprite *_background1;
	Sprite *_background2;

	LayerPlane *_layerPlane;
	LayerBullet *_layerBullet;
	LayerEnemy *_layerEnemy;
	LayerUFO *_layerUFO;
	LayerUI *_layerUI;
};