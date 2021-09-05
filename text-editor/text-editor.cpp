#include <SFML/Graphics.hpp>
#include <iostream>
#include <ostream>
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

    Keybinds::DeleteCharacter = 8;
    Keybinds::InsertNewLine = 13;

    // loads the default font
    Font::load();

    // create the window
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800, 600), "Text Editor",sf::Style::Default);

    File::CurrentState = State::Default;

    Cursor cursor = Cursor(sf::Vector2f(10, File::YPadding), sf::Vector2f(2, 35));

    // initialize first line of file
    File::Content.push_back(Line("",0));
    cursor.setCurrentLine(File::Content[0]);

    // make top-left file button
    Button* fileButton = new Button();
    UIBuilder::buildFileButton(*fileButton);

    // make file input pop-up box
    TextInput* fileInput = new TextInput();
    UIBuilder::buildFileInputBox(*fileInput);

    cursor.lineIndex = 0;

    window->setFramerateLimit(300);

    float tempInterval = cursor.getAnimationInterval();

    // run the program as long as the window is open
    while (window->isOpen())
    {
        window->setFramerateLimit(60);

        // keep cursor.getCurrentLine up to date with the actual current line 
        // (note: cursor.getCurrentLine returns a copy as opposed to File::Content[cursor.getCurrentLine.lineNumber])
        cursor.setCurrentLine(Line(File::Content[cursor.getCurrentLine().lineNumber].text.getString(), cursor.getCurrentLine().lineNumber));

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
                    File::CurrentState = State::InputBox;
                    fileInput->isOpen = true;
                }
            }

            // default state code reduced from 120 lines to 40...
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (File::CurrentState == State::Default) {

                if (event.type == sf::Event::TextEntered) {
                    // handle the cursor animation clock
                    cursor.resetCursorAnimation();

                    if (event.text.unicode < 128) {
                        // if press backspace
                        if (event.text.unicode == Keybinds::DeleteCharacter) {
                            Keybinds::DefaultBackspace(cursor);
                        }
                        // if pressed enter
                        else if (event.text.unicode == Keybinds::InsertNewLine) {
                            Keybinds::DefaultEnter(cursor);
                        }
                        // normal ascii
                        else {
                            Keybinds::DefaultInputAscii(cursor,event);
                            
                        }
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    Keybinds::DefaultUpArrow(cursor);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    Keybinds::DefaultDownArrow(cursor);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    Keybinds::DefaultLeftArrow(cursor);
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    Keybinds::DefaultRightArrow(cursor);
                }
            }
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            if (File::CurrentState == State::InputBox) {
                if (event.type == sf::Event::TextEntered) {
                    if (event.text.unicode < 128) {
                        // enter
                        if (event.text.unicode == 13) {
                            Keybinds::InputBoxEnter(*fileInput, cursor);
                        }
                        // backspace
                        else if (event.text.unicode == 8) {
                            Keybinds::InputBoxBackspace(*fileInput);
                        }
                        // input regular character
                        else {
                            Keybinds::InputBoxInputAscii(*fileInput, event);
                        }
                    }
                }
            }
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        }

        cursor.getCurrentLine().populateTextList(cursor.getCurrentLine().text);

        // std::cout << File::Content[cursor.getCurrentLine().lineNumber].text.getPosition().y << std::endl;

        float x = cursor.getCurrentLine().getWidth(cursor.lineIndex) + 10;
        float y = File::Content[cursor.getCurrentLine().lineNumber].text.getPosition().y;

        cursor.setPosition(sf::Vector2f(
            x,
            y)
        );
        
        File::Content[0].text.setPosition(10, File::YPadding);
        for (int i = 1; i < File::Content.size(); i++) {
            File::Content[i].text.setPosition(10, (File::Content[i].lineNumber) * File::YPadding);
        }

        // handle the cursor animation clock
        cursor.updateCursorAnimation();

        // clear the window with black color
        window->clear(sf::Color::Black);

        // draw everything here...
        for (auto item : File::Content) {
            window->draw(item.text);
        }

        cursor.setAnimationInterval(tempInterval);
        // shitty fix for a shitty bug that makes the cursor jump to x = 10 for 1 frame when deleting a line
        if (x == 10 && cursor.lineIndex != 0) {
            cursor.isVisible = false;
            cursor.setAnimationInterval(cursor.clock.getElapsedTime().asSeconds());
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

    //file.close();

    // delete pointers
    delete fileButton;
    delete fileInput;
    delete window;

    // write to "output.txt"
    File::WriteFileToOutput();

    return 0;
}