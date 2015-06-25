#include "cocos2d.h"
#include "LayerPlane.h"

USING_NS_CC;

LayerPlane::LayerPlane(void)
{
	isAlive = true;
}

LayerPlane::~LayerPlane(void)
{
}

bool LayerPlane::init()
{
	auto isInit = false;
	do
	{
		CC_BREAK_IF(!Layer::init());

		auto winSize = Director::getInstance()->getWinSize();

		//创建飞机精灵前要先调用CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shoot.plist");加载全局资源
		//我把这个调用plist放到welcome.cpp中了。不然plane会空指针。
		auto plane = Sprite::createWithSpriteFrameName("hero1.png");
		auto planeSize = plane->getContentSize();
		plane->setAnchorPoint(Point(.5,.5));
		plane->setPosition(Point(winSize.width/2,planeSize.height/2));//飞机放置在底部中央
		addChild(plane,0,AIRPLANE);//添加精灵，AIRPLANE是tag

		auto blink = Blink::create(1,3);

		auto animation = Animation::create();
		animation->setDelayPerUnit(0.1f);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero1.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero2.png"));
		auto animate = Animate::create(animation);

		plane->runAction(blink);
		plane->runAction(RepeatForever::create(animate));

		isInit = true;
	} while (0);
	return isInit;
}

void LayerPlane::moveTo( Point location )
{
	//飞机及游戏状态判断
	if (isAlive && !Director::getInstance()->isPaused())
	{
		//进行边界判断,不可超出屏幕
		auto sizeWin = Director::getInstance()->getWinSize();
		auto plane = getChildByTag(AIRPLANE);
		auto sizePlane = plane->getContentSize();
		if (location.x < sizePlane.width*0.15f)
		{
			location.x = sizePlane.width*0.15f;
		}
		else if (location.x > sizeWin.width - sizePlane.width*0.15f)
		{
			location.x = sizeWin.width - sizePlane.width*0.15f;
		}
		else if (location.y < sizePlane.height/2)
		{
			location.y = sizePlane.height/2;
		}
		else if (location.y > sizeWin.height - sizePlane.height/2)
		{
			location.y = sizeWin.height - sizePlane.height/2;
		}
		plane->setPosition(location);
	}
}
