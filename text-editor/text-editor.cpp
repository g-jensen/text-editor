#include <SFML/Graphics.hpp>
#include <iostream>
#include <ostream>
#include <unordered_map>

#include "text-editor.h"

bool stringContains(std::string s, std::vector<std::string> v) {
    for (auto& i : v) {
        if (s == i) {
            return true;
        }
    }
    return false;
}


int main()
{
    // #pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")

    // load config.json
    Config::Load();
    Keybinds::DeleteCharacter = Config::DeleteCharacter;
    Keybinds::DeleteSentence = Config::DeleteSentence;
    Keybinds::InsertNewLine = Config::InsertNewLine;
    Keybinds::CursorUp = Config::CursorUp;
    Keybinds::CursorDown = Config::CursorDown;
    Keybinds::CursorLeft = Config::CursorLeft;
    Keybinds::CursorRight = Config::CursorRight;


    // load theme
    Theme::Load();

    // loads the default font
    Font::load();

    // load icon
    sf::Image icon;
    icon.loadFromFile("img/belp.png");
    

    // create the window
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(Config::WindowWidth, Config::WindowHeight), "Text Editor",sf::Style::Default);

    window->setIcon(icon.getSize().x,icon.getSize().y,icon.getPixelsPtr());

    File::CurrentState = State::Default;

    Cursor cursor = Cursor(sf::Vector2f(10, File::YPadding), sf::Vector2f(15, 5));
    cursor.setFillColor(Theme::cursorColor);

    // initialize first line of file
    File::Content.push_back(Line("",0));
    cursor.setCurrentLine(File::Content[0]);

    // make top-left file button
    Button* fileButton = new Button();
    UIBuilder::buildFileButton(*fileButton);

    Button* settingsButton = new Button();
    UIBuilder::buildSettingsButton(*settingsButton);

    cursor.lineIndex = 0;

    window->setFramerateLimit(300);

    /*for (auto& i : File::DeleteBreaks) {
        std::cout << i << " , ";
    }*/

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
                }
            }

            // handle hovering over settingsButton
            if (UIHover::ButtonHover(*settingsButton, *window)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    SettingsMenu::Open(200, 200);
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
                        // ctrl + backspace
                        else if (event.text.unicode == Keybinds::DeleteSentence) {
                            // std::string string = cursor.getCurrentLine().text.getString().toAnsiString();
                            if (cursor.lineIndex == 0) {
                                Keybinds::DefaultBackspace(cursor);
                            }
                            else if (stringContains(std::string(1, cursor.getCurrentLine().text.getString().toAnsiString()[cursor.lineIndex - 1]), File::DeleteBreaks)) {
                                Keybinds::DefaultBackspace(cursor);
                            }
                            else {
                                for (int i = cursor.lineIndex - 1; i >= 0; i--) {
                                    if (!stringContains(std::string(1, cursor.getCurrentLine().text.getString().toAnsiString()[i]), File::DeleteBreaks)) {
                                        Keybinds::DefaultBackspace(cursor);
                                    }
                                    else {
                                        break;
                                    }
                                }
                            }
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
                else if (event.type == sf::Event::KeyPressed) {
                    if (event.text.unicode == Keybinds::CursorUp) {
                        Keybinds::DefaultUpArrow(cursor);
                    }
                    else if (event.text.unicode == Keybinds::CursorDown) {
                        Keybinds::DefaultDownArrow(cursor);
                    }
                    else if (event.text.unicode == Keybinds::CursorLeft) {
                        Keybinds::DefaultLeftArrow(cursor);
                    }
                    else if (event.text.unicode == Keybinds::CursorRight) {
                        Keybinds::DefaultRightArrow(cursor);
                    }
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
        window->clear(Theme::backgroundColor);

        // draw everything here...
        for (auto item : File::Content) {
            item.text.setFillColor(Theme::textColor);
            window->draw(item.text);
        }

        if (cursor.isVisible) {
            window->draw(cursor);
        }

        fileButton->draw(window);
        settingsButton->draw(window);
        
        // end the current frame
        window->display();
    }

    //file.close();

    // delete pointers
    delete fileButton;
    delete settingsButton;
    delete window;

    // write to "output.txt"
    File::WriteFileToOutput();

    return 0;
}