#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include "IDrawable.h"

class Button : public IDrawable
{
public:
	Button(sf::Vector2f position, sf::Vector2f size);
	void draw(sf::RenderWindow* window);
	bool contains(sf::Vector2i position);
	sf::Color hoverColor;
};

