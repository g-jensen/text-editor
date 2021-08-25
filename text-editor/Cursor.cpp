#include "Cursor.h"

Cursor::Cursor(sf::Vector2f position, sf::Vector2f size)
{
	this->setPosition(position);
	this->setSize(size);
	this->clock.restart();
	this->animationInterval = 0.5f;
	this->currentLine = 0;
	this->isVisible = true;
}

void Cursor::setCurrentLine(int line)
{
	this->currentLine = line;
}

void Cursor::setAnimationInterval(float interval)
{
	this->animationInterval = interval;
}

int Cursor::getCurrentLine()
{
	return this->currentLine;
}

float Cursor::getAnimationInterval()
{
	return this->animationInterval;
}
