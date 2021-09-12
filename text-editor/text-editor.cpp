/*
    * Minimal-style text editor by Greg Jensen:
        - https://github.com/g-jensen/text-editor

    * Rendering library used:
        - https://www.sfml-dev.org/
        - https://github.com/SFML/SFML

    * JSON parsing library used:
        - https://github.com/nlohmann/json
*/

#include <iostream>
#include <ostream>
#include <unordered_map>

#include <SFML/Graphics.hpp>
#include "text-editor.h"

bool isContained(std::string s, std::vector<std::string> v) {
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

    // load keybinds.json
    Keybinds::Load();

    // load theme
    Theme::Load();

    // loads the default font
    Font::load();

    // load icon
    sf::Image icon;
    icon.loadFromFile("img/belp.png");
    

    // create the window
    File::window = new sf::RenderWindow(sf::VideoMode(Config::WindowWidth, Config::WindowHeight), "Text Editor",sf::Style::Default);

    File::window->setIcon(icon.getSize().x,icon.getSize().y,icon.getPixelsPtr());

    File::CurrentState = State::Default;

    Cursor cursor = Cursor(sf::Vector2f(10, File::YPadding), sf::Vector2f(15, 5));
    cursor.setFillColor(Theme::cursorColor);

    // initialize first line of file
    (*File::Content).push_back(Line("",0));
    cursor.setCurrentLine((*File::Content)[0]);

    // make top-left file button
    Button* fileButton = new Button();
    UIBuilder::buildFileButton(*fileButton);

    // make settings button
    Button* settingsButton = new Button();
    UIBuilder::buildSettingsButton(*settingsButton);

    // make snippits button
    Button* snippitButton = new Button();
    UIBuilder::buildSnippitsButton(*snippitButton);

    cursor.lineIndex = 0;

    File::window->setFramerateLimit(300);

    // run the program as long as the window is open
    while (File::window->isOpen())
    {

        // std::cout << FileExplorer::GetClipboard() << std::endl;

        File::window->setFramerateLimit(300);

        // keep cursor.getCurrentLine up to date with the actual current line 
        // (note: cursor.getCurrentLine returns a copy as opposed to File::Content[cursor.getCurrentLine.lineNumber])
        cursor.setCurrentLine(Line((*File::Content)[cursor.getCurrentLine().lineNumber].text.getString(), cursor.getCurrentLine().lineNumber));

        sf::Event event;
        while (File::window->pollEvent(event))
        {

            if (event.type == sf::Event::Resized)
            {
                // update the view to the new size of the window
                sf::FloatRect visibleArea(0.f, 0.f, (float)event.size.width, (float)event.size.height);
                File::window->setView(sf::View(visibleArea));
            }

            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed) {
                File::window->close();
            }

            // handle hovering over fileButton
            if (UIHover::ButtonHover(*fileButton, *File::window)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    File::CurrentState = State::NoInput;
                    File::LoadFile(FileExplorer::Open());
                    std::filesystem::current_path(File::programPath);
                    cursor.setLineNumber(0);
                    cursor.lineIndex = 0;
                }
            }

            // handle hovering over settingsButton
            if (UIHover::ButtonHover(*settingsButton, *File::window)) {
                if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                    SettingsMenu::Open(200, 200);
                }
            }

            if (UIHover::ButtonHover(*snippitButton,*File::window)) {}

            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
            cursor.isVisible = true;
            if (File::CurrentState == State::Default) {
                if (event.type == sf::Event::TextEntered) {
                    std::cout << event.text.unicode << std::endl;
                    // if press backspace
                    if (event.text.unicode == Keybinds::DeleteCharacter) {
                        Keybinds::DefaultDeleteCharacter(cursor);
                    }
                    // ctrl + backspace
                    else if (event.text.unicode == Keybinds::DeleteSentence) {
                        // std::string string = cursor.getCurrentLine().text.getString().toAnsiString();
                        if (cursor.lineIndex == 0) {
                            Keybinds::DefaultDeleteCharacter(cursor);
                        }
                        else if (isContained(std::string(1, cursor.getCurrentLine().text.getString().toAnsiString()[cursor.lineIndex - 1]), File::DeleteBreaks)) {
                            Keybinds::DefaultDeleteCharacter(cursor);
                        }
                        else {
                            for (int i = cursor.lineIndex - 1; i >= 0; i--) {
                                if (!isContained(std::string(1, cursor.getCurrentLine().text.getString().toAnsiString()[i]), File::DeleteBreaks)) {
                                    Keybinds::DefaultDeleteCharacter(cursor);
                                }
                                else {
                                    break;
                                }
                            }
                        }
                    }
                    // if pressed enter
                    else if (event.text.unicode == Keybinds::InsertNewLine) {
                        Keybinds::DefaultInsertNewLine(cursor);
                    } 
                    else if (event.text.unicode == Keybinds::SaveFile) {
                        File::WriteFileToOutput();
                    }
                    else if (event.text.unicode == Keybinds::CloseWindow) {
                        File::window->close();
                    }
                    else if (event.text.unicode == Keybinds::ReloadConfig) {
                        Config::Load();
                        Keybinds::Load();
                        Theme::Load();
                        Font::load();
                        UIBuilder::buildFileButton(*fileButton);
                        UIBuilder::buildSettingsButton(*settingsButton);
                        UIBuilder::buildSnippitsButton(*snippitButton);
                        cursor.setFillColor(Theme::cursorColor);
                    }
                    else if (event.text.unicode == Keybinds::PasteClipboard) {
                        std::string clipboard = FileExplorer::GetClipboard();
                        std::string firstHalf = (*File::Content)[cursor.getCurrentLine().lineNumber].text.getString().toAnsiString().substr(0, cursor.lineIndex);
                        std::string secondHalf = (*File::Content)[cursor.getCurrentLine().lineNumber].text.getString().toAnsiString().substr(cursor.lineIndex, (*File::Content)[cursor.getCurrentLine().lineNumber].text.getString().getSize());
                        (*File::Content)[cursor.getCurrentLine().lineNumber].text.setString(firstHalf + clipboard + secondHalf);
                        cursor.getCurrentLine().populateTextList(cursor.getCurrentLine().text);
                        cursor.lineIndex += clipboard.size();
                    }
                    // normal ascii
                    else {
                        Keybinds::DefaultInputAscii(cursor,event);
                    }
                    
                }
                else if (event.type == sf::Event::KeyPressed) {
                    // std::cout << event.text.unicode << std::endl;
                    if (event.text.unicode == Keybinds::CursorUp) {
                        Keybinds::DefaultCursorUp(cursor);
                    }
                    else if (event.text.unicode == Keybinds::CursorDown) {
                        Keybinds::DefaultCursorDown(cursor);
                    }
                    else if (event.text.unicode == Keybinds::CursorLeft) {
                        Keybinds::DefaultCursorLeft(cursor);
                    }
                    else if (event.text.unicode == Keybinds::CursorRight) {
                        Keybinds::DefaultCursorRight(cursor);
                    }
                }
            }
            //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        }

        cursor.getCurrentLine().populateTextList(cursor.getCurrentLine().text);

        (*File::Content)[0].text.setPosition(10, File::YPadding);
        for (unsigned int i = 1; i < File::Content->size(); i++) {
            (*File::Content)[i].text.setPosition(10, ((*File::Content)[i].lineNumber+1) * File::YPadding);
        }

        float x;
        if (cursor.getCurrentLine().getWidth(cursor.lineIndex) > 0) {
            x = cursor.getCurrentLine().getWidth(cursor.lineIndex)+13;
        }
        else {
            x = 10;
        }
        float y = (*File::Content)[cursor.getCurrentLine().lineNumber].text.getPosition().y + 30;

        cursor.setPosition(sf::Vector2f(
            x,
            y
        ));

        // clear the window with black color
        File::window->clear(Theme::backgroundColor);

        // draw everything here...
        for (auto &item : *File::Content) {
            item.text.setFillColor(Theme::textColor);
            File::window->draw(item.text);
        }

        if (cursor.isVisible) {
            File::window->draw(cursor);
        }

        fileButton->draw(File::window);
        settingsButton->draw(File::window);
        snippitButton->draw(File::window);
        
        // end the current frame
        File::window->display();
    }

    // delete pointers
    delete fileButton;
    delete settingsButton;
    delete snippitButton;
    delete File::window;

    // write to "output.txt"
    File::WriteFileToOutput();

    delete File::Content;

    return 0;
}