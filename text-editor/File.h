#pragma once
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <fstream>
#include "Line.h"
#include "State.h"
#include <iostream>
#include "Cursor.h"
#include <filesystem>

class File
{
public:
	/// <summary>
	/// Path of the .exe
	/// </summary>
	static std::filesystem::path programPath;

	/// <summary>
	/// Path to the file that is currently open
	/// </summary>
	static std::string openFile;

	/// <summary>
	/// Main window
	/// </summary>
	static sf::RenderWindow* window;

	/// <summary>
	/// Enum of current state
	/// </summary>
	static State CurrentState;

	/// <summary>
	/// List of all the lines in the file
	/// </summary>
	static std::vector<Line>* Content;
	
	/// <summary>
	/// List of all the characters that will stop a word delete
	/// </summary>
	static std::vector<std::string> DeleteBreaks;

	/// <summary>
	/// Vertical padding of lines
	/// </summary>
	static float YPadding;

	/// <summary>
	/// Writes File::Content to output.txt
	/// </summary>
	static void WriteFileToOutput();

	/// <summary>
	/// Loads a file and changes File::Content to the file contents
	/// </summary>
	/// <param name="path">Path of the file</param>
	static void LoadFile(std::string path);
};

