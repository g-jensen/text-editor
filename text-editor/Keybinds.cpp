#include "Keybinds.h"


std::unordered_map<sf::Uint32, std::string> Keybinds::ComboKeyCodes
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
sf::Uint32 Keybinds::DeleteSentence = 0;
sf::Uint32 Keybinds::InsertNewLine = 0;

sf::Uint32 Keybinds::CursorUp = 0;
sf::Uint32 Keybinds::CursorDown = 0;
sf::Uint32 Keybinds::CursorLeft = 0;
sf::Uint32 Keybinds::CursorRight = 0;


sf::Uint32 Keybinds::SaveFile = 0;
sf::Uint32 Keybinds::CloseWindow = 0;
sf::Uint32 Keybinds::ReloadConfig = 0;

void Keybinds::Load()
{
    std::string line;
    std::string file;
    std::ifstream myfile("keybinds.json");
    if (myfile.is_open())
    {
        while (getline(myfile, line)) {
            file += line + "\n";
        }
        file = file.substr(0, file.size() - 1);
        myfile.close();
    }
    nlohmann::json json = nlohmann::json::parse(file);


    Keybinds::DeleteCharacter = stoi((std::string)json["DELETE_CHAR"]);
    Keybinds::DeleteSentence = stoi((std::string)json["DELETE_SENTENCE"]);
    Keybinds::InsertNewLine = stoi((std::string)json["INSERT_NEWLINE"]);

    Keybinds::CursorUp = stoi((std::string)json["CURSOR_UP"]);
    Keybinds::CursorDown = stoi((std::string)json["CURSOR_DOWN"]);
    Keybinds::CursorLeft = stoi((std::string)json["CURSOR_LEFT"]);
    Keybinds::CursorRight = stoi((std::string)json["CURSOR_RIGHT"]);

    Keybinds::SaveFile = stoi((std::string)json["SAVE_FILE"]);
    Keybinds::CloseWindow = stoi((std::string)json["CLOSE_WINDOW"]);
    Keybinds::ReloadConfig = stoi((std::string)json["RELOAD_CONFIG"]);
}

void Keybinds::DefaultDeleteCharacter(Cursor& cursor)
{
    // if the line is empty
    if (cursor.getCurrentLine().isEmpty() && cursor.getCurrentLine().lineNumber != 0) {
        // delete the line
        File::Content->erase(File::Content->begin() + cursor.getCurrentLine().lineNumber);

        // decrement current line number
        cursor.decrementLine(1);

        // decrement every line's number past the empty line
        for (unsigned int i = cursor.getCurrentLine().lineNumber + 1; i < File::Content->size(); i++) {
            (*File::Content)[i].lineNumber--;
        }

        cursor.lineIndex = (*File::Content)[cursor.getCurrentLine().lineNumber].text.getString().getSize();
    }
    else {
        // delete a character
        if (cursor.lineIndex > 0) {
            (*File::Content)[cursor.getCurrentLine().lineNumber].deleteCharacter(cursor.lineIndex - 1);
            cursor.lineIndex--;
        }
        // move previous line onto above line
        else if ((*File::Content)[cursor.getCurrentLine().lineNumber].lineNumber > 0) {
            // std::cout << "chugnus" << std::endl;
            int previousLineSize = (*File::Content)[cursor.getCurrentLine().lineNumber].text.getString().getSize();
            // std::cout << previousLineSize << std::endl;
            (*File::Content)[cursor.getCurrentLine().lineNumber - 1].text.setString((*File::Content)[cursor.getCurrentLine().lineNumber - 1].text.getString() + (*File::Content)[cursor.getCurrentLine().lineNumber].text.getString());
            File::Content->erase(File::Content->begin() + cursor.getCurrentLine().lineNumber);

            cursor.lineIndex = (*File::Content)[cursor.getCurrentLine().lineNumber-1].text.getString().getSize() - previousLineSize;
            cursor.decrementLine(1);

            // decrement every line's number past the empty line
            for (unsigned int i = cursor.getCurrentLine().lineNumber + 1; i < File::Content->size(); i++) {
                (*File::Content)[i].lineNumber--;
            }
        }
    }
    cursor.getCurrentLine().populateTextList(cursor.getCurrentLine().text);
}

