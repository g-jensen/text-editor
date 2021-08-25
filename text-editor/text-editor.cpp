#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <unordered_map>

#include "Cursor.h"
#include "File.h"
#include "Button.h"
#include "TextInput.h"

int main()
{
    Font::load();
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Text Editor",sf::Style::Default,settings);

    float yPadding = 30.f;

    Cursor cursor(
        sf::Vector2f(10,yPadding),
        sf::Vector2f(10,35)
    );

    File::content.push_back(Line("",0));
    cursor.setCurrentLine(0);


    Button fileButton(sf::Vector2f(0,0),sf::Vector2f(40,20));
    
    sf::Text fileButtonLabel;
    fileButtonLabel.setFont(Font::defaultFont);
    fileButtonLabel.setPosition(sf::Vector2f(0, 0));
    fileButtonLabel.setCharacterSize(20);
    fileButtonLabel.setFillColor(sf::Color::Black);
    fileButtonLabel.setString("file");

    TextInput fileInput(sf::Vector2f(100,100),sf::Vector2f(300,100));
    fileInput.setFillColor(sf::Color(200,200,200));
    fileInput.title.setString("input file: ");
    fileInput.isOpen = false;

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

            // handle hovering over fileButton
            if (fileButton.contains(sf::Mouse::getPosition(window))) {
                fileButton.setFillColor(fileButton.hoverColor);
                // handle clicking or "selecting" fileButton
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    fileInput.isOpen = true;
                }
            }
            else {
                fileButton.setFillColor(sf::Color::White);
            }

            if (event.type == sf::Event::TextEntered)
            {
                // handle the cursor animation clock
                cursor.isVisible = true;
                cursor.clock.restart();

                if (event.text.unicode < 128) {

                    if (!fileInput.isOpen) {
                        // if press backspace
                        if (event.text.unicode == 8) {
                            // if the line is empty
                            if (File::content[cursor.getCurrentLine()].text.getString().getSize() == 0 && (File::content.size() > 0 && cursor.getCurrentLine() != 0)) {
                                // delete the line
                                File::content.erase(File::content.begin() + cursor.getCurrentLine());
                                // decrement current line
                                cursor.setCurrentLine(cursor.getCurrentLine() - 1);
                                // decrement every line's number past the empty line
                                for (int i = cursor.getCurrentLine() + 1; i < File::content.size(); i++) {
                                    File::content[i].lineNumber--;
                                }
                            }
                            else {
                                // delete a character
                                File::content[cursor.getCurrentLine()].text.setString(File::content[cursor.getCurrentLine()].text.getString().substring(0, File::content[cursor.getCurrentLine()].text.getString().getSize() - 1));
                            }
                        }
                        // if pressed enter
                        else if (event.text.unicode == 13) {
                            cursor.setCurrentLine(cursor.getCurrentLine() + 1);
                            File::content.insert(File::content.begin() + cursor.getCurrentLine(), Line("", cursor.getCurrentLine()));
                            for (int i = cursor.getCurrentLine(); i < File::content.size(); i++) {
                                File::content[i].lineNumber++;
                            }
                        }
                        // normal ascii
                        else {
                            // append whatever was typed
                            File::content[cursor.getCurrentLine()].text.setString(File::content[cursor.getCurrentLine()].text.getString() + static_cast<char>(event.text.unicode));
                        }
                    }
                    else {
                        if (event.text.unicode == 8) {
                            fileInput.value.setString(fileInput.value.getString().substring(0, fileInput.value.getString().getSize() - 1));
                        }
                        else {
                            fileInput.value.setString(fileInput.value.getString() + static_cast<char>(event.text.unicode));
                        }
                        if (event.text.unicode == 13) {
                            std::string value = (std::string)fileInput.value.getString();
                            value = value.substr(0, value.length() - 1);
                            std::ifstream myfile(value);
                            std::string data;
                            if (myfile.is_open())
                            {
                                File::content.clear();
                                int n = 1;
                                while (std::getline(myfile, data))
                                {
                                    File::content.push_back(Line(data, n));
                                    n++;
                                }
                                myfile.close();
                            }
                            else std::cout << "Unable to open \"" + value + "\"";
                            fileInput.isOpen = false;
                        }
                    }
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                // handle the cursor animation clock
                cursor.isVisible = true;
                cursor.clock.restart();
                // decrement current line
                if (File::content.size() > 0 && cursor.getCurrentLine() != 0) {
                    cursor.setCurrentLine(cursor.getCurrentLine() - 1);
                }
            }
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                // handle the cursor animation clock
                cursor.isVisible = true;
                cursor.clock.restart();
                // increment current line
                if (File::content.size() > 0 && cursor.getCurrentLine() < File::content.size() - 1) {
                    cursor.setCurrentLine(cursor.getCurrentLine() + 1);
                }
            }
        }

        // set the cursor position to the beginning of the current line
        cursor.setPosition(sf::Vector2f(
            File::content[cursor.getCurrentLine()].text.getPosition().x,
            File::content[cursor.getCurrentLine()].text.getPosition().y)
        );

        // handle the cursor animation clock
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
        for (auto item : File::content) {
            window.draw(item.text);
        }

        if (cursor.isVisible) {
            window.draw(cursor);
        }

        window.draw(fileButton);
        window.draw(fileButtonLabel);

        if (fileInput.isOpen) {
            window.draw(fileInput);
            window.draw(fileInput.value);
            window.draw(fileInput.title);
        }
        

        // end the current frame
        window.display();
    }

    // write to "output.txt"
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