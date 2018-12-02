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

std::string StringUtil::trimLeft(const std::string &text, const std::string &sp) {
    size_t startpos = text.find_first_not_of(sp);
    return (startpos == std::string::npos) ? "" : text.substr(startpos);
}

std::string StringUtil::trimRight(const std::string &text, const std::string &sp) {
    size_t endpos = text.find_last_not_of(sp);
    return (endpos == std::string::npos) ? "" : text.substr(0, endpos+1);
}

std::string StringUtil::trim(const std::string &text, const std::string &sp) {
    return trimRight(trimLeft(text, sp), sp);
}
