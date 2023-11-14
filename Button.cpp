#include "stdafx.h"
#include "Button.h"

//constructors
Button::Button(float pos_x, float pos_y, float width, float height,
	sf::Color idle_color, sf::Color hover_color, 
	std::string text, sf::Font& font, unsigned character_size)
	: idleColor(idle_color), hoverColor(hover_color)
{
	this->shape.setPosition(pos_x, pos_y);
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setFillColor(this->idleColor);

	this->buttonText.setFont(font);
	this->buttonText.setString(text);
	this->buttonText.setCharacterSize(character_size);
	this->buttonText.setFillColor(sf::Color::White);

	//center text on button
	sf::FloatRect text_bounds = buttonText.getLocalBounds();
	this->buttonText.setOrigin(text_bounds.left + text_bounds.width / 2.f,
		text_bounds.top + text_bounds.height / 2.f);
	this->buttonText.setPosition(pos_x + width / 2.f, pos_y + height / 2.f);
}

Button::Button()
{
}

//getters
sf::FloatRect Button::getGlobalBounds()
{
	return shape.getGlobalBounds();
}

sf::Vector2f Button::getPosition()
{
	return shape.getPosition();
}

//public functions
bool Button::isMouseOver(const sf::Vector2f& mouse_pos)
{
	return shape.getGlobalBounds().contains(mouse_pos);
}

bool Button::isClicked(const sf::Vector2f& mouse_pos)
{
	return isMouseOver(mouse_pos) && sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void Button::draw(sf::RenderTarget& target, const sf::Vector2f& mouse_pos)
{

	if (isMouseOver(mouse_pos))
	{
		shape.setFillColor(this->hoverColor);
	}
	else
	{
		shape.setFillColor(this->idleColor);
	}

	target.draw(shape);
	target.draw(buttonText);
}
