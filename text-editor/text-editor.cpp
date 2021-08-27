#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>

#include "Cursor.h"
#include "File.h"
#include "Button.h"
#include "TextInput.h"
#include "UIBuilder.h"
#include "State.h"

int main()
{
    // loads the default font
    Font::load();

    // create the window
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800, 600), "Text Editor",sf::Style::Default);

    File::CurrentState = State::Default;

    Cursor cursor(
        sf::Vector2f(10,File::YPadding),
        sf::Vector2f(10,35)
    );

    // initialize first line of file
    File::Content.push_back(Line("",0));
    cursor.setCurrentLine(0);

    // make top-left file button
    Button* fileButton = new Button();
    UIBuilder::buildFileButton(*fileButton);

    // make file input pop-up box
    TextInput* fileInput = new TextInput();
    UIBuilder::buildFileInputBox(*fileInput);

    // run the program as long as the window is open
    while (window->isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window->pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            // handle hovering over fileButton
            if (fileButton->contains(sf::Mouse::getPosition(*window))) {
                fileButton->setFillColor(fileButton->hoverColor);
                // handle clicking or "selecting" fileButton
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    File::CurrentState = State::TextInput;
                    fileInput->isOpen = true;
                }
            }
            else {
                fileButton->setFillColor(sf::Color::White);
            }

            if (File::CurrentState == State::Default) {

                if (event.type == sf::Event::TextEntered) {
                    // handle the cursor animation clock
                    cursor.isVisible = true;
                    cursor.clock.restart();

                    if (event.text.unicode < 128) {
                        // if press backspace
                        if (event.text.unicode == 8) {
                            // if the line is empty
                            if (File::Content[cursor.getCurrentLine()].text.getString().getSize() == 0 && (File::Content.size() > 0 && cursor.getCurrentLine() != 0)) {
                                // delete the line
                                File::Content.erase(File::Content.begin() + cursor.getCurrentLine());
                                // decrement current line
                                cursor.setCurrentLine(cursor.getCurrentLine() - 1);
                                // decrement every line's number past the empty line
                                for (int i = cursor.getCurrentLine() + 1; i < File::Content.size(); i++) {
                                    File::Content[i].lineNumber--;
                                }
                            }
                            else {
                                // delete a character
                                File::Content[cursor.getCurrentLine()].text.setString(File::Content[cursor.getCurrentLine()].text.getString().substring(0, File::Content[cursor.getCurrentLine()].text.getString().getSize() - 1));
                            }
                        }
                        // if pressed enter
                        else if (event.text.unicode == 13) {
                            cursor.setCurrentLine(cursor.getCurrentLine() + 1);
                            File::Content.insert(File::Content.begin() + cursor.getCurrentLine(), Line("", cursor.getCurrentLine()));
                            for (int i = cursor.getCurrentLine(); i < File::Content.size(); i++) {
                                File::Content[i].lineNumber++;
                            }
                        }
                        // normal ascii
                        else {
                            // append whatever was typed
                            File::Content[cursor.getCurrentLine()].text.setString(File::Content[cursor.getCurrentLine()].text.getString() + static_cast<char>(event.text.unicode));
                        }
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    // handle the cursor animation clock
                    cursor.isVisible = true;
                    cursor.clock.restart();
                    // decrement current line
                    if (File::Content.size() > 0 && cursor.getCurrentLine() != 0) {
                        cursor.setCurrentLine(cursor.getCurrentLine() - 1);
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    // handle the cursor animation clock
                    cursor.isVisible = true;
                    cursor.clock.restart();
                    // increment current line
                    if (File::Content.size() > 0 && cursor.getCurrentLine() < File::Content.size() - 1) {
                        cursor.setCurrentLine(cursor.getCurrentLine() + 1);
                    }
                }
            }
            if (File::CurrentState == State::TextInput) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode < 128) {
                        // enter
                        if (event.text.unicode == 13) {
                            std::string value = (std::string)fileInput->value.getString();
                            std::ifstream myfile(value);
                            std::string data;
                            if (myfile.is_open())
                            {
                                File::Content.clear();
                                int n = 1;
                                while (std::getline(myfile, data))
                                {
                                    File::Content.push_back(Line(data, n));
                                    n++;
                                }
                                myfile.close();
                            }
                            else { std::cout << "Unable to open \"" + value + "\""; }
                            cursor.setCurrentLine(0);
                            File::CurrentState = State::Default;
                            fileInput->isOpen = false;
                        }
                        // backspace
                        else if (event.text.unicode == 8) {
                            fileInput->value.setString(fileInput->value.getString().substring(0, fileInput->value.getString().getSize() - 1));
                        }
                        // regular character
                        else {
                            fileInput->value.setString(fileInput->value.getString() + static_cast<char>(event.text.unicode));
                        }
                    }
                }
            }
        }

        // set the cursor position to the beginning of the current line
        cursor.setPosition(sf::Vector2f(
            File::Content[cursor.getCurrentLine()].text.getPosition().x,
            File::Content[cursor.getCurrentLine()].text.getPosition().y)
        );

        // handle the cursor animation clock
        if (cursor.clock.getElapsedTime().asSeconds() >= cursor.getAnimationInterval()) {
            cursor.clock.restart();
            cursor.isVisible = !cursor.isVisible;
        }

        // set position all lines of file
        File::Content[0].text.setPosition(10, File::YPadding);
        for (int i = 1; i < File::Content.size(); i++) {
            File::Content[i].text.setPosition(10,(File::Content[i].lineNumber) * File::YPadding);
        }

        // clear the window with black color
        window->clear(sf::Color::Black);

        // draw everything here...
        for (auto item : File::Content) {
            window->draw(item.text);
        }

        if (cursor.isVisible) {
            window->draw(cursor);
        }

        fileButton->draw(window);

        if (fileInput->isOpen) {
            fileInput->draw(window);
        }
        
        // end the current frame
        window->display();
    }

    // delete pointers
    delete fileButton;
    delete fileInput;
    delete window;

    // write to "output.txt"
    File::WriteFileToOutput();

    return 0;
}