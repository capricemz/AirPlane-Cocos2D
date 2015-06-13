#pragma once

#include "cocos2d.h"

USING_NS_CC;

const int AIRPLANE = 747;

class LayerPlane : public Layer
{
public:
	static LayerPlane *getInstance();//提供getInstance全局指针

	~LayerPlane(void);

	CREATE_FUNC(LayerPlane);

	virtual bool init();

	void moveTo(Point location);

public:
	bool isAlive;

private:
	LayerPlane(void);
};

