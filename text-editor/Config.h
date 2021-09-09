#pragma once

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

class Config
{
public:
	static void Load();
	static int WindowWidth;
	static int WindowHeight;
	static std::string ThemePath;

    static int DeleteCharacter;
    static int DeleteSentence;
    static int InsertNewLine;

    static int CursorUp;
    static int CursorDown;
    static int CursorLeft;
    static int CursorRight;
};

