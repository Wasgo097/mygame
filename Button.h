#pragma once
#include "Shared.h"
class Button{
	sf::Font font;
	sf::RectangleShape background;
	sf::Vector2u size;
	sf::Vector2u margin;
	sf::Text text;
	unsigned int font_size = 30;
	sf::RenderWindow * window;
	sf::Vector2f ratio;
public:
	Button(sf::RenderWindow * window, sf::Vector2f  ratio, string text ,  sf::Vector2u  margin,sf::Color outline=sf::Color::Black) {
		if (!font.loadFromFile("Font/Deutsch.ttf")) {
			std::cout << "Error with load font" << std::endl;
			exit(0);
		}
		else {
			this->window = window;
			this->ratio = ratio;
			this->margin = margin;
			this->size = sf::Vector2u(text.length()*font_size*0.65, font_size+10);
			this->text.setFont(font);
			this->text.setString(text);
			this->text.setCharacterSize(font_size);
			this->text.setPosition(sf::Vector2f(margin));
			this->text.setPosition(sf::Vector2f(this->margin.x+0.08*size.x,this->margin.y+2));
			this->text.setFillColor(sf::Color::Black);
			this->text.setScale(this->ratio.x, this->ratio.y);
			background.setPosition(sf::Vector2f(margin));
			background.setSize(sf::Vector2f(size));
			background.setFillColor(sf::Color::White);
			background.setOutlineColor(outline);
			background.setOutlineThickness(2);
			background.setScale(this->ratio.x, this->ratio.y);
		}
	}
	bool is_clicked(sf::Vector2i mouse) {
		if (mouse.x >= margin.x&&mouse.x <= (margin.x + size.x*ratio.x) && mouse.y >= margin.y&&mouse.y <= (margin.y + size.y*ratio.y)) return true;
		else return false;
	}
	bool is_target(sf::Vector2i mouse) {
		if (mouse.x>= margin.x&&mouse.x <= (margin.x + size.x*ratio.x)&&mouse.y>= margin.y&&mouse.y <= (margin.y + size.y*ratio.y)) return true;
		else return false;
	}
	void draw() {
		window->draw(background);
		window->draw(text);
	}
	void set_white_background() { background.setFillColor(sf::Color::White); }
	void set_yellow_background(){ background.setFillColor(sf::Color::Yellow); }
	sf::RectangleShape* get_background() { return &background; }
	sf::Text* get_text() { return &text; }
	void set_text(string txt) {
		text.setString(txt);
		size = sf::Vector2u(txt.length()*font_size*0.65, font_size + 10);
		background.setSize(sf::Vector2f(size));
	}
};

