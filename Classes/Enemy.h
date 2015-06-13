#pragma once

#include "cocos2d.h"

USING_NS_CC;

class Enemy : public Sprite
{
public:
	Enemy(void);
	~Enemy(void);

	CREATE_FUNC(Enemy);

	int hpGet();
	void hpSet(int value);
	void hpLose(int value = 1);

	void postionRandomSet();
public:
	int hp;
};

