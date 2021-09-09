#pragma once

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

class Config
{
public:
	static void Load();
	static int WindowWidth;
	static int WindowHeight;
	static std::string ThemePath;
};

