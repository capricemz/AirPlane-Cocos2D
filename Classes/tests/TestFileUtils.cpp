#include "TestFileUtils.h"
#include "util\UtilString.h"

TestFileUtils::TestFileUtils()
{
}

TestFileUtils::~TestFileUtils()
{
}

std::string TestFileUtils::readFileByName(const string &fileName)
{
	auto fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
	log("path = %s", fullPath.c_str());

	if (fullPath.length() <= 0)
	{
		return nullptr;
	}
	auto file = fopen(fullPath.c_str(), "rb");//创建一个文件指针
	if (!file)
	{
		return nullptr;
	}
	char *buf;//要获取的字符串
	int len;//获取的长度
	fseek(file, 0, SEEK_END);//移到尾部
	len = ftell(file);//提取长度
	rewind(file);//回归原位
	//分配buf空间
	buf = (char *)malloc(sizeof(char) * len + 1);
	if (!buf)
	{
		log("malloc space is not enough.");
		return nullptr;
	}
	//读取文件
	int rlen = fread(buf, sizeof(char), len, file);//读取进的buf，单位大小，长度，文件指针
	buf[rlen] = '\0';
	log("has read Length = %d", rlen);
	log("has read content = %s", buf);

	string result = buf;
	fclose(file);
	free(buf);
	return result;
}

bool TestFileUtils::saveFile(char *content, const string &fileName)
{
	return false;
}

DicCfgMonster TestFileUtils::cfgMonsterGet()
{
	DicCfgMonster cfgs;
	auto strCfg = TestFileUtils::readFileByName("configs/monster.cfg");
	string delim = "[data]";
	strCfg = strCfg.substr(strCfg.find("[data]") + delim.length(), strCfg.length());
	delim = "\r\n";
	auto vecCfg = UtilString::split(strCfg, delim);
	delim = "\t";
	for each (auto strItem in vecCfg)
	{
		if (strItem == "")
		{
			continue;
		}
		CfgMonster cfg;
		auto vecItem = UtilString::split(strItem, delim);
		cfg.index = Value(vecItem[0]).asInt();
		cfg.name = vecItem[1];
		cfg.hp = Value(vecItem[2]).asInt();
		cfgs[cfg.index] = cfg;
	}
	return cfgs;
}
