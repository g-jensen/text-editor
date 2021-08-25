#include "Line.h"

Line::Line(std::string content, int lineNumber)
{
	Font::load();
	this->text.setFont(Font::defaultFont);
	this->text.setString(content);
	this->lineNumber = lineNumber;
}
