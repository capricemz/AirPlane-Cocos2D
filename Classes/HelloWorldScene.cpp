#include "HelloWorldScene.h"
#include "cocostudio/CocoStudio.h"
#include "tests/TestFileUtils.h"
#include "tests/TestLoadingBar.h"

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

	auto btn = Button::create(TEST_BTN_0, TEST_BTN_1);
	btn->setPosition(Vec2(btn->getContentSize().width / 2, btn->getContentSize().height));
	btn->addTouchEventListener(CC_CALLBACK_2(HelloWorld::touchHandle,this));
	addChild(btn);

	auto sizeWin = Director::getInstance()->getWinSize();

	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);

	auto btnSprite = Sprite::create(TEST_BTN_0);
	btnSprite->setPosition(Vec2(sizeWin.width / 2.0f, sizeWin.height / 2.0f));
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, btnSprite);
	addChild(btnSprite);

	/*auto layer = LayerColor::create(Color4B(0, 128, 128, 255));
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
	addChild(layer2, 30);*/

	//scheduleUpdate();
	//schedule(schedule_selector(updateCustom), 1.0f, kRepeatForever, 0);
	//scheduleOnce(schedule_selector(updateOnce), 0.1f);

	/*auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin = Director::getInstance()->getVisibleOrigin();
	auto red = LayerColor::create(Color4B(255, 100, 100, 128), visibleSize.width/2, visibleSize.height/2);
	auto green = LayerColor::create(Color4B(100, 255, 100, 128), visibleSize.width/4, visibleSize.height/4);
	red->addChild(green);
	this->addChild(red);

	auto sprite = Sprite::create();
	sprite->setColor(Color3B(100, 100, 255));
	sprite->setContentSize(Size(50, 50));
	red->addChild(sprite);*/

	/*auto placeAction = Place::create(Vec2(10,10));

	auto flipxAction = FlipX::create(true);
	auto moveTo = MoveTo::create(0.4f, Vec2(0, 0));
	
	auto blink = Blink::create(10, 10);
	auto action = Sequence::create(moveTo, flipxAction, blink, NULL);*/
	/*sprite->runAction(action);*/

	/*auto dic = TestFileUtils::cfgMonsterGet();*/

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

void HelloWorld::touchHandle(Ref *ref, Widget::TouchEventType type)
{
	if (type == Widget::TouchEventType::BEGAN)
	{
		/*TestLoadingBar::doTest(this);*/
		auto _target = (Widget *)ref;
		intptr_t id = 0;
		auto anchor = _target->getAnchorPoint();
		auto size = _target->getContentSize();
		auto postion = _target->getPosition();
		log("0 postion.x:%f,postion.y:%f", postion.x, postion.y);
		postion.add(Vec2((0.5f - anchor.x) * size.width, (0.5f - anchor.y) * size.height));
		log("1 postion.x:%f,postion.y:%f", postion.x, postion.y);
		postion = _target->getParent()->convertToWorldSpace(postion);
		log("2 postion.x:%f,postion.y:%f", postion.x, postion.y);
		postion = Director::getInstance()->convertToGL(postion);
		log("3 postion.x:%f,postion.y:%f", postion.x, postion.y);
		/*Director::getInstance()->getOpenGLView()->handleTouchesBegin(1, &id, &postion.x, &postion.y);
		Director::getInstance()->getOpenGLView()->handleTouchesEnd(1, &id, &postion.x, &postion.y);*/
	}
}

bool HelloWorld::onTouchBegan(Touch *touch, Event *event)
{
	Sprite *btn = (Sprite *)event->getCurrentTarget();
	auto locationInView = touch->getLocationInView();
	log("locationInView.x:%f,locationInView.y:%f", locationInView.x, locationInView.y);
	auto postionTouch = btn->getParent()->convertTouchToNodeSpace(touch);
	log("postionTouch.x:%f,postionTouch.y:%f", postionTouch.x, postionTouch.y);
	/*auto postionWindow = btn->getParent()->convertToWindowSpace(postionTouch);
	log("postionWindow.x:%f,postionWindow.y:%f", postionWindow.x, postionWindow.y);*/
	/*auto postionWorld = btn->getParent()->convertToWorldSpace(postionTouch);
	log("postionWorld.x:%f,postionWorld.y:%f", postionWorld.x, postionWorld.y);*/
	auto postionGL = Director::getInstance()->convertToGL(postionTouch);
	log("postionGL.x:%f,postionGL.y:%f", postionGL.x, postionGL.y);
	return false;
}