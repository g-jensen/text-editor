#include "UIHover.h"

bool UIHover::ButtonHover(Button& button, sf::RenderWindow &window)
{
    if (button.contains(sf::Mouse::getPosition(window))) {
        button.setFillColor(Theme::buttonHoverColor);
        return true;
    }
    else {
        button.setFillColor(Theme::buttonFillColor);
        return false;
    }
}
