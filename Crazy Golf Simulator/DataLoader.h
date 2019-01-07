#pragma once
#include "GlobalHeaders.h"
#include "Square.h"
#include <fstream>
#include <sstream>

class DataLoader
{
public:
	DataLoader();
	~DataLoader();

	static void Load_Data();
	static std::vector<std::string> split(std::string strToSplit, char delimeter);
	static float zoom;
};


