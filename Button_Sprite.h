#pragma once
#include "Shared.h"
class Button_Sprite{
	sf::Sprite button_free;
	sf::Sprite button_target;
	sf::Sprite * button;
	sf::Texture target;
	sf::Texture free;
	sf::RenderWindow * window;
	sf::Vector2f ratio;
	unsigned int margin_x;
	unsigned int margin_y;/*
	unsigned int size_x;
	unsigned int size_y;*/
public:
	Button_Sprite(string path_target, string path_free, sf::RenderWindow* win, sf::Vector2f rat, /*sf::Vector2u size,*/ sf::Vector2u margin) {
		if (!target.loadFromFile(path_target)||!free.loadFromFile(path_free)) {
			std::cout << "error with load button texture";
			window->close();
			std::cin.ignore();
			exit(-1);
		}
		ratio = rat;
		margin_x = margin.x;
		margin_y = margin.y;
		/*size_x = size.x;
		size_y = size.y;*/
		button_free.setTexture(free);
		button_target.setTexture(target);
		button_free.setScale(ratio.x, ratio.y);
		button_target.setScale(ratio.x, ratio.y);
		button_free.setPosition(margin_x, margin_y);
		button_target.setPosition(margin_x, margin_y);
		button = &button_free;
		window = win;
	}
	~Button_Sprite() {

	}
	void draw() {
		window->draw(*button);
	}
	bool is_clicked(sf::Vector2i mouse) {
		if (mouse.x >= margin_x&&mouse.x <= (margin_x + button->getTexture()->getSize().x*ratio.x) && mouse.y >= margin_y&&mouse.y <= (margin_y + button->getTexture()->getSize().y*ratio.y)) return true;
		else return false;
	}
	bool is_target(sf::Vector2i mouse) {
		if (mouse.x >= margin_x && mouse.x <= (margin_x + button->getTexture()->getSize().x*ratio.x) && mouse.y >= margin_y && mouse.y <= (margin_y + button->getTexture()->getSize().y*ratio.y)) return true;
		else return false;
	}
	void set_target() { button = &button_target; }
	void set_free() { button = &button_free; }
};

