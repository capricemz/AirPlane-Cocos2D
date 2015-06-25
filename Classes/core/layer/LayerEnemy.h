#pragma once

#include "cocos2d.h"
#include "Enemy.h"

USING_NS_CC;

class LayerEnemy : public Layer
{
public:
	LayerEnemy(void);
	~LayerEnemy(void);

	CREATE_FUNC(LayerEnemy);

	virtual bool init();

	Vector<Enemy *> vecEnemyGet();

	void enemyBlowupAll();

	void addStop();

private:
	TypeEnemy typeEnemyGet();
	void enemyAdd(float delte);
	void enemyRemove4Vec(Node *enemy);

private:
	Vector<Enemy *> _vecEmemy;

};

