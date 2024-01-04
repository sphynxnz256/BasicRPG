#pragma once
class Button
{
private:
	//private variables
	sf::RectangleShape shape;
	sf::Color idleColor;
	sf::Color hoverColor;
	sf::Text buttonText;

public:
	//constructors
	Button(float position_x, float position_y, float width, float height,
		sf::Color idle_color, sf::Color hover_color,
		std::string text, sf::Font& font, unsigned character_size);

	Button();

	//getters
	sf::FloatRect getGlobalBounds();
	sf::Vector2f getPosition();

	//public functions
	bool isMouseOver(const sf::Vector2f& mouse_pos);
	bool isClicked(const sf::Vector2f& mouse_pos);

	void render(sf::RenderTarget& target, const sf::Vector2f& mouse_pos);
};

