#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "IDrawable.h"

class Button : public IDrawable
{
public:
	Button(sf::Vector2f position, sf::Vector2f size);
	Button();
	void draw(sf::RenderWindow* window);
	bool contains(sf::Vector2i position);
	sf::Text label;
};

