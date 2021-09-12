#include "UIBuilder.h"

sf::Vector2f UIBuilder::fileButtonSize = {};
sf::Vector2f UIBuilder::settingsButtonSize = {};
sf::Vector2f UIBuilder::snippitButtonSize = {};

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
    sf::Text templateText;
    templateText.setFont(Font::defaultFont);
    templateText.setString("gp");
    templateText.setCharacterSize(20);

    button = Button();

    float outlineThickness = 3.f;
    button.label.setCharacterSize(20);
    button.label.setFillColor(Theme::textColor);
    button.label.setString("file");
    button.label.setFont(Font::defaultFont);

    UIBuilder::fileButtonSize.x = button.label.getGlobalBounds().width + outlineThickness * 2;
    UIBuilder::fileButtonSize.y = templateText.getGlobalBounds().height + outlineThickness * 2;

    button.label.setPosition(sf::Vector2f(outlineThickness,0));
    button.setPosition(outlineThickness,outlineThickness);
    button.setSize(UIBuilder::fileButtonSize);
    button.setOutlineColor(Theme::buttonOutlineColor);
    button.setOutlineThickness(outlineThickness);
    button.setFillColor(Theme::buttonFillColor);
}

void UIBuilder::buildSettingsButton(Button& button) {
    sf::Text templateText;
    templateText.setFont(Font::defaultFont);
    templateText.setString("gp");
    templateText.setCharacterSize(20);

    button = Button();

    float outlineThickness = 3.f;
    button.label.setCharacterSize(20);
    button.label.setFillColor(Theme::textColor);
    button.label.setString("settings");
    button.label.setFont(Font::defaultFont);

    UIBuilder::settingsButtonSize.x = button.label.getGlobalBounds().width + outlineThickness * 2;
    UIBuilder::settingsButtonSize.y = templateText.getGlobalBounds().height + outlineThickness * 2;

    button.label.setPosition(sf::Vector2f(outlineThickness + UIBuilder::fileButtonSize.x, 0));
    button.setPosition(outlineThickness + UIBuilder::fileButtonSize.x, outlineThickness);
    button.setSize(UIBuilder::settingsButtonSize);
    button.setOutlineColor(Theme::buttonOutlineColor);
    button.setOutlineThickness(outlineThickness);
    button.setFillColor(Theme::buttonFillColor);
}

void UIBuilder::buildSnippitsButton(Button& button) {
    sf::Text templateText;
    templateText.setFont(Font::defaultFont);
    templateText.setString("gp");
    templateText.setCharacterSize(20);

    button = Button();

    float outlineThickness = 3.f;
    button.label.setCharacterSize(20);
    button.label.setFillColor(Theme::textColor);
    button.label.setString("snippits");
    button.label.setFont(Font::defaultFont);

    UIBuilder::snippitButtonSize.x = button.label.getGlobalBounds().width + outlineThickness * 2;
    UIBuilder::snippitButtonSize.y = templateText.getGlobalBounds().height + outlineThickness * 2;

    button.label.setPosition(sf::Vector2f(outlineThickness + UIBuilder::fileButtonSize.x + UIBuilder::settingsButtonSize.x, 0));
    button.setPosition(outlineThickness + UIBuilder::fileButtonSize.x + UIBuilder::settingsButtonSize.x, outlineThickness);
    button.setSize(UIBuilder::settingsButtonSize);
    button.setOutlineColor(Theme::buttonOutlineColor);
    button.setOutlineThickness(outlineThickness);
    button.setFillColor(Theme::buttonFillColor);
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
