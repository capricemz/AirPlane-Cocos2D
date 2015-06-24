#include "layer/LayerUI.h"
#include "layer/LayerGame.h"
#include "layer/ManagetLayer.h"

using namespace std;

LayerUI::LayerUI(void)
{
	_countBoom = 0;
	_score = 0;
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

		isInit = true;
	} while (0);
	return isInit;
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
		stringstream countBoom;
		countBoom << _countBoom;
		string text = "X" + countBoom.str();
		auto labelCountBoom = (Label *)getChildByTag(TAG_LABEL_COUNT_BOOM);
		labelCountBoom->setString(text);
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
		/*LayerGame::getInstance()->layerEnemyGet()->enemyBlowupAll();*/
		ManagetLayer::getInstance()->layerEnemyGet()->enemyBlowupAll();
	}
}