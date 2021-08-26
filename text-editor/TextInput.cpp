#include "TextInput.h"

TextInput::TextInput(sf::Vector2f position, sf::Vector2f size)
{
	this->setPosition(position);
	this->setSize(size);
	
	this->isOpen = false;

	this->value.setFont(Font::defaultFont);
	this->value.setPosition(sf::Vector2f(position.x + 10, position.y + 45));

	this->title.setFont(Font::defaultFont);
	this->title.setPosition(sf::Vector2f(position.x + 10, position.y));
}

TextInput::TextInput()
{
	this->isOpen = false;
}

void TextInput::draw(sf::RenderWindow* window)
{
	window->draw(*this);
	window->draw(this->title);
	window->draw(this->value);
}
