#pragma once

#include "TextInput.h"

class UIBuilder
{
public:
	/// <summary>
	/// Change textInput to object with pre-defined values for a file input box
	/// </summary>
	/// <param name="textInput">Object that will be changed</param>
	static void buildFileInputBox(TextInput* textInput);
};

