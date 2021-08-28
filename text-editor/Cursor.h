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

	void resetCursorAnimation();
	void updateCursorAnimation();

	void incrementLine(int n);
	void decrementLine(int n);

	void setCurrentLine(Line line);
	void setAnimationInterval(float interval);

	Line getCurrentLine();
	float getAnimationInterval();

private:
	Line currentLine;
	float animationInterval;
};

