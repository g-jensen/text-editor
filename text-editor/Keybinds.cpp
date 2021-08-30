#include "Keybinds.h"

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
        }
        else if (File::Content[cursor.getCurrentLine().lineNumber].lineNumber > 0) {
            // std::cout << "chugnus" << std::endl;
            cursor.lineIndex = File::Content[cursor.getCurrentLine().lineNumber - 1].text.getString().getSize() + 1;
            File::Content[cursor.getCurrentLine().lineNumber - 1].text.setString(File::Content[cursor.getCurrentLine().lineNumber - 1].text.getString() + File::Content[cursor.getCurrentLine().lineNumber].text.getString());
            File::Content.erase(File::Content.begin() + cursor.getCurrentLine().lineNumber);

            cursor.decrementLine(1);
            // decrement every line's number past the empty line
            for (int i = cursor.getCurrentLine().lineNumber + 1; i < File::Content.size(); i++) {
                File::Content[i].lineNumber--;
            }
        }

        if (cursor.lineIndex > 0) {
            cursor.lineIndex--;
        }
    }
    cursor.getCurrentLine().populateTextList(cursor.getCurrentLine().text);
}

void Keybinds::DefaultEnter(Cursor& cursor)
{
    std::string secondHalf = File::Content[cursor.getCurrentLine().lineNumber].text.getString().substring(cursor.lineIndex,File::Content[cursor.getCurrentLine().lineNumber].text.getString().getSize());
    File::Content[cursor.getCurrentLine().lineNumber].text.setString(File::Content[cursor.getCurrentLine().lineNumber].text.getString().substring(0,cursor.lineIndex));
    cursor.incrementLine(1);
    File::Content.insert(File::Content.begin() + cursor.getCurrentLine().lineNumber, Line(secondHalf, cursor.getCurrentLine().lineNumber));
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
