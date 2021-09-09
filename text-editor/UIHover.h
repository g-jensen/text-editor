#pragma once

#include "Button.h"
#include <SFML/Graphics.hpp>
#include "File.h"
#include "Theme.h"

class UIHover
{
public:
	static bool ButtonHover(Button &button, sf::RenderWindow &window);
};

