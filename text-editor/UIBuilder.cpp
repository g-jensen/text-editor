#include "UIBuilder.h"

// deprecated
void UIBuilder::buildFileInputBox(TextInput &textInput)
{
    textInput = TextInput(sf::Vector2f(100, 100), sf::Vector2f(300, 100));
    textInput.setFillColor(sf::Color(200, 200, 200));
    textInput.title.setString("input file: ");
    textInput.isOpen = false;
}

void UIBuilder::buildFileButton(Button &button)
{
    float outlineThickness = 3.f;
    button = Button(sf::Vector2f(0 + outlineThickness,0 + outlineThickness),sf::Vector2f(50,20));
    button.defaultColor = sf::Color::Black;
    button.setOutlineColor(sf::Color(148, 0, 211));
    button.setOutlineThickness(outlineThickness);
    button.label.setFont(Font::defaultFont);
    button.label.setPosition(sf::Vector2f(0 + outlineThickness, 0 + outlineThickness));
    button.label.setCharacterSize(20);
    button.label.setOutlineColor(sf::Color::White);
    button.label.setString("file");
}

void UIBuilder::buildSettingsButton(Button& button) {
    float outlineThickness = 3.f;
    button = Button(sf::Vector2f(50 + outlineThickness, 0 + outlineThickness), sf::Vector2f(80, 20));
    button.defaultColor = sf::Color::Black;
    button.setOutlineColor(sf::Color(148, 0, 211));
    button.setOutlineThickness(outlineThickness);
    button.label.setFont(Font::defaultFont);
    button.label.setPosition(sf::Vector2f(50 + outlineThickness, 0 + outlineThickness));
    button.label.setCharacterSize(20);
    button.label.setOutlineColor(sf::Color::White);
    button.label.setString("settings");
}
