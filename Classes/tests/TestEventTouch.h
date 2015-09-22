#pragma execution_character_set("utf-8")

#ifndef __TESTS_TEST_EVENT_TOUCH_H__
#define __TESTS_TEST_EVENT_TOUCH_H__

#include "cocos2d.h"

USING_NS_CC;

class TestEventTouch : public Node
{
public:
	CREATE_FUNC(TestEventTouch);

public:
	TestEventTouch();
	~TestEventTouch();

	virtual bool init();

private:

};

#endif