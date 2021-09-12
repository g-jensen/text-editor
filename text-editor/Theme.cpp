#include "Theme.h"

std::string Theme::fontPath = "";
sf::Color Theme::backgroundColor = sf::Color(0, 0, 0);
sf::Color Theme::textColor = sf::Color(255, 255, 255);
sf::Color Theme::cursorColor = sf::Color(255, 255, 255);
sf::Color Theme::buttonFillColor = sf::Color(0, 0, 0);
sf::Color Theme::buttonHoverColor = sf::Color(105, 105, 105);
sf::Color Theme::buttonOutlineColor = sf::Color(148, 0, 211);

void Theme::Load()
{
    std::string line;
    std::string file;
    std::ifstream myfile(Config::ThemePath);
    if (myfile.is_open())
    {
        while (getline(myfile, line)) {
            file += line + "\n";
        }
        file = file.substr(0, file.size() - 1);
        myfile.close();
    }
    
    nlohmann::json json = nlohmann::json::parse(file);

    Theme::fontPath = (std::string)json["font"];

    Theme::backgroundColor = sf::Color(
        stoi((std::string)json["background-color"]["r"]),
        stoi((std::string)json["background-color"]["g"]),
        stoi((std::string)json["background-color"]["b"])
    );

    Theme::textColor = sf::Color(
        stoi((std::string)json["text-color"]["r"]),
        stoi((std::string)json["text-color"]["g"]),
        stoi((std::string)json["text-color"]["b"])
    );

    Theme::cursorColor = sf::Color(
        stoi((std::string)json["cursor-color"]["r"]),
        stoi((std::string)json["cursor-color"]["g"]),
        stoi((std::string)json["cursor-color"]["b"])
    );

    Theme::buttonFillColor = sf::Color(
        stoi((std::string)json["button-fill-color"]["r"]),
        stoi((std::string)json["button-fill-color"]["g"]),
        stoi((std::string)json["button-fill-color"]["b"])
    );

    Theme::buttonHoverColor = sf::Color(
        stoi((std::string)json["button-hover-color"]["r"]),
        stoi((std::string)json["button-hover-color"]["g"]),
        stoi((std::string)json["button-hover-color"]["b"])
    );

    Theme::buttonOutlineColor = sf::Color(
        stoi((std::string)json["button-outline-color"]["r"]),
        stoi((std::string)json["button-outline-color"]["g"]),
        stoi((std::string)json["button-outline-color"]["b"])
    );

}
