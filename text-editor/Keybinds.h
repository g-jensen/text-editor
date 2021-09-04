#pragma once

#include "Cursor.h"
#include "File.h"
#include "TextInput.h"
#include <SFML/Window/Event.hpp>
#include <unordered_map>

class Keybinds
{
public:

	static std::unordered_map<sf::Uint32,  std::string> ComboKeyCodes;

	static sf::Uint32 DeleteCharacter;
	static sf::Uint32 InsertNewLine;
	static sf::Uint32 CursorUp;
	static sf::Uint32 CursorDown;
	static sf::Uint32 CursorLeft;
	static sf::Uint32 CursorRight;

	static sf::Uint32 CtrlQ;
	static sf::Uint32 CtrlW;
	static sf::Uint32 CtrlE;
	static sf::Uint32 CtrlR;
	static sf::Uint32 CtrlT;
	static sf::Uint32 CtrlY;
	static sf::Uint32 CtrlU;
	static sf::Uint32 CtrlI;
	static sf::Uint32 CtrlO;
	static sf::Uint32 CtrlP;
	static sf::Uint32 CtrlA;
	static sf::Uint32 CtrlS;
	static sf::Uint32 CtrlD;
	static sf::Uint32 CtrlF;
	static sf::Uint32 CtrlG;
	static sf::Uint32 CtrlH;
	static sf::Uint32 CtrlJ;
	static sf::Uint32 CtrlK;
	static sf::Uint32 CtrlL;
	static sf::Uint32 CtrlZ;
	static sf::Uint32 CtrlX;
	static sf::Uint32 CtrlC;
	static sf::Uint32 CtrlV;
	static sf::Uint32 CtrlB;
	static sf::Uint32 CtrlN;
	static sf::Uint32 CtrlM;

	static void DefaultBackspace(Cursor& cursor);
	static void DefaultEnter(Cursor& cursor);
	static void DefaultInputAscii(Cursor& cursor, sf::Event event);
	static void DefaultUpArrow(Cursor& cursor);
	static void DefaultDownArrow(Cursor& cursor);
	static void DefaultLeftArrow(Cursor& cursor);
	static void DefaultRightArrow(Cursor& cursor);

	static void InputBoxBackspace(TextInput& textInput);
	static void InputBoxEnter(TextInput& textInput, Cursor& cursor);
	static void InputBoxInputAscii(TextInput& textInput, sf::Event event);
};

