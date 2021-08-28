#include "Line.h"

Line::Line(std::string content, int lineNumber)
{
	Font::load();
	this->text.setFont(Font::defaultFont);
	this->text.setString(content);
	this->lineNumber = lineNumber;
}

Line::Line()
{
	lineNumber = 0;
}

bool Line::isEmpty()
{
	return this->text.getString().getSize() == 0;
}

void Line::deleteEndCharacter()
{
	this->text.setString(this->text.getString().substring(0, this->text.getString().getSize() - 1));

}
