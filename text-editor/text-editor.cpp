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
#include "FileExplorer.h"

int main()
{
    // #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

    

    Keybinds::DeleteCharacter = 8;
    Keybinds::InsertNewLine = 13;

    // loads the default font
    Font::load();

    // load icon
    sf::Image icon;
    icon.loadFromFile("img/belp.png");
    

    // create the window
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(800, 600), "Text Editor",sf::Style::Default);

    window->setIcon(icon.getSize().x,icon.getSize().y,icon.getPixelsPtr());

    File::CurrentState = State::Default;

    Cursor cursor = Cursor(sf::Vector2f(10, File::YPadding), sf::Vector2f(15, 5));

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

    // run the program as long as the window is open
    while (window->isOpen())
    {
        window->setFramerateLimit(300);

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
                    File::CurrentState = State::NoInput;
                    File::LoadFile(FileExplorer::Open());
                    cursor.setLineNumber(0);
                    cursor.lineIndex = 0;
                    std::cout << File::Content[cursor.getCurrentLine().lineNumber].lineNumber << std::endl;
                }
            }

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            cursor.isVisible = true;
            if (File::CurrentState == State::Default) {

                if (event.type == sf::Event::TextEntered) {

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
        }

        cursor.getCurrentLine().populateTextList(cursor.getCurrentLine().text);

        File::Content[0].text.setPosition(10, File::YPadding);
        for (int i = 1; i < File::Content.size(); i++) {            
            File::Content[i].text.setPosition(10, (File::Content[i].lineNumber+1) * File::YPadding);
        }

        float x;
        if (cursor.getCurrentLine().getWidth(cursor.lineIndex) > 0) {
            x = cursor.getCurrentLine().getWidth(cursor.lineIndex)+13;
        }
        else {
            x = 10;
        }
        float y = File::Content[cursor.getCurrentLine().lineNumber].text.getPosition().y + 30;

        cursor.setPosition(sf::Vector2f(
            x,
            y
        ));

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

    //file.close();

    // delete pointers
    delete fileButton;
    delete fileInput;
    delete window;

    // write to "output.txt"
    File::WriteFileToOutput();

    return 0;
}