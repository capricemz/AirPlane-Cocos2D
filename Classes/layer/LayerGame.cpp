#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "layer/LayerGame.h"

USING_NS_CC;

LayerGame* LayerGame::_instance = nullptr;//��̬��Ա�����Ķ���
LayerGame::CGarbo LayerGame::_garbo;//��Ƕ�ྲ̬��Ա�����Ķ���

LayerGame::LayerGame(void)
{
	_layerBullet = nullptr;
	_layerEnemy = nullptr;
	_layerPlane = nullptr;
	_layerUFO = nullptr;
	_layerUI = nullptr;
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

		//png����ȫ��cache��
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/shoot_background.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/shoot.plist");

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

		//����layerPlane
		_layerPlane = LayerPlane::create();
		addChild(_layerPlane);

		//����layerBullet
		_layerBullet = LayerBullet::create();
		addChild(_layerBullet);
		_layerBullet->shootStart();

		//����layerEnemy
		_layerEnemy = LayerEnemy::create();
		addChild(_layerEnemy);

		//����layerUFO
		_layerUFO = LayerUFO::create();
		addChild(_layerUFO);

		//����layerUI
		_layerUI = LayerUI::create();
		addChild(_layerUI);

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
	for each (bullet in _layerBullet->vecBulletGet())//���������ӵ�
	{
		for each (enemy in _layerEnemy->vecEnemyGet())//�������ел�
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
		_layerBullet->bulletRemove(bullet);//ִ���Ƴ�
	}
	vecBullet2Del.clear();
}

void LayerGame::updateCollisionUFOPlane()
{
	Vector<UFO *> vecUFO2Del;//����һ��Vector<UFO *>�����Դ�Ŵ�ɾ����UFO��Ҳ���Ǵ�֡�б���⵽��ײ��UFO
	UFO *ufo;
	for each (ufo in _layerUFO->vecUFOGet())
	{
		auto rectUFO = ufo->getBoundingBox();
		auto rectPlane = _layerPlane->getChildByTag(AIRPLANE)->getBoundingBox();
		auto isIntersects = rectUFO.intersectsRect(rectPlane);
		if (isIntersects)
		{
			if (ufo->typeGet() == TypeUFO::DOUBEL_BULLET)
			{
				_layerBullet->useBulletDouble();
			}
			else if (ufo->typeGet() == TypeUFO::BOOM)
			{
				_layerUI->countBoomAdd();
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
	if(_layerPlane->isAlive)//isAlive��AirPlane��һ����Ա���ԣ���ʾ�ɻ��Ƿ񻹻���
	{
		//juggle the area of drag
		auto rectPlane = _layerPlane->getChildByTag(AIRPLANE)->getBoundingBox();
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
	if(_layerPlane->isAlive)//isAlive��AirPlane��һ����Ա���ԣ���ʾ�ɻ��Ƿ񻹻���
	{
		auto pointBegin = touch->getLocationInView();
		pointBegin = Director::getInstance()->convertToGL(pointBegin);//��ȡ��������

		auto pointEnd = touch->getPreviousLocationInView();//��ȡ������ǰһ��λ��
		pointEnd = Director::getInstance()->convertToGL(pointEnd);

		auto offset = pointBegin - pointEnd;//��ȡoffset
		auto pointTo = _layerPlane->getChildByTag(AIRPLANE)->getPosition() + offset;//��ȡ�����ƶ�λ��

		_layerPlane->moveTo(pointTo);//�ƶ��ɻ�
	}
}

void LayerGame::eventRemove()
{
	Director::getInstance()->getEventDispatcher()->removeEventListener(_eventListener);
}

LayerPlane * LayerGame::layerPlaneGet()
{
	return _layerPlane;
}

LayerEnemy * LayerGame::layerEnemyGet()
{
	return _layerEnemy;
}
