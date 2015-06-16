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

	/*static Enemy *create(TypeEnemy value, const std::function<void()> &func);
	virtual bool init(TypeEnemy value, const std::function<void()> &func);*/
	static Enemy *create(TypeEnemy value, CallFuncN *actionRemove4Vec);
	virtual bool init(TypeEnemy value, CallFuncN *actionRemove4Vec);

	TypeEnemy typeGet();
	const int hpGet();
	void hpLose();

	void blowup();
private:
	void remove4Par();
private:
	TypeEnemy _type;
	int _hp;
	float _duration;
	/*std::function<void()> _funcRemove4Vec;*/
	CallFuncN *_actionRemove4Vec;
};

