#include "Config.h"

int Config::WindowWidth = 300;
int Config::WindowHeight = 300;

void Config::Load()
{
    std::string line;
    std::string file;
    std::ifstream myfile("config.json");
    if (myfile.is_open())
    {
        while (getline(myfile, line)) {
            file += line + "\n";
        }
        file = file.substr(0,file.size()-1);
        myfile.close();
    }
    nlohmann::json json = nlohmann::json::parse(file);

    // set vars
    Config::WindowHeight = stoi((std::string)json["WINDOW_HEIGHT"]);
    Config::WindowWidth = stoi((std::string)json["WINDOW_WIDTH"]);

    Keybinds::DeleteCharacter = stoi((std::string)json["DELETE_CHAR"]);
    Keybinds::DeleteSentence = stoi((std::string)json["DELETE_SENTENCE"]);
    Keybinds::InsertNewLine = stoi((std::string)json["INSERT_NEWLINE"]);

    Keybinds::CursorUp = stoi((std::string)json["CURSOR_UP"]);
    Keybinds::CursorDown = stoi((std::string)json["CURSOR_DOWN"]);
    Keybinds::CursorLeft = stoi((std::string)json["CURSOR_LEFT"]);
    Keybinds::CursorRight = stoi((std::string)json["CURSOR_RIGHT"]);



}
