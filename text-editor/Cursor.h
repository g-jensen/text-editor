#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>
#include "Line.h"

class Cursor : public sf::RectangleShape
{
public:
	Cursor(sf::Vector2f position, sf::Vector2f size);
	sf::Clock clock;
	bool isVisible;

	void setCurrentLine(int line);
	void setAnimationInterval(float interval);

	int getCurrentLine();
	float getAnimationInterval();

private:
	int currentLine;
	float animationInterval;
};

