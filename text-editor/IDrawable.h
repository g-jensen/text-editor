#pragma once

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

/// <summary>
/// Interface for things that can be drawn
/// </summary>
class IDrawable : public sf::RectangleShape
{
public:
	/// <summary>
	/// Virtual method that draws the object onto the window
	/// </summary>
	/// <param name="window">Window to draw to</param>
	virtual void draw(sf::RenderWindow* window) = 0;
};

