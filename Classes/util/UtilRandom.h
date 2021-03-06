#pragma once
#include <vector>

using namespace std;

class UtilRandom
{
public:
	UtilRandom(void);
	~UtilRandom(void);
	
	static float random();
	static float randomWave(float value, float wave = GOLDE_RATIO_Y);
	static float randomBewteen(float valueMin, float valueMax);
	static int randomPitchUpon(vector<float> probabilityDistribution);
public:
	static float GOLDE_RATIO_X;
	static float GOLDE_RATIO_Y;
};