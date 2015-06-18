#pragma once

#include "cocos2d.h"

USING_NS_CC;

const int MAX_BOOM_COUNT = 100000;

class LayerUI : public Layer
{
public:
	LayerUI(void);
	~LayerUI(void);

	CREATE_FUNC(LayerUI);
	virtual bool init();

	void countBoomAdd();
	void updateBoomCount();
	
private:
	//使用炸弹的回调函数
	void menuCallBackBoom();

private:
	Menu *_menuBoom;
	Label *_labelCountBoom;

	int _countBoom;
	int _score;
};

