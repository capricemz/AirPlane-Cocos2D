#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "LayerGame.h"
#include "LayerBullet.h"

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

		//����bulletLayer
		layerBullet = LayerBullet::create();
		addChild(layerBullet);
		layerBullet->shootStart();

		//����planeLayer
		layerPlane = LayerPlane::getInstance();
		addChild(layerPlane);

		isInit = true;
	} while (0);
	return isInit;
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

void LayerGame::backgroundMove(float dt)
{
	background1->setPositionY(background1->getPositionY() - 2);
	background2->setPositionY(background1->getPositionY() + background1->getContentSize().height - 2);
	if(background2->getPositionY() <= 0)//Ҫע����Ϊ����ͼ�߶���842������ÿ�μ�ȥ2�����Ե���0�����米���߶���841����ô���������Զ�ﲻ��������ʧ��
	{
		background1->setPositionY(0);
	}
}