#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <string>

#include "Font.h"

class TextInput : public sf::RectangleShape
{
public:
	TextInput(sf::Vector2f position, sf::Vector2f size);
	bool isOpen;
	sf::Text title;
	sf::Text value;
};

