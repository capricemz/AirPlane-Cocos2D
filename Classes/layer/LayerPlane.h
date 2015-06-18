#pragma once

#include "cocos2d.h"

USING_NS_CC;

const int AIRPLANE = 747;

class LayerPlane : public Layer
{
public:
	LayerPlane(void);
	~LayerPlane(void);

	CREATE_FUNC(LayerPlane);

	virtual bool init();

	void moveTo(Point location);

public:
	bool isAlive;

};

