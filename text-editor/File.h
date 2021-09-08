#pragma once
class Line;
#include <SFML/Graphics/Text.hpp>
#include <fstream>
#include "Line.h"
#include "State.h"
#include <iostream>
#include "Cursor.h"

class File
{
public:
	static State CurrentState;
	static std::vector<Line> Content;
	static std::vector<std::string> DeleteBreaks;
	static float YPadding;
	static void WriteFileToOutput();
	static void LoadFile(std::string path);
};