void Keybinds::DefaultInsertNewLine(Cursor& cursor)
{
    std::string secondHalf = (*File::Content)[cursor.getCurrentLine().lineNumber].text.getString().substring(cursor.lineIndex, (*File::Content)[cursor.getCurrentLine().lineNumber].text.getString().getSize());
    (*File::Content)[cursor.getCurrentLine().lineNumber].text.setString((*File::Content)[cursor.getCurrentLine().lineNumber].text.getString().substring(0,cursor.lineIndex));
    cursor.incrementLine(1);

    Line newLine = Line(secondHalf, cursor.getCurrentLine().lineNumber-1);
    File::Content->insert(File::Content->begin() + cursor.getCurrentLine().lineNumber, newLine);

    for (unsigned int i = cursor.getCurrentLine().lineNumber; i < File::Content->size(); i++) {
        (*File::Content)[i].lineNumber++;
    }
    cursor.getCurrentLine().populateTextList(cursor.getCurrentLine().text);
    cursor.lineIndex = 0;

    cursor.setPosition(sf::Vector2f(
        cursor.getCurrentLine().getWidth(cursor.lineIndex) + 10,
        (*File::Content)[cursor.getCurrentLine().lineNumber].text.getPosition().y)
    );
}

void Keybinds::DefaultInputAscii(Cursor& cursor, sf::Event event)
{
    std::string firstHalf = (*File::Content)[cursor.getCurrentLine().lineNumber].text.getString().toAnsiString().substr(0, cursor.lineIndex);
    std::string secondHalf = (*File::Content)[cursor.getCurrentLine().lineNumber].text.getString().toAnsiString().substr(cursor.lineIndex, (*File::Content)[cursor.getCurrentLine().lineNumber].text.getString().getSize());
    (*File::Content)[cursor.getCurrentLine().lineNumber].text.setString(firstHalf + static_cast<char>(event.text.unicode) + secondHalf);
    cursor.getCurrentLine().populateTextList(cursor.getCurrentLine().text);
    cursor.lineIndex++;
}

void Keybinds::DefaultCursorUp(Cursor& cursor)
{

    if ((unsigned int)cursor.lineIndex > (*File::Content)[cursor.getCurrentLine().lineNumber - 1].text.getString().getSize()) {
        cursor.lineIndex = (*File::Content)[cursor.getCurrentLine().lineNumber - 1].text.getString().getSize();
    }

    // decrement current line
    if (File::Content->size() > 0 && cursor.getCurrentLine().lineNumber != 0) {
        cursor.decrementLine(1);
    }
}

void Keybinds::DefaultCursorDown(Cursor& cursor)
{

    if ((unsigned int)cursor.lineIndex > (*File::Content)[cursor.getCurrentLine().lineNumber + 1].text.getString().getSize()) {
        cursor.lineIndex = (*File::Content)[cursor.getCurrentLine().lineNumber + 1].text.getString().getSize();
    }

    // increment current line
    if (File::Content->size() > 0 && (unsigned int)cursor.getCurrentLine().lineNumber < File::Content->size() - 1) {
        cursor.incrementLine(1);
    }
}

void Keybinds::DefaultCursorLeft(Cursor& cursor)
{
    if (cursor.lineIndex > 0) {
        cursor.lineIndex--;
    } else if (cursor.lineIndex == 0 && cursor.getCurrentLine().lineNumber > 0) {
        
        cursor.decrementLine(1);
        cursor.lineIndex = (*File::Content)[cursor.getCurrentLine().lineNumber].text.getString().getSize();
    }
}

void Keybinds::DefaultCursorRight(Cursor& cursor)
{
    if ((unsigned int)cursor.lineIndex < cursor.getCurrentLine().text.getString().getSize()) {
        cursor.lineIndex++;
    }
    else if ((unsigned int)cursor.lineIndex == cursor.getCurrentLine().text.getString().getSize() && (unsigned int)cursor.getCurrentLine().lineNumber < File::Content->size() - 1) {
        cursor.lineIndex = 0;
        cursor.incrementLine(1);
    }
}