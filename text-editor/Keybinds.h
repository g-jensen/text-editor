#pragma once

#include "Cursor.h"
#include "File.h"
#include "TextInput.h"
#include <SFML/Window/Event.hpp>

class Keybinds
{
public:
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

