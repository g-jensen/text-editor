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
}

void Keybinds::TextInputBackspace(TextInput& textInput)
{
    textInput.value.setString(textInput.value.getString().substring(0, textInput.value.getString().getSize() - 1));
}

void Keybinds::TextInputEnter(TextInput& textInput, Cursor& cursor)
{
    File::LoadFile((std::string)textInput.value.getString());
    cursor.setCurrentLine(Line(File::Content[0].text.getString(), 0));
    File::CurrentState = State::Default;
    textInput.isOpen = false;
}
