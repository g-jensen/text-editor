#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Rect.hpp>

class Button
{
public:
	Button(sf::Vector2f position, sf::Vector2f size);
	void setPosition(sf::Vector2f position);
	bool contains(sf::Vector2f position);
	sf::IntRect hitbox;
	sf::RectangleShape rectangle;
};

