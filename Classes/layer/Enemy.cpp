#include "layer\Enemy.h"
#include "util\UtilRandom.h"

using namespace std;

Enemy::Enemy(void)
{
}

Enemy::~Enemy(void)
{
}

Enemy *Enemy::create( TypeEnemy value, CallFuncN *actionRemove4Vec)
{
	Enemy *enemy = new Enemy(); 
	if (enemy && enemy->init(value, actionRemove4Vec)) 
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

bool Enemy::init(TypeEnemy value, CallFuncN *actionRemove4Vec)
{
	auto isInit = false;
	do 
	{
		_type = value;
		_actionRemove4Vec = actionRemove4Vec;
		string spriteFrameName;
		switch (value)
		{
		case TypeEnemy::SMALL:
			spriteFrameName = "enemy1.png";
			_hp = 1;
			_duration = 2.0f;
			break;
		case TypeEnemy::MEDIUM:
			spriteFrameName = "enemy2.png";
			_hp = 3;
			_duration = 3.0f;
			break;
		case TypeEnemy::LARGE:
			spriteFrameName = "enemy3_n1.png";
			_hp = 10;
			_duration = 4.0f;
			break;
		default:
			spriteFrameName = "enemy1.png";
			_hp = 1;
			_duration = 2.0f;
			break;
		}
		CC_BREAK_IF(!initWithSpriteFrameName(spriteFrameName));
		
		auto sizeEnemy = getContentSize();
		auto sizeWin = Director::getInstance()->getWinSize();
		auto xActual = UtilRandom::randomBewteen(sizeEnemy.width/2,sizeWin.width - sizeEnemy.width/2);//Ëæ»ú³õÊ¼Î»ÖÃ
		setAnchorPoint(Point(0.5f,0.5f));
		setPosition(xActual,sizeWin.height + sizeEnemy.height/2);

		auto actionMoveBy = MoveBy::create(_duration,Size(0,-(sizeWin.height + sizeEnemy.height)));
		auto actionRemove4Par = CallFunc::create(CC_CALLBACK_0(Enemy::remove4Par,this));

		auto sequence = Sequence::create(actionMoveBy,_actionRemove4Vec,actionRemove4Par,NULL);

		runAction(sequence);

		if (_type == TypeEnemy::LARGE)
		{
			auto animation = Animation::create();
			animation->setDelayPerUnit(0.2f);
			auto spriteFrame1 = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n1.png");
			animation->addSpriteFrame(spriteFrame1);
			auto spriteFrame2 = SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_n2.png");
			animation->addSpriteFrame(spriteFrame2);

			auto animate = Animate::create(animation);
			runAction(RepeatForever::create(animate));
		}
		isInit = true;
	} while (0);
	return isInit;
}

TypeEnemy Enemy::typeGet()
{
	return _type;
}

const int Enemy::hpGet()
{
	return _hp;
}

void Enemy::hpLose()
{
	_hp--;
}

void Enemy::blowup()
{
	auto animation = Animation::create();
	switch (_type)
	{
	case TypeEnemy::SMALL:
		animation->setDelayPerUnit(0.1f);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down1.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down2.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down3.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down4.png"));
		break;
	case TypeEnemy::MEDIUM:
		animation->setDelayPerUnit(0.1f);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down1.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down2.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down3.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy2_down4.png"));
		break;
	case TypeEnemy::LARGE:
		animation->setDelayPerUnit(0.1f);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down1.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down2.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down3.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down4.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down5.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy3_down6.png"));
		break;
	default:
		animation->setDelayPerUnit(0.1f);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down1.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down2.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down3.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("enemy1_down4.png"));
		break;
	}

	auto animate = Animate::create(animation);
	auto actionRemove4Par = CallFunc::create(CC_CALLBACK_0(Enemy::remove4Par,this));
	auto sequence = Sequence::create(_actionRemove4Vec,animate,actionRemove4Par,nullptr);
	runAction(sequence);
}

void Enemy::remove4Par()
{
	auto parent = getParent();
	if (parent)
	{
		parent->removeChild(this,true);
	}
}