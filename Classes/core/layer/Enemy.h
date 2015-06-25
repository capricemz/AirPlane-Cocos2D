#pragma once

#include "cocos2d.h"

USING_NS_CC;

enum class TypeEnemy
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

	static Enemy *create(TypeEnemy value, CallFuncN *actionRemove4Vec);
	virtual bool init(TypeEnemy value, CallFuncN *actionRemove4Vec);

	TypeEnemy typeGet();

	const int hpGet();
	void hpLose();

	const int scoreGet();

	void blowup();
private:
	void remove4Par();
private:
	TypeEnemy _type;
	int _hp;
	int _score;
	float _duration;
	CallFuncN *_actionRemove4Vec;
};

