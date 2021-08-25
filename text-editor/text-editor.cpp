#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <unordered_map>

#include "Cursor.h"
#include "File.h"

int main()
{
    Font::load();
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Text Editor",sf::Style::Default,settings);

    sf::Text templateText;
    templateText.setFont(Font::defaultFont);
    templateText.setPosition(20, 30.f);

    float yPadding = 30.f;

    Cursor cursor(
        sf::Vector2f(10,yPadding),
        sf::Vector2f(10,35)
    );

    
    //std::vector<sf::Text> output;
    File::content.push_back(Line("",0));
    cursor.setCurrentLine(0);

    // run the program as long as the window is open
    while (window.isOpen())
    {
        settings.antialiasingLevel = 8;
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::TextEntered)
            {
                cursor.isVisible = true;
                cursor.clock.restart();
                if (event.text.unicode < 128) {
                    // backspace
                    if (event.text.unicode == 8) {
                        // if the line is empty
                        if (File::content[cursor.getCurrentLine()].text.getString().getSize() == 0 && (File::content.size() > 0 && cursor.getCurrentLine() != 0)) {
                            std::cout << "bruh";
                            File::content.erase(File::content.begin()+cursor.getCurrentLine());
                            cursor.setCurrentLine(cursor.getCurrentLine() - 1);
                            for (int i = cursor.getCurrentLine()+1; i < File::content.size(); i++) {
                                File::content[i].lineNumber--;
                            }
                        } else {
                            // delete a character
                            File::content[cursor.getCurrentLine()].text.setString(File::content[cursor.getCurrentLine()].text.getString().substring(0, File::content[cursor.getCurrentLine()].text.getString().getSize() - 1));
                        }
                    }
                    // enter
                    else if (event.text.unicode == 13) {
                        cursor.setCurrentLine(cursor.getCurrentLine() + 1);
                        File::content.insert(File::content.begin()+cursor.getCurrentLine(),Line("", cursor.getCurrentLine()));
                        for (int i = cursor.getCurrentLine(); i < File::content.size(); i++) {
                            File::content[i].lineNumber++;
                        }
                    }
                    // normal ascii
                    else {
                        File::content[cursor.getCurrentLine()].text.setString(File::content[cursor.getCurrentLine()].text.getString() + static_cast<char>(event.text.unicode));
                    }
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                cursor.isVisible = true;
                cursor.clock.restart();
                if (File::content.size() > 0 && cursor.getCurrentLine() != 0) {
                    cursor.setCurrentLine(cursor.getCurrentLine() - 1);
                }
            } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                cursor.isVisible = true;
                cursor.clock.restart();
                if (File::content.size() > 0 && cursor.getCurrentLine() < File::content.size() - 1) {
                    cursor.setCurrentLine(cursor.getCurrentLine() + 1);
                }
            }
        }

        cursor.setPosition(sf::Vector2f(
            File::content[cursor.getCurrentLine()].text.getPosition().x,
            File::content[cursor.getCurrentLine()].text.getPosition().y)
        );

        if (cursor.clock.getElapsedTime().asSeconds() >= cursor.getAnimationInterval()) {
            cursor.clock.restart();
            cursor.isVisible = !cursor.isVisible;
        }

        // set position all lines of file
        File::content[0].text.setPosition(10, yPadding);
        for (int i = 1; i < File::content.size(); i++) {
            File::content[i].text.setPosition(10,(File::content[i].lineNumber) * yPadding);
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
        // window.draw(...);
        for (auto item : File::content) {
            window.draw(item.text);
        }
        if (cursor.isVisible) {
            window.draw(cursor);
        }

        // end the current frame
        window.display();
    }

    std::ofstream file;
    file.open("output.txt");
    for (int i = 0; i < File::content.size(); i++) {
        if (i != File::content.size() - 1) {
            file << File::content[i].text.getString().toAnsiString() << std::endl;
        }
        else {
            file << File::content[i].text.getString().toAnsiString();
        }
    }
    file.close();

    return 0;
}