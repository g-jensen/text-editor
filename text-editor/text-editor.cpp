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

    cursor.lineIndex = 0;

    // just for printing
    int lineIndexPlaceholder = 0;

    window->setFramerateLimit(60);

    // run the program as long as the window is open
    while (window->isOpen())
    {
        window->setFramerateLimit(60);

        lineIndexPlaceholder = cursor.lineIndex;
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
                    File::CurrentState = State::TextInput;
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
                        if (event.text.unicode == 8) {
                            // delete one character
                            Keybinds::DefaultBackspace(cursor);
                            cursor.getCurrentLine().populateTextList(cursor.getCurrentLine().text);
                        }
                        // if pressed enter
                        else if (event.text.unicode == 13) {
                            Keybinds::DefaultEnter(cursor);
                            cursor.getCurrentLine().populateTextList(cursor.getCurrentLine().text);
                            cursor.lineIndex = 0;
                        }
                        // normal ascii
                        else {
                            // append whatever was typed
                            std::string firstHalf = File::Content[cursor.getCurrentLine().lineNumber].text.getString().toAnsiString().substr(0,cursor.lineIndex);
                            std::string secondHalf = File::Content[cursor.getCurrentLine().lineNumber].text.getString().toAnsiString().substr(cursor.lineIndex, File::Content[cursor.getCurrentLine().lineNumber].text.getString().getSize());
                            File::Content[cursor.getCurrentLine().lineNumber].text.setString(firstHalf + static_cast<char>(event.text.unicode) + secondHalf);
                            cursor.getCurrentLine().populateTextList(cursor.getCurrentLine().text);
                            cursor.lineIndex++;
                        }
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                    // handle the cursor animation clock
                    cursor.resetCursorAnimation();

                    if (cursor.getCurrentLine().text.getString().getSize() > File::Content[cursor.getCurrentLine().lineNumber - 1].text.getString().getSize()) {
                        cursor.lineIndex = File::Content[cursor.getCurrentLine().lineNumber - 1].text.getString().getSize();
                    }

                    // decrement current line
                    if (File::Content.size() > 0 && cursor.getCurrentLine().lineNumber != 0) {
                        cursor.decrementLine(1);
                    }

                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                    // handle the cursor animation clock
                    cursor.resetCursorAnimation();

                    if (cursor.getCurrentLine().text.getString().getSize() > File::Content[cursor.getCurrentLine().lineNumber + 1].text.getString().getSize()) {
                        cursor.lineIndex = File::Content[cursor.getCurrentLine().lineNumber + 1].text.getString().getSize();
                    }

                    // increment current line
                    if (File::Content.size() > 0 && cursor.getCurrentLine().lineNumber < File::Content.size() - 1) {
                        cursor.incrementLine(1);
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    cursor.resetCursorAnimation();
                    if (cursor.lineIndex > 0) {
                        cursor.lineIndex--;
                    }
                }
                else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    cursor.resetCursorAnimation();
                    if (cursor.lineIndex < cursor.getCurrentLine().text.getString().getSize()) {
                        cursor.lineIndex++;
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
        // change later to be better or something
        cursor.setPosition(sf::Vector2f(
            cursor.getCurrentLine().getWidth(cursor.lineIndex) + 10,
            File::Content[cursor.getCurrentLine().lineNumber].text.getPosition().y)
        );

        /*if (cursor.lineIndex != lineIndexPlaceholder) {
            std::cout << cursor.lineIndex << std::endl;
        }*/

        // handle the cursor animation clock
        cursor.updateCursorAnimation();

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