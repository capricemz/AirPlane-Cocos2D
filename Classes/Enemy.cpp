#include "Enemy.h"
#include "LayerEnemy.h"
#include "util\UtilRandom.h"

using namespace std;

Enemy::Enemy(void)
{
}

Enemy::~Enemy(void)
{
}

Enemy *Enemy::create( TypeEnemy value )
{
	Enemy *enemy = new Enemy(); 
	if (enemy && enemy->init(value)) 
	{ 
		enemy->autorelease(); 
		return enemy; 
	} 
	else 
	{ 
		delete enemy; 
		enemy = NULL; 
		return NULL; 
	}
}

bool Enemy::init(TypeEnemy value)
{
	auto isInit = false;
	do 
	{
		_type = value;
		string spriteFrameName;
		switch (value)
		{
		case SMALL:
			spriteFrameName = "enemy1.png";
			_hp = 1;
			break;
		case MEDIUM:
			spriteFrameName = "enemy2.png";
			_hp = 2;
			break;
		case LARGE:
			spriteFrameName = "enemy3_n1.png";
			_hp = 3;
			break;
		default:
			spriteFrameName = "enemy1.png";
			_hp = 1;
			break;
		}
		CC_BREAK_IF(!initWithSpriteFrameName(spriteFrameName));

		isInit = true;
	} while (0);
	return isInit;
}

void Enemy::actionSet( const std::function<void(Node*)> &func )
{
	auto sizeEnemy = getContentSize();
	auto sizeWin = Director::getInstance()->getWinSize();
	auto xActual = UtilRandom::randomBewteen(sizeEnemy.width/2,sizeWin.width - sizeEnemy.width/2);//Ëæ»ú³õÊ¼Î»ÖÃ
	setPosition(xActual,sizeWin.height + sizeEnemy.height/2);

	float durationActual = 3;
	auto actionMoveBy = MoveBy::create(durationActual,Size(0,sizeWin.height + sizeEnemy.height));
	auto actionDone = CallFuncN::create(func);

	auto sequence = Sequence::create(actionMoveBy,actionDone,NULL);

	runAction(sequence);
}

TypeEnemy Enemy::typeGet()
{
	return _type;
}

int Enemy::hpGet()
{
	return _hp;
}