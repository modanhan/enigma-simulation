#pragma once
#include <vector>
#include <string>
class rotor
{
	unsigned int p;
	std::vector<char> f,b;
public:
	rotor();
	bool config(const std::string&);
	bool operator++(int);
	char front(char);
	char back(char);
};
