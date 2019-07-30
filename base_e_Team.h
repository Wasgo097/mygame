#pragma once
#include "eArcher.h"
#include "eFighter.h"
#include "eMage_warrior.h"
#include "eTank.h"
#include "eWizzard.h"
#include "Ghost.h"
#include "Orc.h"
#include "Werewolf.h"
#include "Spider.h"
#include "Wolf.h"
class base_e_Team{
protected:
	/*std::vector<Enemies*> e_team;
	std::vector<sf::Sprite> sprite_e_team;*/
	std::vector < std::pair < sf::Sprite, Enemies*>> e_team_full;
	sf::Vector2f ratio;
public:
	virtual ~base_e_Team() {for (auto c : e_team_full)delete c.second;}
	auto get_e_team() { return &e_team_full; }
	/*auto get_e_team() { return &e_team; }
	auto get_sprite_e_team() { return &sprite_e_team; }*/
};

