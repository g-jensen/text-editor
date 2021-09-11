#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

#include "IDrawable.h"
#include "Font.h"

/// <summary>
/// DEPRECATED | Opens a text input box
/// </summary>
class TextInput : public IDrawable
{
public:
	TextInput(sf::Vector2f position, sf::Vector2f size);
	TextInput();
	void draw(sf::RenderWindow* window);
	bool isOpen;
	sf::Text title;
	sf::Text value;
};

