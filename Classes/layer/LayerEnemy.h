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

	Vector<Enemy *> vecEnemyGet();

	void enemyAdd(float dt);
	void enemyRemove(Node *enemy);
	void enemyRemoveAll();

private:
	TypeEnemy typeEnemyGet();
private:
	Vector<Enemy *> _vecEmemy;
};

