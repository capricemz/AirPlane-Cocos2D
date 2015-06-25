#include "cocos2d.h"
#include "LayerPlane.h"
#include "over\SceneGameOver.h"
#include "ManagetLayer.h"

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

		//�����ɻ�����ǰҪ�ȵ���CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("shoot.plist");����ȫ����Դ
		//�Ұ��������plist�ŵ�welcome.cpp���ˡ���Ȼplane���ָ�롣
		auto plane = Sprite::createWithSpriteFrameName("hero1.png");
		auto planeSize = plane->getContentSize();
		plane->setAnchorPoint(Point(.5,.5));
		plane->setPosition(Point(winSize.width/2,planeSize.height/2));//�ɻ������ڵײ�����
		addChild(plane,0,AIRPLANE);//��Ӿ��飬AIRPLANE��tag

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
	//�ɻ�����Ϸ״̬�ж�
	if (isAlive && !Director::getInstance()->isPaused())
	{
		//���б߽��ж�,���ɳ�����Ļ
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

void LayerPlane::blowUp()
{
	if (isAlive)
	{
		isAlive = false;

		auto animation = Animation::create();
		animation->setDelayPerUnit(0.2f);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n1.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n2.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n3.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("hero_blowup_n4.png"));

		auto actionAnimate = Animate::create(animation);
		auto actionRemove4Par = CallFuncN::create(CC_CALLBACK_0(LayerPlane::remove4Par, this));
		auto sequence = Sequence::create(actionAnimate, actionRemove4Par, nullptr);
		auto plane = getChildByTag(AIRPLANE);
		plane->stopAllActions();
		plane->runAction(sequence);
	}
}

void LayerPlane::remove4Par()
{
	removeChildByTag(AIRPLANE, true);
	auto scene = SceneGameOver::create();
	auto scoreOver = ManagetLayer::getInstance()->layerUIGet()->scoreGet();
	scene->scoreOverSet(scoreOver);
	auto animateScene = TransitionMoveInT::create(0.8f, scene);
	Director::getInstance()->replaceScene(animateScene);
}
