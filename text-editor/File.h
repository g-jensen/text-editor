#pragma once
class Line;
#include <SFML/Graphics/Text.hpp>
#include <fstream>
#include "Line.h"

class File
{
public:
	static std::vector<Line> content;
	static float yPadding;
	static void writeFileToOutput();
};

