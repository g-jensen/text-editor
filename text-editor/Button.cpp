#include "Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size)
{
	this->setSize(size);
	this->setPosition(position);
	this->hoverColor = sf::Color(this->getFillColor().r - 26, this->getFillColor().b - 26, this->getFillColor().g - 26);
}

void Button::draw(sf::RenderWindow* window)
{
	window->draw(*this);
}

bool Button::contains(sf::Vector2i position)
{
	return this->getGlobalBounds().contains(position.x,position.y);
}
