#include "layer/UFO.h"
#include "util/UtilRandom.h"

UFO::UFO(void)
{
}


UFO::~UFO(void)
{
}

UFO *UFO::create( TypeUFO value, CallFuncN *actionRemove4Vec)
{
	UFO *ufo = new UFO(); 
	if (ufo && ufo->init(value, actionRemove4Vec)) 
	{ 
		ufo->autorelease(); 
		return ufo; 
	} 
	else 
	{ 
		delete ufo; 
		ufo = NULL; 
		return NULL; 
	}
}

bool UFO::init(TypeUFO value, CallFuncN *actionRemove4Vec)
{
	auto isInit = false;
	do 
	{
		_type = value;
		_actionRemove4Vec = actionRemove4Vec;
		string spriteFrameName;
		switch (value)
		{
		case TypeUFO::DOUBEL_BULLET:
			spriteFrameName = "ufo1.png";
			break;
		case TypeUFO::BOOM:
			spriteFrameName = "ufo2.png";
			break;
		default:
			spriteFrameName = "ufo1.png";
			break;
		}
		CC_BREAK_IF(!initWithSpriteFrameName(spriteFrameName));

		auto sizeUFO = getContentSize();
		auto sizeWin = Director::getInstance()->getWinSize();
		auto xActual = UtilRandom::randomBewteen(sizeUFO.width/2,sizeWin.width - sizeUFO.width/2);//Ëæ»ú³õÊ¼Î»ÖÃ
		setAnchorPoint(Point(0.5f,0.5f));
		setPosition(xActual,sizeWin.height + sizeUFO.height/2);

		auto actionMoveBy1 = MoveBy::create(0.5f,Point(0,-150));
		auto actionMoveBy2 = MoveBy::create(0.3f,Point(0,100));
		auto actionMoveBy3 = MoveBy::create(1.0f,Point(0,-(sizeWin.height + sizeUFO.height)));
		auto actionRemove4Par = CallFunc::create(CC_CALLBACK_0(UFO::remove4Par,this));

		auto sequence = Sequence::create(actionMoveBy1,actionMoveBy2,actionMoveBy3,_actionRemove4Vec,actionRemove4Par,nullptr);

		runAction(sequence);

		isInit = true;
	} while (0);
	return isInit;
}

TypeUFO UFO::typeGet()
{
	return _type;
}

void UFO::remove4Par()
{
	auto parent = getParent();
	if (parent)
	{
		parent->removeChild(this,true);
	}
}

void UFO::pickUp()
{
	auto actionRemove4Par = CallFunc::create(CC_CALLBACK_0(UFO::remove4Par,this));
	auto sequence = Sequence::create(_actionRemove4Vec,actionRemove4Par,nullptr);
	runAction(sequence);
}