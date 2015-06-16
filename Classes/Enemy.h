#pragma once

#include "cocos2d.h"

USING_NS_CC;

enum TypeEnemy
{
	SMALL,
	MEDIUM,
	LARGE
};

class Enemy : public Sprite
{
public:
	Enemy(void);
	~Enemy(void);

	static Enemy *create(TypeEnemy value);
	virtual bool init(TypeEnemy value);
	void actionSet(const std::function<void(Node*)> &func);

	TypeEnemy typeGet();
	int hpGet();
private:
	TypeEnemy _type;
	int _hp;
};

