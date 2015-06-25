#pragma once

#include "cocos2d.h"

USING_NS_CC;

class LayerWelcome : public Layer
{
public:
	LayerWelcome();
	~LayerWelcome();

	CREATE_FUNC(LayerWelcome);

	virtual bool init();

private:
	void loadingOver();
};