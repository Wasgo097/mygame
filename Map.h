#pragma once
#include "Shared.h"
struct Position {
	Position(bool acc, char terr, char boss)
	{
		access = acc;
		terrain = terr;
		this->boss = boss;
	}
	bool access;
	char terrain;
	char boss;
};

class Map
{
	bool ** access;
	char ** boss;
	char ** terrain;
	//size
	unsigned int x;
	unsigned int y;
public:
	Map(bool ** acc, char**boss, char**terr,unsigned int x,unsigned int y) {
		access = acc;
		this->boss = boss;
		terrain = terr;
		this->x = x;
		this->y = y;
	}
	~Map() {
		clear_map(access, y);
		clear_map(boss, y);
		clear_map(terrain,y);
	}
	Position get_position(unsigned int x, unsigned int y)const{
		if (x > this->x || y > this->x||x<0||y<0) {
			std::cout << "Error read memory";
			exit(-1);
		}
		return Position(access[y][x], terrain[y][x], boss[y][x]);
	}
	Position get_position(sf::Vector2i vec)const {
		//position on maps
		unsigned int x = vec.x;
		unsigned int y = vec.y;
		return get_position(x, y);
	}
};



