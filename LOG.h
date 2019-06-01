#ifndef _LOG
#define _LOG

#include <iostream>
#include <string>
#include <vector>

class LOG
{
public:
	void Add(std::wstring msg) {log_list.push_back(msg);}

private:
	std::vector<std::wstring> log_list;
};

#endif 