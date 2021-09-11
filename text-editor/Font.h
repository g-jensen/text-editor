#pragma once

#include "Theme.h"
#include <SFML/Graphics/Font.hpp>

class Font
{
public:
	/// <summary>
	/// Font in the theme file defined in config.json
	/// </summary>
	static sf::Font defaultFont;

	/// <summary>
	/// Returns if the default font has been loaded
	/// </summary>
	static bool hasBeenLoaded;

	/// <summary>
	/// Loads the default font
	/// </summary>
	static void load();
};

