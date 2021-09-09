#include "Config.h"

int Config::WindowWidth = 300;
int Config::WindowHeight = 300;
int Config::DeleteCharacter = 0;
int Config::DeleteSentence = 0;
int Config::InsertNewLine = 0;

int Config::CursorUp = 0;
int Config::CursorDown = 0;
int Config::CursorLeft = 0;
int Config::CursorRight = 0;

std::string Config::ThemePath = "";

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

    Config::DeleteCharacter = stoi((std::string)json["DELETE_CHAR"]);
    Config::DeleteSentence = stoi((std::string)json["DELETE_SENTENCE"]);
    Config::InsertNewLine = stoi((std::string)json["INSERT_NEWLINE"]);

    Config::CursorUp = stoi((std::string)json["CURSOR_UP"]);
    Config::CursorDown = stoi((std::string)json["CURSOR_DOWN"]);
    Config::CursorLeft = stoi((std::string)json["CURSOR_LEFT"]);
    Config::CursorRight = stoi((std::string)json["CURSOR_RIGHT"]);

    Config::ThemePath = (std::string)json["THEME"];
}
