#include "LayerEnemy.h"
#include "Enemy.h"

LayerEnemy::LayerEnemy(void)
{
}

LayerEnemy::~LayerEnemy(void)
{
}

bool LayerEnemy::init()
{
	auto isInit = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());

		isInit = true;
	} while (0);
	return isInit;
}

void LayerEnemy::enemyAdd( float dt )
{
	auto enemy = (Enemy*)Enemy::createWithSpriteFrameName("enemy1.png");
	enemy->hpSet(1);

}

void LayerEnemy::enemyRemove( Sprite *enemy )
{

}

void LayerEnemy::enemyMoveOut( Node *pSender )
{

}
