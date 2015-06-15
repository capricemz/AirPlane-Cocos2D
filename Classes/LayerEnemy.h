#pragma once

#include "cocos2d.h"
#include "Enemy.h"

USING_NS_CC;

/*
struct StructEnemy
{
	int id;
	int hp;
};*/

class LayerEnemy : public Layer
{
public:
	LayerEnemy(void);
	~LayerEnemy(void);

	CREATE_FUNC(LayerEnemy);

	virtual bool init();

	void enemyAdd(float dt);
	void enemyRemove(Sprite *enemy);
	void enemyMoveOut(Node *node);
private:
	TypeEnemy typeEnemyGet();
};

