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

		//����background1��background1��background2��CCSprite*�ͳ�Ա����
		_background1 = Sprite::createWithSpriteFrameName("background.png");
		_background1->setAnchorPoint(Vec2(0,0));
		_background1->setPosition(Vec2(0,0));
		addChild(_background1);

		//����background2
		_background2 = Sprite::createWithSpriteFrameName("background.png");
		_background2->setAnchorPoint(Vec2(0,0));
		_background2->setPosition(Vec2(0,_background2->getContentSize().height - 2));//�����2��Ŀ����Ϊ�˷�ֹͼƬ����ĺ���
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
	if(_background2->getPositionY() <= 0)//Ҫע����Ϊ����ͼ�߶���842������ÿ�μ�ȥ2�����Ե���0�����米���߶���841����ô���������Զ�ﲻ��������ʧ��
	{
		_background1->setPositionY(0);
	}
}

void LayerGame::update( float delta )
{
	updateCollisionBulletEnemy();
	updateCollisionUFOPlane();
}

void LayerGame::updateCollisionBulletEnemy()
{
	Vector<Sprite *> vecBullet2Del;//����һ��Vector<Sprite *>�����Դ�Ŵ�ɾ�����ӵ���Ҳ���Ǵ�֡�б���⵽��ײ���ӵ�
	Vector<Enemy *> vecEnemy2Del;//����һ��Vector<Enemy *>�����Դ�Ŵ�ɾ���ĵл�
	Sprite *bullet;
	Enemy *enemy;
	auto layerBullet = ManagetLayer::getInstance()->layerBulletGet();
	for each (bullet in layerBullet->vecBulletGet())//���������ӵ�
	{
		auto vecEnemy = ManagetLayer::getInstance()->layerEnemyGet()->vecEnemyGet();
		for each (enemy in vecEnemy)//�������ел�
		{
			auto rectEnemy = enemy->getBoundingBox();
			auto rectBullet = bullet->getBoundingBox();
			auto isIntersects = rectEnemy.intersectsRect(rectBullet);
			if (isIntersects)
			{
				auto hpEnemy = enemy->hpGet();
				if (hpEnemy >= 1)//���hp>=1,�Ƴ�bullet
				{
					enemy->hpLose();
					if (!vecBullet2Del.contains(bullet))
					{
						vecBullet2Del.pushBack(bullet);//�Ѵ�ɾ���ӵ�����Vector<Sprite *>
					}
				}
				if (hpEnemy == 1)//���life==1,�Ƴ�enemy3
				{
					vecEnemy2Del.pushBack(enemy);//�Ѵ�ɾ���л�����Vector<Enemy *>��Ҳ���Ǵ��ӵ����еĵл�
				}
			}
		}
		for (auto enemy2Del : vecEnemy2Del)//�������д�֡����ײ�����ĵл�
		{
			enemy2Del->blowup();//ִ�б�ը
		}
		vecEnemy2Del.clear();
	}
	for each (bullet in vecBullet2Del)//�������д�֡����ײ���ӵ�
	{
		layerBullet->bulletRemove(bullet);//ִ���Ƴ�
	}
	vecBullet2Del.clear();
}

void LayerGame::updateCollisionUFOPlane()
{
	Vector<UFO *> vecUFO2Del;//����һ��Vector<UFO *>�����Դ�Ŵ�ɾ����UFO��Ҳ���Ǵ�֡�б���⵽��ײ��UFO
	UFO *ufo;
	auto vecUFO = ManagetLayer::getInstance()->layerUFOGet()->vecUFOGet();
	for each (ufo in vecUFO)
	{
		auto rectUFO = ufo->getBoundingBox();
		auto rectPlane = ManagetLayer::getInstance()->layerPlaneGet()->getChildByTag(AIRPLANE)->getBoundingBox();
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
	if(layerPlane->isAlive)//isAlive��AirPlane��һ����Ա���ԣ���ʾ�ɻ��Ƿ񻹻���
	{
		//juggle the area of drag
		auto rectPlane = layerPlane->getChildByTag(AIRPLANE)->getBoundingBox();
		rectPlane.origin.x -= 15;
		rectPlane.origin.y -= 15;
		rectPlane.size.width += 30;
		rectPlane.size.height += 30;//������΢�Ӵ�һ�㴥��λ�ã���Ϸʵ����Ҫ
		if (rectPlane.containsPoint(getParent()->convertTouchToNodeSpace(touch))) //�жϴ������Ƿ��ڷɻ���Χ��
		{
			return true;//��ʾ��ǰ����մ����¼�����
		}
	}
	return false;
}

void LayerGame::onTouchMoved( Touch *touch, Event *event )
{
	auto layerPlane = ManagetLayer::getInstance()->layerPlaneGet();
	if(layerPlane->isAlive)//isAlive��AirPlane��һ����Ա���ԣ���ʾ�ɻ��Ƿ񻹻���
	{
		auto pointBegin = touch->getLocationInView();
		pointBegin = Director::getInstance()->convertToGL(pointBegin);//��ȡ��������

		auto pointEnd = touch->getPreviousLocationInView();//��ȡ������ǰһ��λ��
		pointEnd = Director::getInstance()->convertToGL(pointEnd);

		auto offset = pointBegin - pointEnd;//��ȡoffset
		auto pointTo = layerPlane->getChildByTag(AIRPLANE)->getPosition() + offset;//��ȡ�����ƶ�λ��

		layerPlane->moveTo(pointTo);//�ƶ��ɻ�
	}
}

void LayerGame::eventRemove()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(_eventListener);
}