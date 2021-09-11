#pragma once

#include "Button.h"
#include <SFML/Graphics.hpp>
#include "File.h"
#include "Theme.h"

class UIHover
{
public:
	/// <summary>
	/// Changes the button color to the theme's hover color if the mouse is hovering over it
	/// </summary>
	/// <param name="button">Button to check the position of</param>
	/// <param name="window">Window to check mouse position of</param>
	/// <returns>If the mouse position is contained by the button</returns>
	static bool ButtonHover(Button &button, sf::RenderWindow &window);
};

