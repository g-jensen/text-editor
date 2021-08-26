#include "UIBuilder.h"

void UIBuilder::buildFileInputBox(TextInput* textInput)
{
    textInput = new TextInput(sf::Vector2f(100, 100), sf::Vector2f(300, 100));
    textInput->setFillColor(sf::Color(200, 200, 200));
    textInput->title.setString("input file: ");
    textInput->isOpen = false;
}
