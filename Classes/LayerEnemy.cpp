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

		isInit = true;
	} while (0);
	return isInit;
}

void LayerEnemy::enemyAdd( float dt )
{
	auto type = typeEnemyGet();
	auto enemy = Enemy::create(type);


	auto sizeEnemy = enemy->getContentSize();
	auto sizeWin = Director::getInstance()->getWinSize();
	auto xActual = UtilRandom::randomBewteen(sizeEnemy.width/2,sizeWin.width - sizeEnemy.width/2);//Ëæ»ú³õÊ¼Î»ÖÃ
	enemy->setPosition(xActual,sizeWin.height + sizeEnemy.height/2);

	float durationActual = 3;
	auto actionMoveBy = MoveBy::create(durationActual,Size(0,sizeWin.height + sizeEnemy.height));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(LayerEnemy::enemyMoveOut,this));

	auto sequence = Sequence::create(actionMoveBy,actionDone,NULL);

	enemy->runAction(sequence);
}

void LayerEnemy::enemyRemove( Sprite *enemy )
{

}

void LayerEnemy::enemyMoveOut( Node *node )
{

}

TypeEnemy LayerEnemy::typeEnemyGet()
{
	vector<TypeEnemy> values;
	values.push_back(SMALL);
	values.push_back(MEDIUM);
	values.push_back(LARGE);
	vector<float> probabilityDistribution;
	probabilityDistribution.push_back(0.5f);
	probabilityDistribution.push_back(0.35f);
	probabilityDistribution.push_back(0.15f);
	auto randomPitchUpon = UtilRandom::randomPitchUpon(probabilityDistribution);
	return values[randomPitchUpon];
}