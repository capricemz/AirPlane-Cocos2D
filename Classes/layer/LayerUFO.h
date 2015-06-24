#pragma once

#include "cocos2d.h"
#include "layer/UFO.h"

USING_NS_CC;

class LayerUFO : public Layer
{
public:
	LayerUFO(void);
	~LayerUFO(void);

	CREATE_FUNC(LayerUFO);
	virtual bool init();

	Vector<UFO *> vecUFOGet();

	void ufoAdd(float delte);
	void ufoRemove4Vec(Node *ufo);

private:
	TypeUFO typeUFOGet();

private:
	float _timeNow;
	float _timeNextAdd;
	Vector<UFO *> _vecUFO;
};