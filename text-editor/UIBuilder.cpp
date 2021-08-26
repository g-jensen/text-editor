#include "UIBuilder.h"

void UIBuilder::buildFileInputBox(TextInput &textInput)
{
    textInput = TextInput(sf::Vector2f(100, 100), sf::Vector2f(300, 100));
    textInput.setFillColor(sf::Color(200, 200, 200));
    textInput.title.setString("input file: ");
    textInput.isOpen = false;
}

void UIBuilder::buildFileButton(Button &button)
{
    button = Button(sf::Vector2f(0,0),sf::Vector2f(40,20));
    button.label.setFont(Font::defaultFont);
    button.label.setPosition(sf::Vector2f(0, 0));
    button.label.setCharacterSize(20);
    button.label.setFillColor(sf::Color::Black);
    button.label.setString("file");
}
