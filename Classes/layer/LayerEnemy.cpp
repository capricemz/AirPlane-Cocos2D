#include "LayerEnemy.h"
#include "Enemy.h"
#include "util\UtilRandom.h"

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

		schedule(schedule_selector(LayerEnemy::enemyAdd),0.5f);

		isInit = true;
	} while (0);
	return isInit;
}

Vector<Enemy *> LayerEnemy::vecEnemyGet()
{
	return _vecEmemy;
}

void LayerEnemy::enemyAdd( float dt )
{
	auto type = typeEnemyGet();
	Enemy *enemy = Enemy::create(type, CallFuncN::create(CC_CALLBACK_1(LayerEnemy::enemyRemove,this)));
	addChild(enemy);
	_vecEmemy.pushBack(enemy);
}

TypeEnemy LayerEnemy::typeEnemyGet()
{
	vector<TypeEnemy> values;
	values.push_back(TypeEnemy::SMALL);
	values.push_back(TypeEnemy::MEDIUM);
	values.push_back(TypeEnemy::LARGE);
	vector<float> probabilityDistribution;
	probabilityDistribution.push_back(0.5f);
	probabilityDistribution.push_back(0.35f);
	probabilityDistribution.push_back(0.15f);
	auto randomPitchUpon = UtilRandom::randomPitchUpon(probabilityDistribution);
	return values[randomPitchUpon];
}

void LayerEnemy::enemyRemove( Node *enemy )
{
	if (enemy != NULL)
	{
		_vecEmemy.erase(_vecEmemy.find((Enemy *)enemy));
	}
}

void LayerEnemy::enemyRemoveAll()
{
	for (auto enemy : _vecEmemy)
	{
		if (enemy->hpGet() > 0)
		{
			enemy->blowup();
		}
	}
}