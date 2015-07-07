#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "tests/TestFileUtils.h"

USING_NS_CC;

using namespace cocostudio::timeline;

Scene *HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    auto rootNode = CSLoader::createNode("MainScene.csb");

    addChild(rootNode);

	auto layer = LayerColor::create(Color4B(0, 128, 128, 255));
	layer->setContentSize(Size(120, 80));
	layer->setPosition(Point(50, 50));
	addChild(layer, 10);
	auto layer1 = LayerColor::create(Color4B(128, 0, 128, 255));
	layer1->setContentSize(Size(120, 80));
	layer1->setPosition(Point(100, 80));
	addChild(layer1, 20);
	auto layer2 = LayerColor::create(Color4B(128, 128, 0, 255));
	layer2->setContentSize(Size(120, 80));
	layer2->setPosition(Point(150, 110));
	addChild(layer2, 30);

	//scheduleUpdate();
	//schedule(schedule_selector(updateCustom), 1.0f, kRepeatForever, 0);
	//scheduleOnce(schedule_selector(updateOnce), 0.1f);
	auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
	auto red = LayerColor::create(Color4B(255, 100, 100, 128), visibleSize.width/2, visibleSize.height/2);
	auto green = LayerColor::create(Color4B(100, 255, 100, 128), visibleSize.width/4, visibleSize.height/4);
	red->addChild(green);
	this->addChild(red);

	auto sprite = Sprite::create();
	sprite->setColor(Color3B(100, 100, 255));
	sprite->setContentSize(Size(50, 50));
	red->addChild(sprite);

	/*auto placeAction = Place::create(Vec2(10,10));

	auto flipxAction = FlipX::create(true);
	auto moveTo = MoveTo::create(0.4f, Vec2(0, 0));
	
	auto blink = Blink::create(10, 10);
	auto action = Sequence::create(moveTo, flipxAction, blink, NULL);*/
	/*sprite->runAction(action);*/

	auto dic = TestFileUtils::cfgMonsterGet();

    return true;
}

void HelloWorld::update(float dt)
{
	log("update");
}

void HelloWorld::updateCustom(float dt)
{
	log("update custom");
}

void HelloWorld::updateOnce(float dt)
{
	log("once");
}