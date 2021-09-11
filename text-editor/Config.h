#pragma once

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

class Config
{
public:
	/// <summary>
	/// Loads config.json
	/// </summary>
	static void Load();

	/// <summary>
	/// Window width variable read in from config.json
	/// </summary>
	static int WindowWidth;

	/// <summary>
	/// Window height variable read in from config.json
	/// </summary>
	static int WindowHeight;

	/// <summary>
	/// Path of the theme file
	/// </summary>
	static std::string ThemePath;
};

