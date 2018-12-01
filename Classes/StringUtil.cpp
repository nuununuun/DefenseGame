#include "StringUtil.h"

#include<sstream>

std::vector<std::string> StringUtil::split(const std::string & s, char delim)
{
	std::vector<std::string> elems;

	std::stringstream ss;
	ss.str(s);
	std::string item;
	while (getline(ss, item, delim)) {
		elems.push_back(item);
	}

	return elems;
}