#include "Keybinds.h"


std::unordered_map<sf::Uint32,  std::string> Keybinds::ComboKeyCodes
{    
    {17,"Ctrl + Q"},
    {23,"Ctrl + W"},
    {5,"Ctrl + E"},
    {18,"Ctrl + R"},
    {20,"Ctrl + T"},
    {25,"Ctrl + Y"},
    {21,"Ctrl + U"},
    {9,"Ctrl + I"},
    {15,"Ctrl + O"},
    {16,"Ctrl + P"},
    {1,"Ctrl + A"},
    {19,"Ctrl + S"},
    {4,"Ctrl + D"},
    {6,"Ctrl + F"},
    {7,"Ctrl + G"},
    {8,"Ctrl + H"},
    {10,"Ctrl + J"},
    {11,"Ctrl + K"},
    {12,"Ctrl + L"},
    {26,"Ctrl + Z"},
    {24,"Ctrl + X"},
    {3,"Ctrl + C"},
    {22,"Ctrl + V"},
    {2,"Ctrl + B"},
    {14,"Ctrl + N"},
    {13,"Ctrl + M"},
};

sf::Uint32 Keybinds::DeleteCharacter = 0;
sf::Uint32 Keybinds::InsertNewLine = 0;

sf::Uint32 CursorUp = 0;
sf::Uint32 CursorDown = 0;
sf::Uint32 CursorLeft = 0;
sf::Uint32 CursorRight = 0;

sf::Uint32 CtrlQ = 0;
sf::Uint32 CtrlW = 0;
sf::Uint32 CtrlE = 0;
sf::Uint32 CtrlR = 0;
sf::Uint32 CtrlT = 0;
sf::Uint32 CtrlY = 0;
sf::Uint32 CtrlU = 0;
sf::Uint32 CtrlI = 0;
sf::Uint32 CtrlO = 0;
sf::Uint32 CtrlP = 0;
sf::Uint32 CtrlA = 0;
sf::Uint32 CtrlS = 0;
sf::Uint32 CtrlD = 0;
sf::Uint32 CtrlF = 0;
sf::Uint32 CtrlG = 0;
sf::Uint32 CtrlH = 0;
sf::Uint32 CtrlJ = 0;
sf::Uint32 CtrlK = 0;
sf::Uint32 CtrlL = 0;
sf::Uint32 CtrlZ = 0;
sf::Uint32 CtrlX = 0;
sf::Uint32 CtrlC = 0;
sf::Uint32 CtrlV = 0;
sf::Uint32 CtrlB = 0;
sf::Uint32 CtrlN = 0;
sf::Uint32 CtrlM = 0;

void Keybinds::DefaultBackspace(Cursor& cursor)
{
    // if the line is empty
    if (cursor.getCurrentLine().isEmpty() && cursor.getCurrentLine().lineNumber != 0) {
        // delete the line
        File::Content.erase(File::Content.begin() + cursor.getCurrentLine().lineNumber);

        // decrement current line number
        cursor.decrementLine(1);

        // decrement every line's number past the empty line
        for (int i = cursor.getCurrentLine().lineNumber + 1; i < File::Content.size(); i++) {
            File::Content[i].lineNumber--;
        }

        cursor.lineIndex = File::Content[cursor.getCurrentLine().lineNumber].text.getString().getSize();
    }
    else {
        // delete a character
        if (cursor.lineIndex > 0) {
            File::Content[cursor.getCurrentLine().lineNumber].deleteCharacter(cursor.lineIndex - 1);
            cursor.lineIndex--;
        }
        else if (File::Content[cursor.getCurrentLine().lineNumber].lineNumber > 0) {
            // std::cout << "chugnus" << std::endl;
            int previousLineSize = File::Content[cursor.getCurrentLine().lineNumber].text.getString().getSize();
            // std::cout << previousLineSize << std::endl;
            File::Content[cursor.getCurrentLine().lineNumber - 1].text.setString(File::Content[cursor.getCurrentLine().lineNumber - 1].text.getString() + File::Content[cursor.getCurrentLine().lineNumber].text.getString());
            File::Content.erase(File::Content.begin() + cursor.getCurrentLine().lineNumber);

            cursor.decrementLine(1);
            
            cursor.lineIndex = File::Content[cursor.getCurrentLine().lineNumber].text.getString().getSize() - previousLineSize;
            std::cout << cursor.lineIndex << std::endl;

            //cursor.lineIndex += 2;
            // decrement every line's number past the empty line
            for (int i = cursor.getCurrentLine().lineNumber + 1; i < File::Content.size(); i++) {
                File::Content[i].lineNumber--;
            }

        }
    }
    cursor.getCurrentLine().populateTextList(cursor.getCurrentLine().text);
}

