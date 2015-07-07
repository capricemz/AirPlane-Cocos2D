#ifndef __TEST_FILE_UTILS_H__
#define __TEST_FILE_UTILS_H__

#include "cocos2d.h"

USING_NS_CC;
using namespace std;

struct CfgMonster
{
	int index;
	string name;
	int hp;
};
typedef std::map<int32_t, CfgMonster> DicCfgMonster;

class TestFileUtils
{
public:
	TestFileUtils();
	~TestFileUtils();

	static string readFileByName(const string &fileName);
	static bool saveFile(char *content, const string &fileName);
	static DicCfgMonster cfgMonsterGet();

private:

};

#endif