#include "layer\LayerBullet.h"
#include "layer\LayerGame.h"

LayerBullet::LayerBullet(void)
{
}

LayerBullet::~LayerBullet(void)
{
}

bool LayerBullet::init()
{
	auto isInit = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		isInit = true;
	} while (0);
	return isInit;
}

Vector<Sprite *> LayerBullet::vecBulletGet()
{
	return _vecBullet;
}

void LayerBullet::bulletAdd(float delta)
{
	_timeNow += delta;
	if (_timeNow > _timeOverDoubleBullet)
	{
		createBulletSingle();
	}
	else
	{
		createBulletDouble();
	}
}

void LayerBullet::createBulletSingle()
{
	auto bullet = Sprite::createWithSpriteFrameName("bullet1.png");
	addChild(bullet);
	_vecBullet.pushBack(bullet);

	auto plane = LayerGame::getInstance()->layerPlaneGet()->getChildByTag(AIRPLANE);
	auto positionPlane = plane->getPosition();
	bullet->setPosition(Point(positionPlane.x,positionPlane.y + plane->getContentSize().height/2));

	Value distance(Director::getInstance()->getWinSize().height + bullet->getContentSize().height/2 - positionPlane.y);
	Value velocity(380.0f);//飞行速度：380pixel/sec
	Value duration(distance.asFloat()/velocity.asFloat());
	auto actionMoveBy = MoveBy::create(duration.asFloat(),Size(0,distance.asFloat()));
	auto actionDone = CallFuncN::create(CC_CALLBACK_1(LayerBullet::bulletRemove,this));
	auto sequence = Sequence::create(actionMoveBy,actionDone,nullptr);

	bullet->runAction(sequence);
}

void LayerBullet::createBulletDouble()
{
	auto bulletLeft = Sprite::createWithSpriteFrameName("bullet2.png");
	auto bulletRight = Sprite::createWithSpriteFrameName("bullet2.png");
	addChild(bulletLeft);
	addChild(bulletRight);
	_vecBullet.pushBack(bulletLeft);
	_vecBullet.pushBack(bulletRight);

	auto positionPlane = LayerGame::getInstance()->layerPlaneGet()->getChildByTag(AIRPLANE)->getPosition();
	bulletLeft->setPosition(Point(positionPlane.x - 33, positionPlane.y + 35));
	bulletRight->setPosition(Point(positionPlane.x + 33, positionPlane.y + 35));

	Value distance(Director::getInstance()->getWinSize().height + bulletLeft->getContentSize().height/2 - positionPlane.y);
	Value velocity(420.0f);//飞行速度：420pixel/sec
	Value duration(distance.asFloat()/velocity.asFloat());

	auto actionMoveByLeft = MoveBy::create(duration.asFloat(),Size(0,distance.asFloat()));
	auto actionDoneLeft = CallFuncN::create(CC_CALLBACK_1(LayerBullet::bulletRemove,this));
	auto sequenceLeft = Sequence::create(actionMoveByLeft,actionDoneLeft,nullptr);

	auto actionMoveByRight = MoveBy::create(duration.asFloat(),Size(0,distance.asFloat()));
	auto actionDoneRight = CallFuncN::create(CC_CALLBACK_1(LayerBullet::bulletRemove,this));
	auto sequenceRight = Sequence::create(actionMoveByRight,actionDoneRight,nullptr);

	bulletLeft->runAction(sequenceLeft);
	bulletRight->runAction(sequenceRight);
}

void LayerBullet::bulletRemove(Node *bullet)
{
	if (bullet != NULL)
	{
		auto find = _vecBullet.find((Sprite *)bullet);
		if (_vecBullet.end() != find)
		{
			_vecBullet.erase(find);
		}
		if (bullet->getParent())
		{
			removeChild(bullet,true);
		}
	}
}

void LayerBullet::shootStart()
{
	schedule(schedule_selector(LayerBullet::bulletAdd),0.2f,kRepeatForever,0.0f);
}

void LayerBullet::shootStop()
{
	unschedule(schedule_selector(LayerBullet::bulletAdd));
}

void LayerBullet::useBulletDouble()
{
	_timeOverDoubleBullet = _timeNow + 10.0f;
}