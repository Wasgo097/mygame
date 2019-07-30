#pragma once
#include "Shared.h"
#include "Map.h"
#include "Battle.h"
class Path {
	sf::RenderWindow * window;
	sf::Transformable * obj_t;
	sf::Drawable *obj_d;
	sf::Sprite * background;
	sf::Vector2i  current;
	const Map * map;
	std::queue<sf::Vector2i> path;
	std::shared_ptr<Team> team;
	void clear_path() {
		while (!path.empty())path.pop();
	}
public:
	Path(sf::RenderWindow *win, sf::Transformable & ob_t, sf::Drawable & ob_d, sf::Sprite & back,const Map * map, std::shared_ptr<Team> tea) {
		window = win;
		obj_t = &ob_t;
		obj_d = &ob_d;
		background = &back;
		current = sf::Vector2i(ob_t.getPosition());
		this->map = map;
		team = tea;
	}
	inline void add_new_point(sf::Vector2i x) {
		path.push(x);
	}
	void realize_path();
	void save_pos();
	void load_pos();
	//auto get_team() { return team; }
};
