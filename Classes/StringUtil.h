#pragma once


#include<vector>
#include<string>


class StringUtil {
public:
	static std::vector<std::string> split(const std::string &s, char delim);
    
    static std::string trimLeft(const std::string &text, const std::string &sp);
    static std::string trimRight(const std::string &text, const std::string &sp);
    static std::string trim(const std::string &text, const std::string &sp);
};
