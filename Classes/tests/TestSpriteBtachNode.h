/*
SpriteBtachNode�Ѳ��Ƽ�ʹ��
*/
#pragma once

#include "cocos2d.h"

USING_NS_CC;

class TestSpriteBtachNode : public Layer
{
public:
	TestSpriteBtachNode(void);
	~TestSpriteBtachNode(void);

	CREATE_FUNC(TestSpriteBtachNode);
	virtual bool init();

	void normal();
	void btach();
};

