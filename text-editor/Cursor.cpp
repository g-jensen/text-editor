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
	this->lineIndex = 0;
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

void Cursor::setLineNumber(int n)
{
	this->currentLine.lineNumber = n;
}

void Cursor::incrementLine(int n)
{
	Line placeholder = Line(this->getCurrentLine().text.getString(), this->getCurrentLine().lineNumber + n);
	placeholder.text.setPosition(10, (this->getCurrentLine().lineNumber + 1) * File::YPadding);
	this->setCurrentLine(placeholder);
}

void Cursor::decrementLine(int n)
{
	Line placeholder = Line(this->getCurrentLine().text.getString(), this->getCurrentLine().lineNumber - n);
	placeholder.text.setPosition(10, (this->getCurrentLine().lineNumber) * File::YPadding);
	this->setCurrentLine(placeholder);
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