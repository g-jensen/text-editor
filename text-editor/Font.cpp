#include "Font.h"

bool Font::hasBeenLoaded = false;
sf::Font Font::defaultFont;

void Font::load()
{
	if (!Font::hasBeenLoaded) {
		Font::defaultFont.loadFromFile("fonts/Ubuntu-Light.ttf");
		Font::hasBeenLoaded = true;
	}
}
