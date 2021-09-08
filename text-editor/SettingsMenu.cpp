#include "SettingsMenu.h"

void SettingsMenu::Open(int width, int height)
{
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(width, height), "Settings", sf::Style::Default);

	window->setFramerateLimit(60);

	while (window->isOpen()) {

		window->setFramerateLimit(60);

		sf::Event event;
		while (window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window->close();
			}
		}

		window->clear();

		// window->draw();

		window->display();
	}

	delete window;
}
