#include "layer/LayerUI.h"
#include "layer/LayerGame.h"
#include "layer/ManagetLayer.h"

using namespace std;

LayerUI::LayerUI(void)
{
}


LayerUI::~LayerUI(void)
{
}

bool LayerUI::init()
{
	auto isInit = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());
		_score = 0;
		_countBoom = 0;

		auto sizeWin = Director::getInstance()->getWinSize();
		
		auto pauseNormal = Sprite::createWithSpriteFrameName("game_pause_nor.png");
		auto pausePressed = Sprite::createWithSpriteFrameName("game_pause_pressed.png");
		_menuItemSpritePause = MenuItemSprite::create(pauseNormal,pausePressed,CC_CALLBACK_0(LayerUI::menuCallbackPause,this));
		_menuItemSpritePause->setPosition(Point(pauseNormal->getContentSize().width/2, pauseNormal->getContentSize().height/2));
		_menuItemSpritePause->setContentSize(Size(pauseNormal->getContentSize().width, pauseNormal->getContentSize().height));
		auto menuPause = Menu::create(_menuItemSpritePause, nullptr);
		menuPause->setContentSize(_menuItemSpritePause->getContentSize());
		menuPause->setPosition(Point(0, sizeWin.height - menuPause->getContentSize().height));
		addChild(menuPause);

		_labelScore = Label::createWithBMFont("font/font.fnt", "0");
		_labelScore->setColor(Color3B(143, 146, 147));
		_labelScore->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
		_labelScore->setPosition(Point(_menuItemSpritePause->getPositionX() + pauseNormal->getContentSize().width/2 + 5, menuPause->getPositionY() + menuPause->getContentSize().height/2));
		addChild(_labelScore);

		isInit = true;
	} while (0);
	return isInit;
}

void LayerUI::menuCallbackPause()
{
	if (!Director::getInstance()->isPaused())
	{
		_menuItemSpritePause->setNormalImage(Sprite::createWithSpriteFrameName("game_resume_nor.png"));
		_menuItemSpritePause->setSelectedImage(Sprite::createWithSpriteFrameName("game_resume_pressed.png"));
		Director::getInstance()->pause();
	}
	else
	{
		_menuItemSpritePause->setNormalImage(Sprite::createWithSpriteFrameName("game_pause_nor.png"));
		_menuItemSpritePause->setSelectedImage(Sprite::createWithSpriteFrameName("game_pause_pressed.png"));
		Director::getInstance()->resume();
	}
}

void LayerUI::updateScore(int score)
{
	if (score > 0)
	{
		_score += score;
		Value strScore(_score);
		_labelScore->setString(strScore.asString());
	} 
}

void LayerUI::countBoomAdd()
{
	_countBoom++;
	updateBoomCount();
}

void LayerUI::updateBoomCount()
{
	if (_countBoom > 0)
	{
		if (!getChildByTag(TAG_MENU_BOOM))
		{
			auto boomNormal = Sprite::createWithSpriteFrameName("bomb.png");
			auto boomPressed = Sprite::createWithSpriteFrameName("bomb.png");
			auto menuItemSpriteBoom = MenuItemSprite::create(boomNormal,boomPressed,nullptr,CC_CALLBACK_0(LayerUI::menuCallBackBoom,this));
			menuItemSpriteBoom->setPosition(Point(boomNormal->getContentSize().width/2 + 10, boomNormal->getContentSize().height/2 + 10));
			auto menuBoom = Menu::create(menuItemSpriteBoom,nullptr);
			menuBoom->setPosition(Point::ZERO);
			addChild(menuBoom, 0, TAG_MENU_BOOM);
		}
		if (!getChildByTag(TAG_LABEL_COUNT_BOOM))
		{
			auto boomNormal = Sprite::createWithSpriteFrameName("bomb.png");
			auto labelCountBoom = Label::createWithBMFont("font/font.fnt","");
			labelCountBoom->setColor(Color3B(143, 146, 147));
			labelCountBoom->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
			labelCountBoom->setPosition(Point(boomNormal->getContentSize().width + 15, boomNormal->getContentSize().height/2 + 5));
			addChild(labelCountBoom, 0, TAG_LABEL_COUNT_BOOM);
		}
		Value strCountBoom(_countBoom);
		auto labelCountBoom = (Label *)getChildByTag(TAG_LABEL_COUNT_BOOM);
		labelCountBoom->setString("X" + strCountBoom.asString());
	}
	else
	{
		if (getChildByTag(TAG_MENU_BOOM))
		{
			removeChildByTag(TAG_MENU_BOOM,true);
		}
		if (getChildByTag(TAG_LABEL_COUNT_BOOM))
		{
			removeChildByTag(TAG_LABEL_COUNT_BOOM,true);
		}
	}
}

void LayerUI::menuCallBackBoom()
{
	if (_countBoom > 0 && !Director::getInstance()->isPaused())//Õ¨µ¯Êý´óÓÚ0£¬ÇÒÓÎÏ·Î´ÔÝÍ£
	{
		_countBoom--;//Õ¨µ¯Êý-1
		updateBoomCount();
		ManagetLayer::getInstance()->layerEnemyGet()->enemyBlowupAll();
	}
}