#pragma once

#include "Cursor.h"
#include "File.h"
#include "TextInput.h"
#include <SFML/Window/Event.hpp>
#include <unordered_map>
#include <nlohmann/json.hpp>


class Keybinds
{
public:
	/// <summary>
	/// List of key combinations of ctrl + all letters of the alphabet
	/// </summary>
	static std::unordered_map<sf::Uint32,  std::string> ComboKeyCodes;

	///////////////////////////////////
	// Key codes for the respective functions
	static sf::Uint32 DeleteCharacter;
	static sf::Uint32 DeleteSentence;
	static sf::Uint32 InsertNewLine;
	static sf::Uint32 CursorUp;
	static sf::Uint32 CursorDown;
	static sf::Uint32 CursorLeft;
	static sf::Uint32 CursorRight;
	static sf::Uint32 SaveFile;
	///////////////////////////////////

	/// <summary>
	/// Loads keybinds from keybinds.json
	/// </summary>
	static void Load();

	/// <summary>
	/// Deletes a character in the default state
	/// </summary>
	static void DefaultDeleteCharacter(Cursor& cursor);
	/// <summary>
	/// Inserts a new line in the default state
	/// </summary>
	static void DefaultInsertNewLine(Cursor& cursor);
	/// <summary>
	/// Inputs an ascii character in the default state
	/// </summary>
	static void DefaultInputAscii(Cursor& cursor, sf::Event event);
	/// <summary>
	/// Moves the cursor up in the default state
	/// </summary>
	static void DefaultCursorUp(Cursor& cursor);
	/// <summary>
	/// Moves the cursor down in the default state
	/// </summary>
	static void DefaultCursorDown(Cursor& cursor);
	/// <summary>
	/// Moves the cursor left in the default state
	/// </summary>
	static void DefaultCursorLeft(Cursor& cursor);
	/// <summary>
	/// Moves the cursor right in the default state
	/// </summary>
	static void DefaultCursorRight(Cursor& cursor);
};

