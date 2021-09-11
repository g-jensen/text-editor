#pragma once

#include <iostream>
#include "File.h"
#include "Cursor.h"

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#include <string>

class FileExplorer
{
public:
	/// <summary>
	/// Opens the file explorer to choose a file
	/// </summary>
	/// <returns>Path to the file chosen</returns>
	static std::string Open();
};

