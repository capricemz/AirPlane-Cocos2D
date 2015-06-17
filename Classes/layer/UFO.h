#pragma once
#include "cocos2d.h"

USING_NS_CC;

enum class TypeUFO
{
	DOUBEL_BULLET,
	BOOM
};

class UFO : public Sprite
{
public:
	UFO(void);
	~UFO(void);

	static UFO *create(TypeUFO value, CallFuncN *actionRemove4Vec);
	virtual bool init(TypeUFO value, CallFuncN *actionRemove4Vec);
	TypeUFO typeGet();

	void pickUp();

private:
	void remove4Par();
private:
	TypeUFO _type;
	CallFuncN *_actionRemove4Vec;

};

