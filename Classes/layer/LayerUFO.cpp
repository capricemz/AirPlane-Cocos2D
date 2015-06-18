#include "layer\LayerUFO.h"
#include "util\UtilRandom.h"
#include "layer\UFO.h"

const float INTERNAL = 3.0f/*10.0f*/;
const float PROBABILITY_DOUBEL_BULLET = 0.0f/*0.8f*/;
const float PROBABILITY_BOOM = 1.0f/*0.2f*/;

LayerUFO::LayerUFO(void)
{
	_timeNextAdd = UtilRandom::randomWave(INTERNAL);
}

LayerUFO::~LayerUFO(void)
{
}

bool LayerUFO::init()
{
	auto isInit = false;
	do 
	{
		CC_BREAK_IF(!Layer::init());

		schedule(schedule_selector(LayerUFO::ufoAdd),1.0f);

		isInit = true;
	} while (0);
	return isInit;
}

Vector<UFO *> LayerUFO::vecUFOGet()
{
	return _vecUFO;
}

void LayerUFO::ufoAdd( float delte )
{
	_timeNow += delte;

	if(_timeNow > _timeNextAdd)
	{
		_timeNextAdd = _timeNow + UtilRandom::randomWave(INTERNAL);

		auto type = typeUFOGet();
		UFO *ufo = UFO::create(type, CallFuncN::create(CC_CALLBACK_1(LayerUFO::ufoRemove4Vec,this)));
		addChild(ufo);
		_vecUFO.pushBack(ufo);
	}
}

TypeUFO LayerUFO::typeUFOGet()
{
	vector<TypeUFO> values;
	values.push_back(TypeUFO::DOUBEL_BULLET);
	values.push_back(TypeUFO::BOOM);
	vector<float> probabilityDistribution;
	probabilityDistribution.push_back(PROBABILITY_DOUBEL_BULLET);
	probabilityDistribution.push_back(PROBABILITY_BOOM);
	auto randomPitchUpon = UtilRandom::randomPitchUpon(probabilityDistribution);
	return values[randomPitchUpon];
}

void LayerUFO::ufoRemove4Vec( Node *ufo )
{
	if (ufo != NULL)
	{
		auto find = _vecUFO.find((UFO *)ufo);
		if (_vecUFO.end() != find)
		{
			_vecUFO.erase(find);
		}
	}
}