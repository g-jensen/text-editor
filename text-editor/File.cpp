#include "File.h"

std::string File::openFile = "output.txt";

std::filesystem::path File::programPath = std::filesystem::current_path();

sf::RenderWindow* File::window = nullptr;

State File::CurrentState = State::Default;

std::vector<Line>* File::Content = new std::vector<Line>();

std::vector<std::string> File::DeleteBreaks = {
    ""," ", "`", "!", "@", "#", "$", "%", "^", "&", "*", "(", ")", "-", "=", "_", "+", "[" , "]", "{", "}", "\\", "|", ";", ":", "\'", "\"", ",", ".", "/", "<", ">", "?"
};

float File::YPadding = 30.f;

void File::WriteFileToOutput()
{
    std::ofstream file;
    file.open(File::openFile);
    for (unsigned int i = 0; i < File::Content->size(); i++) {
        if (i != File::Content->size() - 1) {
            file << (*File::Content)[i].text.getString().toAnsiString() << std::endl;
        }
        else {
            file << (*File::Content)[i].text.getString().toAnsiString();
        }
    }
    file.close();
}

void File::LoadFile(std::string path)
{
    std::ifstream myfile(path);
    std::string data;
    if (myfile.is_open())
    {
        File::Content->clear();
        int n = 0;
        while (std::getline(myfile, data))
        {
            Line line(data, n);
            File::Content->push_back(line);
            n++;
        }
        myfile.close();
    }
    else { std::cout << "Unable to open \"" + path + "\""; }
    if (File::Content->size() == 0) {
        File::Content->push_back(Line("",0));
    }
    File::openFile = path;
    File::window->setTitle("Text Editor - " + File::openFile);
}
