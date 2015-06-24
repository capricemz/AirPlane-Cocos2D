#pragma once

#include "cocos2d.h"

USING_NS_CC;

const int MAX_BOOM_COUNT = 100000;
const int TAG_MENU_BOOM = 1;
const int TAG_LABEL_COUNT_BOOM = 2;

class LayerUI : public Layer
{
public:
	LayerUI(void);
	~LayerUI(void);

	CREATE_FUNC(LayerUI);
	virtual bool init();

	void countBoomAdd();
	void updateBoomCount();
	void updateScore(int score);
	
private:
	//使用炸弹的回调函数
	void menuCallBackBoom();
	//暂停按钮的回调函数
	void menuCallbackPause();

private:
	Label *_labelScore;
	MenuItemSprite *_menuItemSpritePause;

	int _score;
	int _countBoom;

};

