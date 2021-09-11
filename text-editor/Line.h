#pragma once

#include <SFML/Graphics/Text.hpp>
#include "Font.h"
#include <iostream>

class Line
{
public:

	/// <param name="content">Text contained in the line</param>
	/// <param name="lineNumber">Line number</param>
	Line(std::string content, int lineNumber);
	Line();

	/// <returns>If the line is empty</returns>
	bool isEmpty();

	/// <summary>
	/// Deletes a character from the line
	/// </summary>
	/// <param name="index">Index of the character to be deleted</param>
	void deleteCharacter(int index);
	/// <summary>
	/// Text that is displayed when drawing the line
	/// </summary>
	sf::Text text;

	/// <summary>
	/// List of all characters in the text
	/// </summary>
	std::vector<sf::Text> textList;

	/// <summary>
	/// Zero-indexed vertical order of the line
	/// </summary>
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
	float getWidth(unsigned int n);
};

