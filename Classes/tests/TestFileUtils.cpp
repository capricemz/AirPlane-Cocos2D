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
	auto file = fopen(fullPath.c_str(), "rb");//����һ���ļ�ָ��
	if (!file)
	{
		return nullptr;
	}
	char *buf;//Ҫ��ȡ���ַ���
	int len;//��ȡ�ĳ���
	fseek(file, 0, SEEK_END);//�Ƶ�β��
	len = ftell(file);//��ȡ����
	rewind(file);//�ع�ԭλ
	//����buf�ռ�
	buf = (char *)malloc(sizeof(char) * len + 1);
	if (!buf)
	{
		log("malloc space is not enough.");
		return nullptr;
	}
	//��ȡ�ļ�
	int rlen = fread(buf, sizeof(char), len, file);//��ȡ����buf����λ��С�����ȣ��ļ�ָ��
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
