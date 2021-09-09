#pragma once

#include <SFML/Graphics/Color.hpp>
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include "Config.h"

class Theme
{
public:
	static void Load();
	static std::string fontPath;
	static sf::Color backgroundColor;
	static sf::Color textColor;
	static sf::Color cursorColor;
	static sf::Color buttonFillColor;
	static sf::Color buttonHoverColor;
	static sf::Color buttonOutlineColor;
};

