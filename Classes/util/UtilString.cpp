#include "UtilString.h"

int UtilString::utf8Strlen(const char *str)
{
	if (str == NULL)
	{
		return 0;
	}

	int byteLength = static_cast<int>(strlen(str));

	int length = 0;

	int index = 0;
	while (index < byteLength)
	{
		char ch = str[index];

		length++;

		index++;

		if (index >= byteLength)
		{
			break;
		}

		if (ch & 0x80)
		{
			ch <<= 1;
			while (ch & 0x80)
			{
				index++;
				ch <<= 1;
			}
		}
	}

	return length;
}

VectorString UtilString::split(const string &str, const string &delim /* =  */, uint32_t maxSplits /* = 0 */)
{
	VectorString ret;

	uint32_t numSplits = 0;

	size_t start = 0;
	size_t pos = 0;
	do
	{
		pos = str.find_first_of(delim, start);
		if (pos == start)
		{
			ret.push_back("");
			start = pos + 1;
		}
		else if (pos == string::npos || (maxSplits && numSplits == maxSplits))
		{
			ret.push_back(str.substr(start));
			break;
		}
		else
		{
			ret.push_back(str.substr(start, pos - start));
			start = pos + 1;
		}

		++numSplits;

	} while (pos != string::npos);

	return ret;
}

string UtilString::combi(const VectorInt32 &ve, const string &delim)
{
	string str = "";
	VectorInt32::const_iterator it = ve.begin();
	if (it != ve.end())
	{
		char buff[20] = {};
		string tempStr = "";
		sprintf(buff, "%d", *it);
		tempStr = buff;
		str += tempStr;
		it++;
	}

	for (; it != ve.end(); ++it)
	{
		char buff[20] = {};
		string tempStr = "";
		sprintf(buff, "%d", *it);
		tempStr = buff;
		str += ":";
		str += tempStr;
	}

	return str;
}
//s1:Ä¿±ê×Ö·û´®  s2:ÐèÒªÌæ»»µÄ×Ö·û´® s3:Ìæ»»³ÉµÄ×Ö·û´®
void UtilString::string_replace(string &s1, const string &s2, const string &s3)
{
	string::size_type pos = 0;
	string::size_type a = s2.size();
	string::size_type b = s3.size();
	if ((pos = s1.find(s2, pos)) != string::npos)
	{
		s1.replace(pos, a, s3);
		pos += b;
	}
}

UtilString::UtilString()
{
}

UtilString::~UtilString()
{
}
