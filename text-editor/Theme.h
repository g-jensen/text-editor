#pragma once

#include <SFML/Graphics/Color.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include "Config.h"

class Theme
{
public:
	/// <summary>
	/// Loads the theme file determined in config.json
	/// </summary>
	static void Load();
	static std::string fontPath;
	static sf::Color backgroundColor;
	static sf::Color textColor;
	static sf::Color cursorColor;
	static sf::Color buttonFillColor;
	static sf::Color buttonHoverColor;
	static sf::Color buttonOutlineColor;
};

