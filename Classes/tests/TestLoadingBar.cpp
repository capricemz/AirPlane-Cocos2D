#include "TestLoadingBar.h"

static const string TEST_PLIST_HP_BAR = "moduleBattle/pic/battle/hp_bar.png";
static const string TEST_HP_BAR = "test/hp_bar.png";

void TestLoadingBar::doTest(Layer *layer)
{
	auto loadingBar = LoadingBar::create(/*TEST_PLIST_HP_BAR*/TEST_HP_BAR);
	auto sizeWin = Director::getInstance()->getWinSize();
	loadingBar->setPosition(Vec2(sizeWin.width / 2, sizeWin.height / 2));
	loadingBar->setPercent(20.0);
	layer->addChild(loadingBar);
}
