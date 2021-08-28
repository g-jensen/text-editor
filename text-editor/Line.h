#pragma once

#include <SFML/Graphics/Text.hpp>
#include "Font.h"

class Line
{
public:
	Line(std::string content, int lineNumber);
	Line();
	bool isEmpty();
	void deleteEndCharacter();
	sf::Text text;
	int lineNumber;
};