void Keybinds::DefaultEnter(Cursor& cursor)
{
    std::string secondHalf = File::Content[cursor.getCurrentLine().lineNumber].text.getString().substring(cursor.lineIndex,File::Content[cursor.getCurrentLine().lineNumber].text.getString().getSize());
    File::Content[cursor.getCurrentLine().lineNumber].text.setString(File::Content[cursor.getCurrentLine().lineNumber].text.getString().substring(0,cursor.lineIndex));
    cursor.incrementLine(1);

    Line newLine = Line(secondHalf, cursor.getCurrentLine().lineNumber);
    newLine.text.setPosition(10,(cursor.getCurrentLine().lineNumber+1) * File::YPadding);
    File::Content.insert(File::Content.begin() + cursor.getCurrentLine().lineNumber, newLine);

    for (int i = cursor.getCurrentLine().lineNumber; i < File::Content.size(); i++) {
        File::Content[i].lineNumber++;
    }
    cursor.getCurrentLine().populateTextList(cursor.getCurrentLine().text);
    cursor.lineIndex = 0;
}

void Keybinds::DefaultInputAscii(Cursor& cursor, sf::Event event)
{
    std::string firstHalf = File::Content[cursor.getCurrentLine().lineNumber].text.getString().toAnsiString().substr(0, cursor.lineIndex);
    std::string secondHalf = File::Content[cursor.getCurrentLine().lineNumber].text.getString().toAnsiString().substr(cursor.lineIndex, File::Content[cursor.getCurrentLine().lineNumber].text.getString().getSize());
    File::Content[cursor.getCurrentLine().lineNumber].text.setString(firstHalf + static_cast<char>(event.text.unicode) + secondHalf);
    cursor.getCurrentLine().populateTextList(cursor.getCurrentLine().text);
    cursor.lineIndex++;
}

void Keybinds::DefaultUpArrow(Cursor& cursor)
{
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

void Keybinds::DefaultDownArrow(Cursor& cursor)
{
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

void Keybinds::DefaultLeftArrow(Cursor& cursor)
{
    cursor.resetCursorAnimation();
    if (cursor.lineIndex > 0) {
        cursor.lineIndex--;
    }
}

void Keybinds::DefaultRightArrow(Cursor& cursor)
{
    cursor.resetCursorAnimation();
    if (cursor.lineIndex < cursor.getCurrentLine().text.getString().getSize()) {
        cursor.lineIndex++;
    }
}

void Keybinds::InputBoxBackspace(TextInput& textInput)
{
    textInput.value.setString(textInput.value.getString().substring(0, textInput.value.getString().getSize() - 1));
}

void Keybinds::InputBoxEnter(TextInput& textInput, Cursor& cursor)
{
    File::LoadFile((std::string)textInput.value.getString());
    cursor.setCurrentLine(Line(File::Content[0].text.getString(), 0));
    File::CurrentState = State::Default;
    textInput.isOpen = false;
}

void Keybinds::InputBoxInputAscii(TextInput& textInput, sf::Event event)
{
    textInput.value.setString(textInput.value.getString() + static_cast<char>(event.text.unicode));
}
