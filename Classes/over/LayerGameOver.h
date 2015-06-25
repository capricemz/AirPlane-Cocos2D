#pragma once

#include "cocos2d.h"

USING_NS_CC;

class LayerGameOver : public Layer
{
public:
	LayerGameOver(void);
	~LayerGameOver(void);

	CREATE_FUNC(LayerGameOver);

	virtual bool init();

	void scoreOverSet(int score);

private:
	void menuCallBackBack();

	void showAD();

	bool isSaveFileExist();

	int scoreHighestGet();

	void labelScoreHighestSet(Node *node);

private:
	int _scoreOver;
	Label *_labelScoreHighest;
};