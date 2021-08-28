#include "UIHover.h"

bool UIHover::ButtonHover(Button& button, sf::RenderWindow &window)
{
    if (button.contains(sf::Mouse::getPosition(window))) {
        button.setFillColor(button.hoverColor);
        return true;
    }
    else {
        button.setFillColor(sf::Color::White);
        return false;
    }
}
