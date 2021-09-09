#pragma once

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include "Keybinds.h"

class Config
{
public:
	static void Load();
	static int WindowWidth;
	static int WindowHeight;
private:
	static std::vector<std::string> vars;
};

