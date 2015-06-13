#pragma once

#include "cocos2d.h"

USING_NS_CC;

enum EnumEnemy
{
	SMALL,
	MEDIUM,
	LARGE,
}; 

class LayerEnemy : public Layer
{
public:
	LayerEnemy(void);
	~LayerEnemy(void);

	CREATE_FUNC(LayerEnemy);

	virtual bool init();

	void enemyAdd(float dt);
	void enemyRemove(Sprite *enemy);
	void enemyMoveOut(Node *pSender);
};

