#include "welcome/LayerWelcome.h"
#include "core/SceneGame.h"

LayerWelcome::LayerWelcome()
{
}

LayerWelcome::~LayerWelcome()
{
}

bool LayerWelcome::init()
{
	auto isInit = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());
		//png加入全局cache中
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/shoot_background.plist");
		SpriteFrameCache::getInstance()->addSpriteFramesWithFile("ui/shoot.plist");

		auto sizeWin = Director::getInstance()->getWinSize();
		//加入背景
		auto spriteBackground = Sprite::createWithSpriteFrameName("background.png");
		spriteBackground->setPosition(sizeWin.width/2, sizeWin.height/2);
		addChild(spriteBackground);
		//加入copyright
		auto spriteCopyright = Sprite::createWithSpriteFrameName("shoot_copyright.png");
		spriteCopyright->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
		spriteCopyright->setPosition(sizeWin.width/2, sizeWin.height/2);
		addChild(spriteCopyright);
		//加入loading
		auto spriteLoading = Sprite::createWithSpriteFrameName("game_loading1.png");
		spriteLoading->setPosition(sizeWin.width/2, sizeWin.height/2 - 40);
		addChild(spriteLoading);

		auto animation = Animation::create();
		animation->setDelayPerUnit(0.25f);
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading1.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading2.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading3.png"));
		animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("game_loading4.png"));
		auto animate = Animate::create(animation);
		auto actionLoading = Repeat::create(animate, 3);

		auto actionLoadingOver = CallFunc::create(CC_CALLBACK_0(LayerWelcome::loadingOver,this));
		
		auto sequence = Sequence::create(actionLoading, actionLoadingOver, nullptr);

		spriteLoading->runAction(sequence);

		isInit = true;
	} while (0);
	return isInit;
}

void LayerWelcome::loadingOver()
{
	auto scene = SceneGame::create();
	auto animateScene = TransitionMoveInB::create(0.5f, scene);
	Director::getInstance()->replaceScene(animateScene);
}
