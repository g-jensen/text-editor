#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Clock.hpp>
#include "Line.h"
#include "File.h"

class Cursor : public sf::RectangleShape
{
public:
	Cursor(sf::Vector2f position, sf::Vector2f size);

	/// <summary>
	/// DEPRECATED | Timer used to keep track of animation timing for the cursor
	/// </summary>
	sf::Clock clock;

	/// <summary>
	/// bool to check if the cursor should render
	/// </summary>
	bool isVisible;

	/// <summary>
	/// Zero-indexed horizontal order of where the cursor is on the current line
	/// </summary>
	int lineIndex;

	/// <summary>
	/// DEPRECATED | Resets the clock timer for the animation
	/// </summary>
	void resetCursorAnimation();

	/// <summary>
	/// DEPRECATED | Changes isVisible depending on the animationInterval and the current clock timer
	/// </summary>
	void updateCursorAnimation();

	/// <summary>
	/// Change the vertical line number
	/// </summary>
	/// <param name="n">The line number</param>
	void setLineNumber(int n);

	/// <summary>
	/// Increases the current line number
	/// </summary>
	/// <param name="n">Amount to increase line number</param>
	void incrementLine(int n);

	/// <summary>
	/// Decreases the current line number
	/// </summary>
	/// <param name="n">Amount to decrease line number</param>
	void decrementLine(int n);

	/// <summary>
	/// Sets the current line to a new Line
	/// </summary>
	/// <param name="line">Line to replace the current line</param>
	void setCurrentLine(Line line);

	/// <summary>
	/// DEPRECATED | Sets the interval in which the cursor appears and disappears
	/// </summary>
	/// <param name="interval">Time in seconds</param>
	void setAnimationInterval(float interval);

	/// <summary>
	/// Get line object for the current line
	/// </summary>
	/// <returns>Line object of current line</returns>
	Line getCurrentLine();

	/// <summary>
	/// Get interval in which the cursor appears and disappears
	/// </summary>
	/// <returns>Time in seconds</returns>
	float getAnimationInterval();

private:
	Line currentLine;
	float animationInterval;
};

