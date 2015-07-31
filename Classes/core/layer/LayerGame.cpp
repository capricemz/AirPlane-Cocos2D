#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "LayerGame.h"
#include "Enemy.h"
#include "UFO.h"
#include "ManagetLayer.h"

USING_NS_CC;

LayerGame::LayerGame(void)
{
}

LayerGame::~LayerGame(void)
{
	eventRemove();
}

bool LayerGame::init()
{
	auto isInit = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		eventAdd();

		//加载background1，background1和background2是CCSprite*型成员变量
		_background1 = Sprite::createWithSpriteFrameName("background.png");
		_background1->setAnchorPoint(Point::ZERO);
		_background1->setPosition(Point::ZERO);
		_background1->getTexture()->setAliasTexParameters();
		addChild(_background1);

		//加载background2
		_background2 = Sprite::createWithSpriteFrameName("background.png");
		_background2->setAnchorPoint(Point::ZERO);
		_background2->setPosition(Point(0,_background2->getContentSize().height - 2));//这里减2的目的是为了防止图片交界的黑线
		_background2->getTexture()->setAliasTexParameters();
		addChild(_background2);

		schedule(schedule_selector(LayerGame::backgroundMove),0.01f);

		scheduleUpdate();

		isInit = true;
	} while (0);
	return isInit;
}

void LayerGame::backgroundMove(float delta)
{
	_background1->setPositionY(_background1->getPositionY() - 2);
	_background2->setPositionY(_background1->getPositionY() + _background1->getContentSize().height - 2);
	if(_background2->getPositionY() <= 0)//要注意因为背景图高度是842，所以每次减去2最后可以到达0，假如背景高度是841，那么这个条件永远达不到，滚动失败
	{
		_background1->setPositionY(0);
	}
}

void LayerGame::update( float delta )
{
	updateCollisionBulletEnemy();
	updateCollisionUFOPlane();
	updateCollisionEnemyPlane();
}

void LayerGame::updateCollisionBulletEnemy()
{
	Vector<Sprite *> vecBullet2Del;//创建一个Vector<Sprite *>，用以存放待删除的子弹，也就是此帧中被检测到碰撞的子弹
	Vector<Enemy *> vecEnemy2Del;//创建一个Vector<Enemy *>，用以存放待删除的敌机
	Sprite *bullet;
	Enemy *enemy;
	auto layerBullet = ManagetLayer::getInstance()->layerBulletGet();
	for each (bullet in layerBullet->vecBulletGet())//遍历所有子弹
	{
		auto vecEnemy = ManagetLayer::getInstance()->layerEnemyGet()->vecEnemyGet();
		for each (enemy in vecEnemy)//遍历所有敌机
		{
			auto rectEnemy = enemy->getBoundingBox();
			auto rectBullet = bullet->getBoundingBox();
			auto isIntersects = rectEnemy.intersectsRect(rectBullet);
			if (isIntersects)
			{
				auto hpEnemy = enemy->hpGet();
				if (hpEnemy >= 1)//如果hp>=1,移除bullet
				{
					enemy->hpLose();
					if (!vecBullet2Del.contains(bullet))
					{
						vecBullet2Del.pushBack(bullet);//把待删除子弹放入Vector<Sprite *>
					}
				}
				if (hpEnemy == 1)//如果life==1,移除enemy3
				{
					vecEnemy2Del.pushBack(enemy);//把待删除敌机放入Vector<Enemy *>，也就是此子弹击中的敌机
				}
			}
		}
		for (auto enemy2Del : vecEnemy2Del)//遍历所有此帧中碰撞死亡的敌机
		{
			enemy2Del->blowup();//执行爆炸
		}
		vecEnemy2Del.clear();
	}
	for each (bullet in vecBullet2Del)//遍历所有此帧中碰撞的子弹
	{
		layerBullet->bulletRemove(bullet);//执行移除
	}
	vecBullet2Del.clear();
}

