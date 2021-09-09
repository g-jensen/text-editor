#include "Config.h"

int Config::WindowWidth = 300;
int Config::WindowHeight = 300;

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

    

    Config::ThemePath = (std::string)json["THEME"];
}
