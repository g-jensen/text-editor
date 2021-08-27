#pragma once
class Line;
#include <SFML/Graphics/Text.hpp>
#include <fstream>
#include "Line.h"
#include "State.h"

class File
{
public:
	static State CurrentState;
	static std::vector<Line> Content;
	static float YPadding;
	static void WriteFileToOutput();
};

