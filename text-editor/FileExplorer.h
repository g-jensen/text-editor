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
	static std::string Open();
};

