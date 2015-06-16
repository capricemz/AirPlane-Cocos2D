#include "TestSpriteBtachNode.h"
#include "util\UtilRandom.h"


TestSpriteBtachNode::TestSpriteBtachNode(void)
{
}


TestSpriteBtachNode::~TestSpriteBtachNode(void)
{
}

void TestSpriteBtachNode::normal()
{
	for(int i = 0;i < 1000;++i)
	{
		int x = UtilRandom::randomBewteen(0,480);
		int y = UtilRandom::randomBewteen(0,582);
		auto testIcon = Sprite::create("icon.png");
		testIcon->setPosition(Point::ZERO);
		this->addChild(testIcon);
	}
}

void TestSpriteBtachNode::btach()
{
	auto batchNode = SpriteBatchNode::create("icon.png",1000);

	batchNode->setPosition(Vec2(0,0));
	this->addChild(batchNode);

	for(int i = 0;i < 1000;++i){
		int x = UtilRandom::randomBewteen(0,480);
		int y = UtilRandom::randomBewteen(0,582);
		auto testIcon = Sprite::createWithTexture(batchNode->getTexture());
		testIcon->setPosition(Vec2(x,y));
		batchNode->addChild(testIcon);
	}
}

bool TestSpriteBtachNode::init()
{
	auto isInit = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());
		//normal();
		btach();
		isInit = true;
	} while (0);
	return isInit;
}
