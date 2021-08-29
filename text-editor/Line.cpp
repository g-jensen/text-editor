#include "Line.h"

Line::Line(std::string content, int lineNumber)
{
	Font::load();
	this->text.setFont(Font::defaultFont);
	this->text.setString(content);
	this->lineNumber = lineNumber;

	Line::populateTextList(this->text);

}

Line::Line()
{
	lineNumber = 0;
}



bool Line::isEmpty()
{
	return this->text.getString().getSize() == 0;
}

void Line::deleteCharacter(int index)
{
	// std::cout << index << std::endl;
	if (this->text.getString().getSize() > 0) {
		if (index > 0) {
			std::string firstHalf = this->text.getString().substring(0, index);
			std::string secondHalf = this->text.getString().substring(index + 1, this->text.getString().getSize());
			this->text.setString(firstHalf + secondHalf);
		}
		else if (index == 0) {
			std::string secondHalf = this->text.getString().substring(1, this->text.getString().getSize());
			this->text.setString(secondHalf);
		}
	}
}

//void Line::deleteEndCharacter()
//{
//	this->text.setString(this->text.getString().substring(0, this->text.getString().getSize() - 1));
//
//}

void Line::populateTextList(sf::Text text)
{
	this->textList.clear();
	for (int i = 0; i < text.getString().getSize(); i++) {
		sf::Text t;
		t.setFont(Font::defaultFont);
		t.setString(text.getString().toAnsiString().substr(i, 1));
		this->textList.push_back(t);
	}
}

float Line::getWidth(int n)
{
	if (n > this->textList.size()) {
		float sum = 0.0f;
		sf::Text placeholder;
		placeholder.setFont(Font::defaultFont);
		for (int i = 0; i < this->textList.size(); i++) {
			placeholder.setString(placeholder.getString() + textList[i].getString());
		}
		sum = placeholder.getGlobalBounds().width;
		return sum;
	}
	else {
		float sum = 0.0f;
		sf::Text placeholder;
		placeholder.setFont(Font::defaultFont);
		for (int i = 0; i < n; i++) {
			placeholder.setString(placeholder.getString() + textList[i].getString());
		}
		sum = placeholder.getGlobalBounds().width;
		return sum;
	}
}
