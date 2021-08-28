#pragma once

#include "Cursor.h"
#include "File.h"
#include "TextInput.h"

class Keybinds
{
public:
	static void DefaultBackspace(Cursor& cursor);
	static void DefaultEnter(Cursor& cursor);

	static void TextInputBackspace(TextInput& textInput);
	static void TextInputEnter(TextInput& textInput, Cursor& cursor);
};

