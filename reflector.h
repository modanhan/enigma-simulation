#pragma once
#include <vector>
#include <string>

class reflector{
	std::vector<char> v; 
public:
	reflector();
	bool config(std::string);
	char& operator[](char);
};