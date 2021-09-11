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
    button.setOutlineColor(Theme::buttonOutlineColor);
    button.setOutlineThickness(outlineThickness);
    button.setFillColor(Theme::buttonFillColor);
    button.label.setFont(Font::defaultFont);
    button.label.setPosition(sf::Vector2f(0 + outlineThickness, 0 + outlineThickness));
    button.label.setCharacterSize(20);
    button.label.setFillColor(Theme::textColor);
    button.label.setString("file");
}

void UIBuilder::buildSettingsButton(Button& button) {
    float outlineThickness = 3.f;
    button = Button(sf::Vector2f(50 + outlineThickness, 0 + outlineThickness), sf::Vector2f(80, 20));
    button.setOutlineColor(Theme::buttonOutlineColor);
    button.setOutlineThickness(outlineThickness);
    button.setFillColor(Theme::buttonFillColor);
    button.label.setFont(Font::defaultFont);
    button.label.setPosition(sf::Vector2f(50 + outlineThickness, 0 + outlineThickness));
    button.label.setCharacterSize(20);
    button.label.setFillColor(Theme::textColor);
    button.label.setString("settings");
}

void UIBuilder::buildSnippitsButton(Button& button) {
    float outlineThickness = 3.f;
    button = Button(sf::Vector2f(80 + 50 + outlineThickness, 0 + outlineThickness), sf::Vector2f(80, 20));
    button.setOutlineColor(Theme::buttonOutlineColor);
    button.setOutlineThickness(outlineThickness);
    button.setFillColor(Theme::buttonFillColor);
    button.label.setFont(Font::defaultFont);
    button.label.setPosition(sf::Vector2f(80 + 50 + outlineThickness, 0 + outlineThickness));
    button.label.setCharacterSize(20);
    button.label.setFillColor(Theme::textColor);
    button.label.setString("snippits");
}

void UIBuilder::buildExitButton(Button& button)
{
    float buttonSize = 40;
    float outlineThickness = 3.f;
    button = Button(sf::Vector2f(File::window->getSize().x - buttonSize - outlineThickness, 0 + outlineThickness), sf::Vector2f(buttonSize, 20));
    button.setOutlineColor(Theme::buttonOutlineColor);
    button.setOutlineThickness(outlineThickness);
    button.setFillColor(Theme::buttonFillColor);
    button.label.setFont(Font::defaultFont);
    button.label.setPosition(sf::Vector2f(File::window->getSize().x - buttonSize - outlineThickness, 0 + outlineThickness));
    button.label.setCharacterSize(20);
    button.label.setFillColor(Theme::textColor);
    button.label.setString("x");
}
