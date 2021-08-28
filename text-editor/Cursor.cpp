#include "Cursor.h"

Cursor::Cursor(sf::Vector2f position, sf::Vector2f size)
{
	this->setPosition(position);
	this->setSize(size);
	this->clock.restart();
	this->animationInterval = 0.5f;

	// this will probably cause a bug
	this->currentLine = Line("", 0);
	
	this->isVisible = true;
}

void Cursor::resetCursorAnimation()
{
	this->isVisible = true;
	this->clock.restart();
}

void Cursor::updateCursorAnimation()
{
	if (this->clock.getElapsedTime().asSeconds() >= this->getAnimationInterval()) {
		this->clock.restart();
		this->isVisible = !this->isVisible;
	}
}

void Cursor::incrementLine(int n)
{
	this->setCurrentLine(Line(this->getCurrentLine().text.getString(), this->getCurrentLine().lineNumber + n));
}

void Cursor::decrementLine(int n)
{
	this->setCurrentLine(Line(this->getCurrentLine().text.getString(), this->getCurrentLine().lineNumber - n));
}

void Cursor::setCurrentLine(Line line)
{
	this->currentLine = line;
}

void Cursor::setAnimationInterval(float interval)
{
	this->animationInterval = interval;
}

Line Cursor::getCurrentLine()
{
	return this->currentLine;
}

float Cursor::getAnimationInterval()
{
	return this->animationInterval;
}