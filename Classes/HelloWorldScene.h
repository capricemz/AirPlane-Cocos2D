#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "ui/CocosGUI.h"
#include <string.h>

USING_NS_CC;
using namespace cocos2d::ui;
using namespace std;

static const string TEST_BTN_0 = "test/btn0.png";
static const string TEST_BTN_1 = "test/btn1.png";

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Scene *createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

	void update(float dt) override;

	void updateCustom(float dt);

	void updateOnce(float dt);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
	
private:
	void touchHandle(Ref *ref, Widget::TouchEventType type);
	virtual bool onTouchBegan(Touch *touch, Event *event);
};

#endif // __HELLOWORLD_SCENE_H__
