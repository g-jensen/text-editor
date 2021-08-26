#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class IDrawable : public sf::RectangleShape
{
public:
	virtual void draw(sf::RenderWindow* window) = 0;
};

