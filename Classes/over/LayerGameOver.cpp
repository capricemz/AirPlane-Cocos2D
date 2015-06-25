#include "LayerGameOver.h"
#include "core\SceneGame.h"

LayerGameOver::LayerGameOver(void)
{
	_scoreOver = 0;
}

LayerGameOver::~LayerGameOver(void)
{
}

bool LayerGameOver::init()
{
	auto isInit = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());

		auto sizeWin = Director::getInstance()->getWinSize();
		//添加背景
		auto spriteBackground = Sprite::createWithSpriteFrameName("gameover.png");
		spriteBackground->setPosition(sizeWin.width/2, sizeWin.height/2);
		addChild(spriteBackground);
		//添加返回按钮
		auto spriteBackNormal = Sprite::createWithSpriteFrameName("btn_finish.png");
		auto spriteBackPressed = Sprite::createWithSpriteFrameName("btn_finish.png");

		auto menuItemSprite = MenuItemSprite::create(spriteBackNormal, spriteBackPressed, nullptr, CC_CALLBACK_0(LayerGameOver::menuCallBackBack,this));
		menuItemSprite->setPosition(sizeWin.width - spriteBackNormal->getContentSize().width/2 - 10, spriteBackNormal->getContentSize().height/2 + 10);

		auto menu = Menu::create(menuItemSprite, nullptr);
		menu->setPosition(Point::ZERO);
		addChild(menu);

		isInit = true;
	} while (0);
	return isInit;
}

void LayerGameOver::menuCallBackBack()
{
	auto scene = SceneGame::create();
	auto animateScene = TransitionMoveInL::create(1.0f, scene);
	Director::getInstance()->replaceScene(animateScene);
}

void LayerGameOver::showAD()
{

}

void LayerGameOver::scoreOverSet( int score )
{
	_scoreOver = score;
	//添加结果分数
	Value scoreOver(_scoreOver);
	auto labelScoreOver = Label::createWithBMFont("font/font.fnt", scoreOver.asString());
	labelScoreOver->setColor(Color3B(143, 146, 147));
	auto sizeWin = Director::getInstance()->getWinSize();
	labelScoreOver->setPosition(sizeWin.width/2, sizeWin.height/2);
	addChild(labelScoreOver);

	auto actionDelay = DelayTime::create(1.0f);
	auto actionScaleBig = ScaleTo::create(1.0f, 3.0f);
	auto actionScaleSmall = ScaleTo::create(0.3f, 2.0f);
	auto actionShowAD = CallFunc::create(CC_CALLBACK_0(LayerGameOver::showAD, this));
	auto sequence = Sequence::create(actionDelay, actionScaleBig, actionScaleSmall, actionShowAD, nullptr);
	labelScoreOver->runAction(sequence);
	//添加历史分数
	auto _scoreHighest = scoreHighestGet();
	Value scoreHighest(_scoreHighest);
	auto labelScoreHighest = Label::createWithBMFont("font/font.fnt",scoreHighest.asString());
	labelScoreHighest->setColor(Color3B(143, 146, 147));
	labelScoreHighest->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	labelScoreHighest->setPosition(140, sizeWin.height - 30);
	addChild(labelScoreHighest);

	if (_scoreOver > _scoreHighest)//如果当前分数破纪录，左上角历史最高分要进行更新
	{
		UserDefault::getInstance()->setIntegerForKey("scoreHighest",_scoreOver);//修改存档
		auto actionDelay = DelayTime::create(1.3f);
		auto actionMoveOut = MoveBy::create(0.1f, Point(0, 100));
		auto actionLabelScoreHighestSet = CallFuncN::create(CC_CALLBACK_1(LayerGameOver::labelScoreHighestSet,this));
		auto actionMoveIn = MoveBy::create(0.1f, Point(0, -100));
		auto sequence = Sequence::create(actionDelay, actionMoveOut, actionLabelScoreHighestSet, actionMoveIn, nullptr);
		labelScoreHighest->runAction(sequence);
	}
}

int LayerGameOver::scoreHighestGet()
{
	auto score = 0;
	if (isSaveFileExist())
	{
		score = UserDefault::getInstance()->getIntegerForKey("scoreHighest");
		return score;
	}
	return score;
}

bool LayerGameOver::isSaveFileExist()//判断存档是否存在
{
	auto userDefault = UserDefault::getInstance();
	if (!userDefault->getBoolForKey("isSaveFileExist"))//通过设置的bool型标志位判断，如果不存在
	{
		userDefault->setBoolForKey("isSaveFileExist",true);//写入bool判断位
		userDefault->setIntegerForKey("scoreHighest", 0);//写入初始分数0
		userDefault->flush();//设置完一定要调用flush，才能从缓冲写入io
		return false;
	}
	else
	{
		return true;
	}
}

void LayerGameOver::labelScoreHighestSet(Node *node)
{
	Value scoreOver(_scoreOver);
	auto labelScoreHighest = (Label *)node;
	labelScoreHighest->setString(scoreOver.asString());
}