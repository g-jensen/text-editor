#pragma once

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include "IDrawable.h"

/// <summary>
/// Creates UI Buttons
/// </summary>
class Button : public IDrawable
{
public:

	Button(sf::Vector2f position, sf::Vector2f size);

	/// <summary>
	/// Leaves all member variables uninitialized
	/// </summary>
	Button();
	
	/// <summary>
	/// Draws the button onto the screen for the frame
	/// </summary>
	/// <param name="window">The window to draw to</param>
	void draw(sf::RenderWindow* window);

	/// <summary>
	/// Checks if a given position is inside the button
	/// </summary>
	/// <param name="position">The position to check</param>
	/// <returns></returns>
	bool contains(sf::Vector2i position);

	/// <summary>
	/// Text displayed on the button
	/// </summary>
	sf::Text label;
};

