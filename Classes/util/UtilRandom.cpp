#include "UtilRandom.h"
#include <math.h>
#include <stdlib.h>
#include <time.h>

float UtilRandom::GOLDE_RATIO_X = (sqrt(5.0) - 1) * 0.5f;
float UtilRandom::GOLDE_RATIO_Y = (3 - sqrt(5.0)) * 0.5f;

UtilRandom::UtilRandom(void)
{
}


UtilRandom::~UtilRandom(void)
{
}
/*
以value值为中心点数获得波动随机数
@param value 中心点数
@param wave 波动值,值为0时使用GOLDE_RATIO_Y作为wave值计算
@return 波动随机数
*/
float UtilRandom::randomWave( float value, float wave )
{
	return value * (1 - wave + 2 * wave * random());
}
/*
在valueMin值至valueMax值之间获得随机值
@param valueMin 随机下限值
@param valueMax 随机上限值
@return 随机值
*/
float UtilRandom::randomBewteen( float valueMin, float valueMax )
{
	return valueMin + (valueMax - valueMin) * random();
}
/*
根据probabilityDistribution数组中的概率分布在values数组中获得随机值
@param values
@param probabilityDistribution
@return 随机值
*/
float UtilRandom::randomPitchUpon( vector<int> values, vector<int> probabilityDistribution )
{
	if(values.size() != probabilityDistribution.size())
	{
		//throw new Error("数据长度不等");
		return NULL;
	}
	int i,l = probabilityDistribution.size();
	for (i=0;i<l;i++) 
	{
		if(i > 0)
		{
			probabilityDistribution[i] = probabilityDistribution[i] + probabilityDistribution[i-1];
		}
	}
	if(probabilityDistribution[i-1] != 1)
	{
		//throw new Error("概率之和不为1");
		return NULL;
	}
	for (i=0;i<l;i++) 
	{
		if(random() < probabilityDistribution[i])
		{
			break;
		}
	}
	return values[i];
}
/*
生成[0,1)之间的浮点随机数
*/
float UtilRandom::random()
{
	srand( (unsigned)time( NULL ) );
	return rand()/double(RAND_MAX);
}