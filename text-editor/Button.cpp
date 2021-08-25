#include "Button.h"

Button::Button(sf::Vector2f position, sf::Vector2f size)
{
	this->hitbox = sf::IntRect((int)position.x,(int)position.y,(int)size.x,(int)size.y);
	this->rectangle = sf::RectangleShape(size);
	this->rectangle.setPosition(position);
}

void Button::setPosition(sf::Vector2f position)
{
	this->hitbox.left = position.x;
	this->hitbox.top = position.y;
	this->rectangle.setPosition(position);
}

bool Button::contains(sf::Vector2f position)
{
	return this->hitbox.contains((int)position.x,(int)position.y);
}
