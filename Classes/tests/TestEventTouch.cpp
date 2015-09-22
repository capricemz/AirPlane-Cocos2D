#pragma execution_character_set("utf-8")

#include "TestEventTouch.h"

TestEventTouch::TestEventTouch()
{
}

TestEventTouch::~TestEventTouch()
{
}

bool TestEventTouch::init()
{
	auto isInit = false;
	do 
	{
		CC_BREAK_IF(!Node::init());



		isInit = true;
	} while (0);
	return isInit;
}
