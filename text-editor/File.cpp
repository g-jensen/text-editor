#include "File.h"

std::vector<Line> File::content = {};

float File::yPadding = 30.f;

void File::writeFileToOutput()
{
    std::ofstream file;
    file.open("output.txt");
    for (int i = 0; i < File::content.size(); i++) {
        if (i != File::content.size() - 1) {
            file << File::content[i].text.getString().toAnsiString() << std::endl;
        }
        else {
            file << File::content[i].text.getString().toAnsiString();
        }
    }
    file.close();
}
