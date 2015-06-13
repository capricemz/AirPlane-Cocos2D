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

		//png加入全局cache中
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/shoot_background.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/shoot.plist");

		//加载background1，background1和background2是CCSprite*型成员变量
		background1 = Sprite::createWithSpriteFrameName("background.png");
		background1->setAnchorPoint(Vec2(0,0));
		background1->setPosition(Vec2(0,0));
		addChild(background1);

		//加载background2
		background2 = Sprite::createWithSpriteFrameName("background.png");
		background2->setAnchorPoint(Vec2(0,0));
		background2->setPosition(Vec2(0,background2->getContentSize().height - 2));//这里减2的目的是为了防止图片交界的黑线
		addChild(background2);

		schedule(schedule_selector(LayerGame::backgroundMove),0.01f);

		//加入bulletLayer
		layerBullet = LayerBullet::create();
		addChild(layerBullet);
		layerBullet->shootStart();

		//加入planeLayer
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
	Director::getInstance()->getEventDispatcher()->removeEventListener(eventListener);
}

void LayerGame::backgroundMove(float dt)
{
	background1->setPositionY(background1->getPositionY() - 2);
	background2->setPositionY(background1->getPositionY() + background1->getContentSize().height - 2);
	if(background2->getPositionY() <= 0)//要注意因为背景图高度是842，所以每次减去2最后可以到达0，假如背景高度是841，那么这个条件永远达不到，滚动失败
	{
		background1->setPositionY(0);
	}
}