void LayerGame::updateCollisionUFOPlane()
{
	auto layerPlane = ManagetLayer::getInstance()->layerPlaneGet();
	if (!layerPlane->isAlive)
	{
		return;
	}
	Vector<UFO *> vecUFO2Del;//创建一个Vector<UFO *>，用以存放待删除的UFO，也就是此帧中被检测到碰撞的UFO
	UFO *ufo;
	auto vecUFO = ManagetLayer::getInstance()->layerUFOGet()->vecUFOGet();
	for each (ufo in vecUFO)
	{
		auto rectUFO = ufo->getBoundingBox();
		auto rectPlane = layerPlane->getChildByTag(AIRPLANE)->getBoundingBox();
		auto isIntersects = rectUFO.intersectsRect(rectPlane);
		if (isIntersects)
		{
			if (ufo->typeGet() == TypeUFO::DOUBEL_BULLET)
			{
				ManagetLayer::getInstance()->layerBulletGet()->useBulletDouble();
			}
			else if (ufo->typeGet() == TypeUFO::BOOM)
			{
				ManagetLayer::getInstance()->layerUIGet()->countBoomAdd();
			}
			vecUFO2Del.pushBack(ufo);
		}
	}
	for each ( ufo in vecUFO2Del)
	{
		ufo->pickUp();
	}
	vecUFO2Del.clear();
}

void LayerGame::updateCollisionEnemyPlane()
{
	auto layerPlane = ManagetLayer::getInstance()->layerPlaneGet();
	if (!layerPlane->isAlive)
	{
		return;
	}
	Enemy *enemy;
	auto vecEnemy = ManagetLayer::getInstance()->layerEnemyGet()->vecEnemyGet();
	for each (enemy in vecEnemy)//遍历所有敌机
	{
		if (enemy->hpGet() > 0)
		{
			auto rectEnemy = enemy->getBoundingBox();
			auto rectPlane = layerPlane->getChildByTag(AIRPLANE)->getBoundingBox();
			auto isIntersects = rectEnemy.intersectsRect(rectPlane);
			if (isIntersects)
			{
				unscheduleAllCallbacks();
				ManagetLayer::getInstance()->layerUFOGet()->addStop();
				ManagetLayer::getInstance()->layerEnemyGet()->addStop();
				ManagetLayer::getInstance()->layerBulletGet()->addStop();
				ManagetLayer::getInstance()->layerPlaneGet()->blowUp();
			}
		}
	}
}

void LayerGame::eventAdd()
{
	_eventListener = EventListenerTouchOneByOne::create();
	_eventListener->onTouchBegan = CC_CALLBACK_2(LayerGame::onTouchBegan, this);
	_eventListener->onTouchMoved = CC_CALLBACK_2(LayerGame::onTouchMoved, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(_eventListener, this);
}

bool LayerGame::onTouchBegan( Touch *touch, Event* event )
{
	auto layerPlane = ManagetLayer::getInstance()->layerPlaneGet();
	if(layerPlane->isAlive)//isAlive是AirPlane的一个成员属性，表示飞机是否还活着
	{
		//juggle the area of drag
		auto rectPlane = layerPlane->getChildByTag(AIRPLANE)->getBoundingBox();
		rectPlane.origin.x -= 15;
		rectPlane.origin.y -= 15;
		rectPlane.size.width += 30;
		rectPlane.size.height += 30;//允许稍微加大一点触摸位置，游戏实际需要
		if (rectPlane.containsPoint(getParent()->convertTouchToNodeSpace(touch))) //判断触摸点是否在飞机范围内
		{
			return true;//表示当前层接收触摸事件处理
		}
	}
	return false;
}

void LayerGame::onTouchMoved( Touch *touch, Event *event )
{
	auto layerPlane = ManagetLayer::getInstance()->layerPlaneGet();
	if(layerPlane->isAlive)//isAlive是AirPlane的一个成员属性，表示飞机是否还活着
	{
		auto pointBegin = touch->getLocationInView();
		pointBegin = Director::getInstance()->convertToGL(pointBegin);//获取触摸坐标

		auto pointEnd = touch->getPreviousLocationInView();//获取触摸的前一个位置
		pointEnd = Director::getInstance()->convertToGL(pointEnd);

		auto offset = pointBegin - pointEnd;//获取offset
		auto pointTo = layerPlane->getChildByTag(AIRPLANE)->getPosition() + offset;//获取真正移动位置

		layerPlane->moveTo(pointTo);//移动飞机
	}
}

void LayerGame::eventRemove()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(_eventListener);
}