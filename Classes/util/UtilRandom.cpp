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
��valueֵΪ���ĵ�����ò��������
@param value ���ĵ���
@param wave ����ֵ,ֵΪ0ʱʹ��GOLDE_RATIO_Y��Ϊwaveֵ����
@return ���������
*/
float UtilRandom::randomWave( float value, float wave )
{
	return value * (1 - wave + 2 * wave * random());
}
/*
��valueMinֵ��valueMaxֵ֮�������ֵ
@param valueMin �������ֵ
@param valueMax �������ֵ
@return ���ֵ
*/
float UtilRandom::randomBewteen( float valueMin, float valueMax )
{
	return valueMin + (valueMax - valueMin) * random();
}
/*
����probabilityDistribution�����еĸ��ʷֲ���values�����л�����ֵ
@param values
@param probabilityDistribution
@return ���ֵ
*/
float UtilRandom::randomPitchUpon( vector<int> values, vector<int> probabilityDistribution )
{
	if(values.size() != probabilityDistribution.size())
	{
		//throw new Error("���ݳ��Ȳ���");
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
		//throw new Error("����֮�Ͳ�Ϊ1");
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
����[0,1)֮��ĸ��������
*/
float UtilRandom::random()
{
	srand( (unsigned)time( NULL ) );
	return rand()/double(RAND_MAX);
}