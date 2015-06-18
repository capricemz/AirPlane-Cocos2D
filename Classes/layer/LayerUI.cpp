#include "layer\LayerUI.h"
#include "layer\LayerGame.h"


LayerUI::LayerUI(void)
{
	_menuBoom = nullptr;
	_labelCountBoom = nullptr;

	_countBoom = 0;
	_score = 0;
}


LayerUI::~LayerUI(void)
{
	_menuBoom = nullptr;
	_labelCountBoom = nullptr;
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
	auto boomNormal = Sprite::createWithSpriteFrameName("bomb.png");
	auto boomPressed = Sprite::createWithSpriteFrameName("bomb.png");
	if (_countBoom > 0)
	{
		if (!_menuBoom)
		{
			auto menuItemSpriteBoom = MenuItemSprite::create(boomNormal,boomPressed,nullptr,CC_CALLBACK_0(LayerUI::menuCallBackBoom,this));
			menuItemSpriteBoom->setPosition(Point(boomNormal->getContentSize().width/2 + 10, boomNormal->getContentSize().height/2 + 10));
			_menuBoom = Menu::create(menuItemSpriteBoom,nullptr);
			_menuBoom->setPosition(Point::ZERO);
		}
		if (!_menuBoom->getParent())
		{
			addChild(_menuBoom);
		}
		if (!_labelCountBoom)
		{
			_labelCountBoom = Label::createWithBMFont("font/font.fnt","");
			_labelCountBoom->setColor(Color3B(143, 146, 147));
			_labelCountBoom->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
			_labelCountBoom->setPosition(Point(boomNormal->getContentSize().width + 15, boomNormal->getContentSize().height/2 + 5));
		}
		if (!_labelCountBoom->getParent())
		{
			addChild(_labelCountBoom);
		}
		auto text = __String::createWithFormat("x%d",_countBoom);
		_labelCountBoom->setString(text->getCString());
	}
	else
	{
		if (_menuBoom->getParent())
		{
			removeChild(_menuBoom,true);
			_menuBoom = nullptr;
		}
		if (_labelCountBoom->getParent())
		{
			removeChild(_labelCountBoom,true);
			_labelCountBoom = nullptr;
		}
	}
}

void LayerUI::menuCallBackBoom()
{
	if (_countBoom > 0 && !Director::getInstance()->isPaused())//Õ¨µ¯Êý´óÓÚ0£¬ÇÒÓÎÏ·Î´ÔÝÍ£
	{
		_countBoom--;//Õ¨µ¯Êý-1
		updateBoomCount();
		LayerGame::getInstance()->layerEnemyGet()->enemyBlowupAll();
	}
}