#pragma once
#include "Shared.h"
class Text{
	sf::Text text;
	sf::Font font;
	sf::Vector2u position;
	sf::RenderWindow * window;
	sf::Vector2f ratio;
	sf::RectangleShape background;
	unsigned int font_size=30;
public:
	Text(string tex, sf::RenderWindow * win, sf::Vector2f rat, sf::Vector2u pos, unsigned int font_s=30){
		font_size = font_s;
		position = pos;
		window = win;
		ratio = rat;
		if (!font.loadFromFile("Font/Germania.otf")) {
			window->close();
			std::cout << "error with font file" << std::endl;
			std::cin.ignore();
			exit(-1);
		}
		text.setFont(font);
		text.setString(tex);
		text.setCharacterSize(font_size);
		text.setFillColor(sf::Color::Black);
		text.setPosition(sf::Vector2f(position.x+4,position.y));
		background.setFillColor(sf::Color::White);
		background.setPosition(sf::Vector2f(position));
		background.setSize(sf::Vector2f(tex.length()*font_size*0.6, font_size+15));
		text.setScale(ratio.x, ratio.y);
		background.setScale(ratio.x, ratio.y);
	}
	~Text()
	{
	}
	void draw()const {
		window->draw(background);
		window->draw(text);
	}
	void set_text(string x) {
		text.setString(x);
		background.setSize(sf::Vector2f(x.length()*font_size*0.6, font_size + 15));
	}
	sf::Vector2u r_position()const { return position; }
	void set_position(const sf::Vector2u & x) { position = x; }
};

