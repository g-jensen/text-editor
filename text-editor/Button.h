#pragma once

#include <SFML/Graphics/RectangleShape.hpp>

class Button : public sf::RectangleShape
{
public:
	Button(sf::Vector2f position, sf::Vector2f size);
	bool contains(sf::Vector2i position);
	sf::Color hoverColor;
};

