#include "Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size)
{
	this->setSize(size);
	this->setPosition(position);
	this->defaultColor = sf::Color::White;
	this->setFillColor(defaultColor);
	this->hoverColor = sf::Color(this->getFillColor().r - 26, this->getFillColor().b - 26, this->getFillColor().g - 26);
}

Button::Button()
{
}

void Button::draw(sf::RenderWindow* window)
{
	window->draw(*this);
	window->draw(this->label);
}

bool Button::contains(sf::Vector2i position)
{
	return this->getGlobalBounds().contains(position.x,position.y);
}
