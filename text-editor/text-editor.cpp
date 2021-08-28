#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>

#include "Cursor.h"
#include "File.h"
#include "Button.h"
#include "TextInput.h"
#include "UIBuilder.h"
#include "State.h"
#include "Keybinds.h"
#include "UIHover.h"

int main()
{
    // loads the default font
    Font::load();

    // create the window
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800, 600), "Text Editor",sf::Style::Default);

    File::CurrentState = State::Default;

    // initialize main cursor
    // Cursor::MainCursor = Cursor(sf::Vector2f(10, File::YPadding), sf::Vector2f(10, 35));
    Cursor cursor = Cursor(sf::Vector2f(10, File::YPadding), sf::Vector2f(10, 35));

    // initialize first line of file
    File::Content.push_back(Line("",0));
    cursor.setCurrentLine(File::Content[0]);

    // make top-left file button
    Button* fileButton = new Button();
    UIBuilder::buildFileButton(*fileButton);

    // make file input pop-up box
    TextInput* fileInput = new TextInput();
    UIBuilder::buildFileInputBox(*fileInput);

    // run the program as long as the window is open
    while (window->isOpen())
    {
        // keep cursor.getCurrentLine up to date with the actual current line (note: cursor.getCurrentLine returns a copy)
        cursor.setCurrentLine(Line(File::Content[cursor.getCurrentLine().lineNumber].text.getString(), cursor.getCurrentLine().lineNumber));

        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (window->pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                window->close();
            }

            // handle hovering over fileButton
            if (UIHover::ButtonHover(*fileButton, *window)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    File::CurrentState = State::TextInput;
                    fileInput->isOpen = true;
                }
            }

            // reduced from 120 lines to 40...
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (File::CurrentState == State::Default) {

                if (event.type == sf::Event::TextEntered) {
                    // handle the cursor animation clock
                    Cursor::ResetCursorAnimation(cursor);

                    if (event.text.unicode < 128) {
                        // if press backspace
                        if (event.text.unicode == 8) {
                            // delete one character
                            Keybinds::DefaultBackspace(cursor);
                        }
                        // if pressed enter
                        else if (event.text.unicode == 13) {
                            Keybinds::DefaultEnter(cursor);
                        }
                        // normal ascii
                        else {
                            // append whatever was typed
                            File::Content[cursor.getCurrentLine().lineNumber].text.setString(File::Content[cursor.getCurrentLine().lineNumber].text.getString() + static_cast<char>(event.text.unicode));
                        }
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    // handle the cursor animation clock
                    Cursor::ResetCursorAnimation(cursor);

                    // decrement current line
                    if (File::Content.size() > 0 && cursor.getCurrentLine().lineNumber != 0) {
                        cursor.decrementLine(1);
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    // handle the cursor animation clock
                    Cursor::ResetCursorAnimation(cursor);

                    // increment current line
                    if (File::Content.size() > 0 && cursor.getCurrentLine().lineNumber < File::Content.size() - 1) {
                        cursor.incrementLine(1);
                    }
                }
            }
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (File::CurrentState == State::TextInput) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode < 128) {
                        // enter
                        if (event.text.unicode == 13) {
                            Keybinds::TextInputEnter(*fileInput, cursor);
                        }
                        // backspace
                        else if (event.text.unicode == 8) {
                            Keybinds::TextInputBackspace(*fileInput);
                        }
                        // input regular character
                        else {
                            fileInput->value.setString(fileInput->value.getString() + static_cast<char>(event.text.unicode));
                        }
                    }
                }
            }
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        }

        // set the cursor position to the beginning of the current line
        cursor.setPosition(sf::Vector2f(
            File::Content[cursor.getCurrentLine().lineNumber].text.getPosition().x,
            File::Content[cursor.getCurrentLine().lineNumber].text.getPosition().y)
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