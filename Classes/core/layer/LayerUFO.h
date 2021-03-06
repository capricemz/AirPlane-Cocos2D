#pragma once

#include "cocos2d.h"
#include "UFO.h"

USING_NS_CC;

class LayerUFO : public Layer
{
public:
	LayerUFO(void);
	~LayerUFO(void);

	CREATE_FUNC(LayerUFO);
	virtual bool init();

	Vector<UFO *> vecUFOGet();

	void addStop();

private:
	TypeUFO typeUFOGet();
	void ufoAdd(float delte);
	void ufoRemove4Vec(Node *ufo);

private:
	float _timeNow;
	float _timeNextAdd;
	Vector<UFO *> _vecUFO;
};