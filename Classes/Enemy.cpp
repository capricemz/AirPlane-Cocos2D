#include "Enemy.h"
#include "util\UtilRandom.h"

Enemy::Enemy(void)
{
}

Enemy::~Enemy(void)
{
}

int Enemy::hpGet()
{
	return hp;
}

void Enemy::hpSet( int value )
{
	hp = value;
}

void Enemy::hpLose( int value )
{
	hp -= value;
}

void Enemy::postionRandomSet()
{
	auto sizeEnemy = getContentSize();
	auto sizeWin = Director::getInstance()->getWinSize();
	UtilRandom::randomBewteen(sizeEnemy.width/2,)
}
