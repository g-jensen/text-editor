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
	static sf::Uint32 DeleteSentence;
	static sf::Uint32 InsertNewLine;
	static sf::Uint32 CursorUp;
	static sf::Uint32 CursorDown;
	static sf::Uint32 CursorLeft;
	static sf::Uint32 CursorRight;

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

