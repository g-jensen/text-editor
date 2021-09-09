#include "Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size)
{
	this->setSize(size);
	this->setPosition(position);
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
