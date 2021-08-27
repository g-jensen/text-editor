#include "File.h"

State File::CurrentState = State::Default;

std::vector<Line> File::Content = {};

float File::YPadding = 30.f;

void File::WriteFileToOutput()
{
    std::ofstream file;
    file.open("output.txt");
    for (int i = 0; i < File::Content.size(); i++) {
        if (i != File::Content.size() - 1) {
            file << File::Content[i].text.getString().toAnsiString() << std::endl;
        }
        else {
            file << File::Content[i].text.getString().toAnsiString();
        }
    }
    file.close();
}