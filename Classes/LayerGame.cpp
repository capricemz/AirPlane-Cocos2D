#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "LayerGame.h"
#include "LayerBullet.h"
#include "Enemy.h"

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

		//png����ȫ��cache��
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/shoot_background.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/shoot.plist");

		//����background1��background1��background2��CCSprite*�ͳ�Ա����
		background1 = Sprite::createWithSpriteFrameName("background.png");
		background1->setAnchorPoint(Vec2(0,0));
		background1->setPosition(Vec2(0,0));
		addChild(background1);

		//����background2
		background2 = Sprite::createWithSpriteFrameName("background.png");
		background2->setAnchorPoint(Vec2(0,0));
		background2->setPosition(Vec2(0,background2->getContentSize().height - 2));//�����2��Ŀ����Ϊ�˷�ֹͼƬ����ĺ���
		addChild(background2);

		schedule(schedule_selector(LayerGame::backgroundMove),0.01f);

		scheduleUpdate();

		//����layerPlane
		layerPlane = LayerPlane::getInstance();
		addChild(layerPlane);

		//����layerBullet
		layerBullet = LayerBullet::create();
		addChild(layerBullet);
		layerBullet->shootStart();

		//����layerEnemy
		layerEnemy = LayerEnemy::create();
		addChild(layerEnemy);

		isInit = true;
	} while (0);
	return isInit;
}

void LayerGame::backgroundMove(float dt)
{
	background1->setPositionY(background1->getPositionY() - 2);
	background2->setPositionY(background1->getPositionY() + background1->getContentSize().height - 2);
	if(background2->getPositionY() <= 0)//Ҫע����Ϊ����ͼ�߶���842������ÿ�μ�ȥ2�����Ե���0�����米���߶���841����ô���������Զ�ﲻ��������ʧ��
	{
		background1->setPositionY(0);
	}
}

void LayerGame::update( float delta )
{
	Vector<Sprite *> vecBullet2Del;//����һ��Vector<Sprite *>�����Դ�Ŵ�ɾ�����ӵ���Ҳ���Ǵ�֡�б���⵽��ײ���ӵ�
	Vector<Enemy *> vecEnemy2Del;//����һ��Vector<Enemy *>�����Դ�Ŵ�ɾ���ĵл�
	for (auto bullet : layerBullet->vecBulletGet())//���������ӵ�
	{
		for (auto enemy : layerEnemy->vecEnemyGet())//�������ел�
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
					vecBullet2Del.pushBack(bullet);//�Ѵ�ɾ���ӵ�����Vector<Sprite *>
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
	for (auto bullet2Del : vecBullet2Del)//�������д�֡����ײ���ӵ�
	{
		layerBullet->bulletRemove(bullet2Del);//ִ���Ƴ�
	}
	vecBullet2Del.clear();
}

void LayerGame::eventAdd()
{
	eventListener = EventListenerTouchOneByOne::create();
	eventListener->onTouchBegan = CC_CALLBACK_2(LayerGame::onTouchBegan, this);
	eventListener->onTouchMoved = CC_CALLBACK_2(LayerGame::onTouchMoved, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventListener, this);
}

bool LayerGame::onTouchBegan( Touch *touch, Event* event )
{
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
	Director::getInstance()->getEventDispatcher()->removeEventListener(eventListener);
}