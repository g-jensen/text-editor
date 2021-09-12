#pragma once

#include "TextInput.h"
#include "Button.h"
#include "Theme.h"
#include "File.h"

class UIBuilder
{
public:
		
	static sf::Vector2f fileButtonSize;
	static sf::Vector2f settingsButtonSize;
	static sf::Vector2f snippitButtonSize;

	/// <summary>
	/// DEPRECATED | Change textInput to object with pre-defined values for a file input box
	/// </summary>
	/// <param name="textInput">Object that will be changed</param>
	static void buildFileInputBox(TextInput &textInput);
	/// <summary>
	/// Change button to object with pre-defined values for a file button
	/// </summary>
	/// <param name="button">Object that will be changed</param>
	static void buildFileButton(Button& button);
	/// <summary>
	/// Change button to object with pre-defined values for a settings button
	/// </summary>
	/// <param name="button">Object that will be changed</param>
	static void buildSettingsButton(Button& button);
	/// <summary>
	/// Change button to object with pre-defined values for a snippits button
	/// </summary>
	/// <param name="button">Object that will be changed</param>
	static void buildSnippitsButton(Button& button);
	/// <summary>
	/// DEPRECATED | Change button to object with pre-defined values for an exit button
	/// </summary>
	/// <param name="button">Object that will be changed</param>
	static void buildExitButton(Button& button);
};

