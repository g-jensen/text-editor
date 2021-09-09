#pragma once

#include "Theme.h"
#include <SFML/Graphics/Font.hpp>

class Font
{
public:
	static sf::Font defaultFont;
	static bool hasBeenLoaded;
	static void load();
};

