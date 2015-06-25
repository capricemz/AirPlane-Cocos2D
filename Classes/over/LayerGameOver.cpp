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
		//��ӱ���
		auto spriteBackground = Sprite::createWithSpriteFrameName("gameover.png");
		spriteBackground->setPosition(sizeWin.width/2, sizeWin.height/2);
		addChild(spriteBackground);
		//��ӷ��ذ�ť
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
	//��ӽ������
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
	//�����ʷ����
	auto _scoreHighest = scoreHighestGet();
	Value scoreHighest(_scoreHighest);
	auto labelScoreHighest = Label::createWithBMFont("font/font.fnt",scoreHighest.asString());
	labelScoreHighest->setColor(Color3B(143, 146, 147));
	labelScoreHighest->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
	labelScoreHighest->setPosition(140, sizeWin.height - 30);
	addChild(labelScoreHighest);

	if (_scoreOver > _scoreHighest)//�����ǰ�����Ƽ�¼�����Ͻ���ʷ��߷�Ҫ���и���
	{
		UserDefault::getInstance()->setIntegerForKey("scoreHighest",_scoreOver);//�޸Ĵ浵
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

bool LayerGameOver::isSaveFileExist()//�жϴ浵�Ƿ����
{
	auto userDefault = UserDefault::getInstance();
	if (!userDefault->getBoolForKey("isSaveFileExist"))//ͨ�����õ�bool�ͱ�־λ�жϣ����������
	{
		userDefault->setBoolForKey("isSaveFileExist",true);//д��bool�ж�λ
		userDefault->setIntegerForKey("scoreHighest", 0);//д���ʼ����0
		userDefault->flush();//������һ��Ҫ����flush�����ܴӻ���д��io
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