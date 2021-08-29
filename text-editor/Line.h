#pragma once

#include <SFML/Graphics/Text.hpp>
#include "Font.h"
#include <iostream>

class Line
{
public:
	Line(std::string content, int lineNumber);
	Line();
	bool isEmpty();
	void deleteCharacter(int index);
	sf::Text text;
	std::vector<sf::Text> textList;
	int lineNumber;

	/// <summary>
	/// Populates textList with sf::Text objects that are each character of the text parameter
	/// </summary>
	/// <param name="text">Text that will be stored</param>
	void populateTextList(sf::Text text);

	/// <summary>
	/// Adds the bounds of every character in the line to a certain character
	/// </summary>
	/// <param name="n">Index of character to stop</param>
	float getWidth(int n);
};

