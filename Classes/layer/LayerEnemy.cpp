#include "layer\Enemy.h"
#include "layer\LayerEnemy.h"
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

		schedule(schedule_selector(LayerEnemy::enemyAdd),1.0f);

		isInit = true;
	} while (0);
	return isInit;
}

Vector<Enemy *> LayerEnemy::vecEnemyGet()
{
	return _vecEmemy;
}

void LayerEnemy::enemyAdd( float delte )
{
	auto type = typeEnemyGet();
	Enemy *enemy = Enemy::create(type, CallFuncN::create(CC_CALLBACK_1(LayerEnemy::enemyRemove4Vec,this)));
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

void LayerEnemy::enemyRemove4Vec( Node *enemy )
{
	if (enemy != NULL)
	{
		_vecEmemy.erase(_vecEmemy.find((Enemy *)enemy));
	}
}

void LayerEnemy::enemyBlowupAll()
{
	int i = _vecEmemy.size() - 1;
	for (; i >= 0 ; i--)
	{
		auto enemy = _vecEmemy.at(i);
		if (enemy->hpGet() > 0)
		{
			enemy->blowup();
		}
	}
}